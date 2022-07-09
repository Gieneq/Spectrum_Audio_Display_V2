#include "ASD_Core.h"

uint16_t _samplingFrequency = 44e3;
uint16_t _samplingTimeMicros = (int)(1e6/44e3);
//uint16_t _fftTimeMicros;
//uint16_t _renderTimeMicros;

#define IDLE_DETECTOR_ON_DISABLING_INTERVAL 500
#define IDLE_DETECTOR_OFF_ENABLING_INTERVAL 6000

typedef enum {
	IDLE_ON,
	IDLE_ON_DISABLING,
	IDLE_OFF,
	IDLE_OFF_ENABLING
} idle_t;

idle_t idleState;
uint32_t idleDetectorStartTime;;
uint32_t idleDetectorInterval;

animation_t _currentAnimation;
animation_t _attachedAnimation;

static volatile uint32_t _rnd_mix_1;
static volatile uint32_t _rnd_mix_2;

const uint16_t DAC_SINE_SAMPLES[128] = {2048, 2142, 2236, 2329, 2422, 2514, 2605, 2694, 2782, 2868, 2952, 3034, 3114, 3191, 3265, 3337, 3405, 3470, 3531, 3589, 3644, 3694, 3740, 3783, 3821, 3855, 3884, 3909, 3930, 3946, 3958, 3965, 3967, 3965, 3958, 3946, 3930, 3909, 3884, 3855, 3821, 3783, 3740, 3694, 3644, 3589, 3531, 3470, 3405, 3337, 3265, 3191, 3114, 3034, 2952, 2868, 2782, 2694, 2605, 2514, 2422, 2329, 2236, 2142, 2048, 1953, 1859, 1766, 1673, 1581, 1490, 1401, 1313, 1227, 1143, 1061, 981, 904, 830, 758, 690, 625, 564, 506, 451, 401, 355, 312, 274, 240, 211, 186, 165, 149, 137, 130, 128, 130, 137, 149, 165, 186, 211, 240, 274, 312, 355, 401, 451, 506, 564, 625, 690, 758, 830, 904, 981, 1061, 1143, 1227, 1313, 1401, 1490, 1581, 1673, 1766, 1859, 1953};

float32_t bands[BANDS_COUNT];
bounds_t bounds;

/*
 * SWIPE
 */
const float32_t SWIPE_FREQS[SWIPE_STEPS] = {22.0, 30.3, 55.3, 96.9, 155.1, 230.0, 321.5, 429.7, 554.5, 696.0, 854.1, 1028.8, 1220.2, 1428.2, 1652.9, 1894.2, 2152.1, 2426.7, 2717.9, 3025.8, 3350.3, 3691.4, 4049.2, 4423.7, 4814.7, 5222.4, 5646.8, 6087.8, 6545.4, 7019.7, 7510.6, 8018.2, 8542.4, 9083.2, 9640.7, 10214.9, 10805.6, 11413.0, 12037.1, 12677.8, 13335.1, 14009.1, 14699.7, 15407.0, 16130.9, 16871.4, 17628.6, 18402.4, 19192.9, 20000.0};
int _swipesCount;
int _currentSwipe;

int _swipeNextInterval = 250;
int _swipeNextCounter;

int _swipeCurrentFreq;
//int _swipe_number;
//int _current_swipe_step;
//#define SWIPE_DURATION_TICKS 50e3
//
//int _swipe_tick;
//int _swipe_current_tick;

static void onEnterIdleState() {
	_currentAnimation = ASD_Animation_dummy;
}

static void onLeaveIdleState() {
	_currentAnimation = _attachedAnimation;
}

static void updateIdeDetector(bounds_t *bounds) {
	int triggered = !bounds->isIdle;

	if(idleState == IDLE_ON) {
		if(triggered) {
			idleState = IDLE_ON_DISABLING;
			idleDetectorInterval = IDLE_DETECTOR_ON_DISABLING_INTERVAL;
			idleDetectorStartTime = HAL_GetTick();
		}
	} else if(idleState == IDLE_ON_DISABLING) {
		if(triggered) {
			if(HAL_GetTick() - idleDetectorStartTime > idleDetectorInterval){
				idleState = IDLE_OFF; //SUCCESS
				onLeaveIdleState();
			}
		} else
			idleState = IDLE_ON;
	} else if(idleState == IDLE_OFF) {
		if(!triggered) {
			idleState = IDLE_OFF_ENABLING;
			idleDetectorInterval = IDLE_DETECTOR_OFF_ENABLING_INTERVAL;
			idleDetectorStartTime = HAL_GetTick();
		}
	} else if(idleState == IDLE_OFF_ENABLING) {
		if(!triggered) {
			if(HAL_GetTick() - idleDetectorStartTime > idleDetectorInterval){
				idleState = IDLE_ON; //SUCCESS
				onEnterIdleState();
			}
		} else
			idleState = IDLE_OFF;
	}
}

void ASD_CORE_init() {
	ASD_FFT_init();

	HAL_TIM_Base_Start(&htim6); //timing
	HAL_TIM_Base_Start(&htim10); //random generator
	HAL_TIM_Base_Start_IT(&htim7); // swipe animation

	HAL_GPIO_WritePin(BATCH_DONE_GPIO_Port, BATCH_DONE_Pin, GPIO_PIN_RESET);

	// https://deepbluembedded.com/stm32-dac-sine-wave-generation-stm32-dac-dma-timer-example/
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)DAC_SINE_SAMPLES, DAC_SINE_SAMPLES_COUNT, DAC_ALIGN_12B_R);
    HAL_TIM_Base_Start(&htim2); //DAC trigger event
    ASD_CORE_setGeneratorFrequency(BASE_DAC_FREQ); //using Timer2 ARR
    ASD_CORE_attachAnimation(ASD_Animation_dummy);
    idleState = IDLE_ON;
    onEnterIdleState();
}

