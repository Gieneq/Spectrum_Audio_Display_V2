#include "ASD_FFT.h"

volatile uint16_t sapling_time_micros;
volatile uint16_t samples_buffer[FFT_SAMPLES_COUNT*2];

volatile int state = STATE_FINISHED;

uint16_t * key_samples[2];
volatile int samplesBufferIndex = 1;

float32_t * key_magnitudes[2];
volatile int magnitudesBufferIndex = 0;

float32_t fft_input[FFT_SAMPLES_COUNT * 2];
float32_t fft_magnitudes[FFT_SAMPLES_COUNT * 2]; // twice long to calc derrivative


void ASD_FFT_Init() {
	key_samples[0] = (uint16_t *)(&samples_buffer[0]);
	key_samples[1] = (uint16_t *)(&samples_buffer[FFT_SAMPLES_COUNT]);

	key_magnitudes[0] = (float32_t *)(&fft_magnitudes[0]);
	key_magnitudes[1] = (float32_t *)(&fft_magnitudes[FFT_SAMPLES_COUNT]);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)samples_buffer, FFT_SAMPLES_COUNT * 2);
	HAL_TIM_Base_Start(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, fft_input, 0, 1);
}

void ASD_Next_Sample_Aquired() {
	sapling_time_micros = __HAL_TIM_GET_COUNTER(&htim6);
	__HAL_TIM_SET_COUNTER(&htim6,0);

	if(state == STATE_FINISHED) {
		samplesBufferIndex ^= 1;
		magnitudesBufferIndex ^= 1;
		state = STATE_READY;
	}
}

//todo :
// sampling na 2 bufory
// jak koniec bufora 0 to uzupelnia pierwszy
// fft liczy sie na próbkach z 1 pozniej z 0
//magnitudy tez na zmiane
//animacje licze z ostatnich magnitud, startowane od przerwania z DMA

void ASD_update() {
	if(state == STATE_READY){

		uint16_t * startSamplesBuffer = key_samples[samplesBufferIndex];
		float32_t * startMagnitudesBuffer = key_magnitudes[magnitudesBufferIndex];

		for(int i = 0; i < FFT_SAMPLES_COUNT * 2; i++)
			fft_input[i] = (i%2 == 0 ? startSamplesBuffer[i/2] : 0.0);

		arm_cmplx_mag_f32(fft_input, startMagnitudesBuffer, FFT_SAMPLES_COUNT);

		//todo scale 2/samples count *
		//todo calc derrivative


		state = STATE_FINISHED;
	}


}


void ASD_Print_Results(){
	float32_t sapling_time_millis = sapling_time_micros/1000.0;
	float32_t sampling_freq_kHz = 1.0/(sapling_time_millis/FFT_SAMPLES_COUNT);
	printf("Sampling time: %.2f us. Sampling frequency: %.2f kHz, idx %d\n", sapling_time_millis, sampling_freq_kHz, samplesBufferIndex);
}
