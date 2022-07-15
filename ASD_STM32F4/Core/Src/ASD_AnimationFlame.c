#include <ASD_AnimationFlame.h>

#define DISPLAY_PIXELS_COUNT (BANDS_COUNT * DISPLAY_HEIGHT)

#define FLICKER_LENGTH 128
static const uint8_t FLICKER[] = {199, 218, 234, 245, 252, 255, 253, 248, 239, 228, 216, 204, 191, 180, 170, 163, 157, 154, 152, 152, 153, 155, 157, 159, 160, 160, 159, 157, 154, 151, 147, 143, 139, 136, 134, 133, 133, 134, 136, 138, 140, 143, 144, 146, 146, 145, 143, 140, 136, 131, 127, 122, 119, 116, 114, 114, 114, 116, 119, 123, 127, 131, 135, 137, 139, 139, 138, 136, 132, 128, 123, 119, 115, 112, 110, 110, 111, 114, 118, 124, 130, 137, 143, 148, 151, 153, 153, 151, 147, 141, 135, 127, 120, 114, 108, 105, 104, 105, 109, 115, 122, 131, 140, 148, 155, 160, 163, 162, 157, 150, 139, 126, 110, 94, 79, 64, 53, 44, 40, 40, 45, 55, 69, 87, 108, 131, 155, 178};

const uint8_t FIRE_TONGUE_HUE[] = {12, 16, 19, 19, 20, 19, 18, 17, 16, 18, 15, 13, 16, 15, 16, 14, 13, 4, 1, 255, 255}; //wartosc 20 to juz zielony

/* GRAVITY */
#define GRAVITY_FACTOR 1e-11
static float _barHeights[BANDS_COUNT];
static float _barVelocity[BANDS_COUNT];
static float _barAccelerations[BANDS_COUNT];

/* BURNT */
#define BURN_INTERVAL 42
static uint32_t lastBurnTime;
static uint8_t burn_value[DISPLAY_PIXELS_COUNT];

#define FLICKER_SPEED 0.00014;
static float32_t _flicker;

/* BLAZE */
#define BLAZE_INTERVAL 550
static uint32_t _lastBlazeTime;

#define MIN_BRIGHTNESS 0.25
#define MAX_BRIGHTNESS 1.0

volatile uint8_t _hueShift = 200;
int _hueCounter = 50;

static uint8_t getPixelBurnTick(int x, int y){
	if(x > 0 && x < BANDS_COUNT && y > 0 && y < DISPLAY_HEIGHT)
		return burn_value[x + y * BANDS_COUNT];
	return 0;
}

static inline void setPixelBurnTicks(int x, int y, uint8_t ticksLeft) {
	if(x > 0 && x < BANDS_COUNT && y > 0 && y < DISPLAY_HEIGHT)
		burn_value[x + y * BANDS_COUNT] = ticksLeft;
}

static void makeDisplayBurnTick() {
	for (int ix = 0; ix < BANDS_COUNT; ix++) {
		for (int iy = 0; iy < DISPLAY_HEIGHT; iy++) {
			uint8_t burnTick = getPixelBurnTick(ix, iy);
			if(burnTick > 0) {
				setPixelBurnTicks(ix, iy, --burnTick);
			}
		}
	}
}

void ASD_Animation_flame(bounds_t* bouds) {
	float32_t dt = bouds->dt_sec;

	/******************************************************
	 *                      GRAVITY                       *
	 ******************************************************/

	/* Acceleration */
	for (int ix = 0; ix < BANDS_COUNT; ix++) {
		_barAccelerations[ix] = -GRAVITY_FACTOR;
	}

	/* Velocity */
	for (int ix = 0; ix < BANDS_COUNT; ix++) {
		_barVelocity[ix] += _barAccelerations[ix] * dt;
	}

	/* Position */
	for (int ix = 0; ix < BANDS_COUNT; ix++) {
		_barHeights[ix] += _barVelocity[ix] * dt;

		if(bouds->heights[ix] > _barHeights[ix]) {
			if(!bouds->isIdle) //prevent from bottom flicekring, i hope
				_barHeights[ix] = bouds->heights[ix];
			_barVelocity[ix] = 0;//todo alboz roznicy polozen albo ze struktury
			_barAccelerations[ix] = 0;//todo inertia
		}

		if(_barHeights[ix] <= 0.0) {
			_barHeights[ix] = 0.0;
			_barVelocity[ix] = 0;
			_barAccelerations[ix] = 0;
		}
	}

	/******************************************************
	 *                        Burn                        *
	 ******************************************************/

	if(HAL_GetTick() - lastBurnTime > BURN_INTERVAL) {
		lastBurnTime += BURN_INTERVAL;
		makeDisplayBurnTick();
	}

	////////////////////

	_hueCounter += 1;
	if(_hueCounter > 8){
		_hueCounter = 0;
		_hueShift++;
		if(_hueShift > 255)
			_hueShift = 0;
	}


	/******************************************************
	 *                     Animation                      *
	 ******************************************************/

	_flicker += dt * FLICKER_SPEED;
	while(_flicker >= FLICKER_LENGTH)
		_flicker -= FLICKER_LENGTH;
	uint32_t flickerIndex = (uint32_t)(_flicker);

	for (int ix = 0; ix < BANDS_COUNT; ix++) {
		int barHeight = (int)(60.0 * _barHeights[ix]); //drawable
		if(barHeight > DISPLAY_HEIGHT)
			barHeight = DISPLAY_HEIGHT;

		for (int iy = 0; iy < barHeight; iy++) {
			uint8_t hue = (FIRE_TONGUE_HUE[DISPLAY_HEIGHT - 1 - (barHeight - iy - 1)] + _hueShift) % 255;
			uint32_t saturation_32 = 160 + (DISPLAY_HEIGHT - 1 - (barHeight - iy - 1)) * 6;
			uint8_t saturation = saturation_32 > 255 ? 255 : (uint8_t)(saturation_32);

			uint8_t flickerIndexShifted = (uint8_t)((flickerIndex + iy + ix * 3)%FLICKER_LENGTH);
			uint8_t value = 255 - (uint8_t)(FLICKER[flickerIndexShifted]*0.75);

			ASD_DISP_setPixel(ix, iy, hue, saturation, value);

			uint8_t burnValue = 14 + (uint8_t)(ASD_UTILS_getRandom()%22);
			setPixelBurnTicks(ix, iy, burnValue);

		}

		for (int iy = barHeight; iy < DISPLAY_HEIGHT; iy++) {
			uint8_t burnTick = getPixelBurnTick(ix, iy);
			if(burnTick > 0) {
				ASD_DISP_setPixel(ix, iy, 255 +_hueShift, 255, burnTick);
			} else {
				ASD_DISP_setPixel(ix, iy, 0, 255, 0);
			}
		}
	}

	/******************************************************
	 *                       Blaze                        *
	 ******************************************************/
	if(bouds->bassTrig)
		_lastBlazeTime = HAL_GetTick();

	if(HAL_GetTick() - _lastBlazeTime < BLAZE_INTERVAL){
		float32_t blazeValue = (MAX_BRIGHTNESS - MIN_BRIGHTNESS)*(1.0 - ((HAL_GetTick() - _lastBlazeTime) / BLAZE_INTERVAL));
		ASD_DISP_setMaxBrightness(MIN_BRIGHTNESS + blazeValue);
	} else
		ASD_DISP_setMaxBrightness(MIN_BRIGHTNESS);

}