/* Execute every 1 tick = 1 ms */
void ASD_CORE_asyncUpdate() {
	_rnd_mix_1++;
	if(_swipesCount != 0) {
		/* Update swipe tick timer */
		if(_swipeNextCounter > 10) {
			_swipeNextCounter = 0;
			/* Switch to next freq */
			if(_swipeCurrentFreq >= SWIPE_STEPS) {
				_swipeCurrentFreq = 0;
				//you know
			}
			ASD_CORE_setGeneratorFrequency(SWIPE_FREQS[_swipeCurrentFreq]);
			_swipeCurrentFreq++;
		}
		_swipeNextCounter++;
	}

	HAL_GPIO_TogglePin(SWIPE_NEXT_GPIO_Port, SWIPE_NEXT_Pin);
}


void ASD_CORE_processSignal() {
	_rnd_mix_2++;
	/* Evaluate sampling time - load recorded time and start over. Then evaluate sampling frequency */
	_samplingTimeMicros = __HAL_TIM_GET_COUNTER(&htim6);
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	_samplingFrequency = 1000.0 * FFT_SAMPLES_COUNT / _samplingTimeMicros;

	/* Calculate FFT then convert it to bounds. Save evaluation time. */
	HAL_GPIO_WritePin(BATCH_DONE_GPIO_Port, BATCH_DONE_Pin, GPIO_PIN_SET);
	ASD_FFT_toggleBuffers();
	ASD_FFT_evalFFT(bands);

	ASD_FFT_evalDynamics(bands, &bounds, _samplingTimeMicros);
	updateIdeDetector(&bounds);
	_currentAnimation(&bounds);
	ASD_DISP_prepare();
	HAL_GPIO_WritePin(BATCH_DONE_GPIO_Port, BATCH_DONE_Pin, GPIO_PIN_RESET);
}


void ASD_CORE_render() {
	ASD_DISP_render();
}


void ASD_CORE_setGeneratorFrequency(float32_t freq) {
	if(freq > 0) {
		if(freq > DAC_TIM2_FREQ_SINE)
			freq = DAC_TIM2_FREQ_SINE;
		//todo limit wynikajacy z sampling freq
		uint32_t arr = (uint32_t)(DAC_TIM2_FREQ_SINE/freq);
		__HAL_TIM_SET_AUTORELOAD(&htim2, arr);
	}
}

/* Not working, I don't know why. Toggle signal is uneven on oscilloscope */
void ASD_CORE_setSwipe(int swipesCount) {
	_swipesCount = swipesCount;
}

void ASD_CORE_selectSignalSource(source_t source) {
	//todo some relay to switch signal to ADC
}

void ASD_CORE_attachAnimation(animation_t animation){
	_attachedAnimation = animation;
	if(idleState == IDLE_OFF || idleState == IDLE_OFF_ENABLING)
		onLeaveIdleState();
}
















//void ASD_attach_next_stage(animation_stage_t stage){
//	_next_stage = stage;
//}

/*
 * swipe < 0 - infinite,
 * swipe = 0 - turn off.
 * swipe > 0 - number of times
 */
//void ASD_swipe_frequencies(int swipe_number) {
//	_swipe_number = swipe_number;
//	_swipe_tick = (int)(1.0*SWIPE_DURATION_TICKS/swipe_number);
//	_swipe_current_tick = 0;
//}
//
////int freqq[8] = {100,200,400,800,1500,5e3,10e3,20e3};
////int kk = 0;
////int bb = 0;
//
//void ASD_update() {
//	if(_swipe_number != 0) {
//		_swipe_current_tick++;
//		if(_swipe_current_tick >= _swipe_tick) {
//			_swipe_current_tick = 0;
//
//			ASD_set_frequency(SWIPE_FREQS[_current_swipe_step]);
//			printf("Set freq %.1f\n", SWIPE_FREQS[_current_swipe_step]);
//			_current_swipe_step++;
//			if(_current_swipe_step >= SWIPE_STEPS){
//				_current_swipe_step = 0;
//				if(_swipe_number > 0)
//					_swipe_number--;
//			}
//		}
//	}
//}


























//volatile uint16_t samples_buffer[FFT_SAMPLES_COUNT*2];
//
//uint16_t * key_samples[2];
//volatile int samplesBufferIndex = 1; //0 'done' 1 is filling
//
//float32_t * key_magnitudes[2];
//volatile int magnitudesBufferIndex = 0; // shifted - 0 input is done, 1 input is filling - mags are calculated using 0.
//
//float32_t fft_input[FFT_SAMPLES_COUNT * 2];
//float32_t fft_magnitudes[FFT_SAMPLES_COUNT]; // twice long to calc derrivative - serio?2
//float32_t fft_magnitudes_derivative[BINS_COUNT];
//float32_t usable_magnitudes[BINS_COUNT];

//float32_t bounds_last_heights[BANDS_COUNT];
//float32_t bounds_heights[BANDS_COUNT];
//float32_t bounds_last_velocity[BANDS_COUNT];
//float32_t bounds_velocity[BANDS_COUNT];
//float32_t bounds_acceleration[BANDS_COUNT];
//float32_t fft_dts; //delta time refresh rate used in physical calculation of dynamics




//ASD_FFT_Init();
//ASD_swipe_frequencies(0);
////  ASD_attach_next_stage(ASD_animate); //exec after fft calc from interrupt
