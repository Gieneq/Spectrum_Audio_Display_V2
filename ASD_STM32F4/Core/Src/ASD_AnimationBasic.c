#include <ASD_AnimationBasic.h>

#define NOISE_LENGTH 128
static const uint8_t NOISE[] = {199, 218, 234, 245, 252, 255, 253, 248, 239, 228, 216, 204, 191, 180, 170, 163, 157, 154, 152, 152, 153, 155, 157, 159, 160, 160, 159, 157, 154, 151, 147, 143, 139, 136, 134, 133, 133, 134, 136, 138, 140, 143, 144, 146, 146, 145, 143, 140, 136, 131, 127, 122, 119, 116, 114, 114, 114, 116, 119, 123, 127, 131, 135, 137, 139, 139, 138, 136, 132, 128, 123, 119, 115, 112, 110, 110, 111, 114, 118, 124, 130, 137, 143, 148, 151, 153, 153, 151, 147, 141, 135, 127, 120, 114, 108, 105, 104, 105, 109, 115, 122, 131, 140, 148, 155, 160, 163, 162, 157, 150, 139, 126, 110, 94, 79, 64, 53, 44, 40, 40, 45, 55, 69, 87, 108, 131, 155, 178};

static float _barHeights[BANDS_COUNT];
static float _barVelocity[BANDS_COUNT];
static float _barAccelerations[BANDS_COUNT];

#define PARTICLE_GEN_INTERVAL 80
static uint32_t lastParticleGenTime;
#define MIN_SATURATION 200
#define MIN_VALUE 120

static const float32_t HUE_INCREMENT = 255.0/(BANDS_COUNT * DISPLAY_HEIGHT);
static uint16_t _hueIdx = 0;

void ASD_Animation_dummy(bounds_t* bounds) {
	if(HAL_GetTick() - lastParticleGenTime > PARTICLE_GEN_INTERVAL) {
		lastParticleGenTime = HAL_GetTick();
		uint8_t rndValue;
		int nextX, nextY;
		int incr = 0;

		while(1) {
			rndValue = NOISE[(HAL_GetTick() + incr++) % NOISE_LENGTH];
			rndValue ^= (uint8_t)(HAL_GetTick());

			nextX = (rndValue + 81) % BANDS_COUNT;
			nextY = (rndValue + 7) % DISPLAY_HEIGHT;

			CHSV* currentPixel = ASD_DISP_getPixel(nextX, nextY);
			//todo change pixel count to true max
			if(((currentPixel != NULL) && (currentPixel->val <= 0)) || incr > (BANDS_COUNT * DISPLAY_HEIGHT))
				break;
		}

		uint8_t nextHue = (uint8_t)((uint32_t)(rndValue + 41) % 256);
		uint8_t nextSat = (uint8_t)((uint32_t)(rndValue + 123) % (256-MIN_SATURATION) + MIN_SATURATION);
		uint8_t nextVal = (uint8_t)((uint32_t)(rndValue + 7) % (256-MIN_VALUE) + MIN_VALUE);

		ASD_DISP_setPixel(nextX, nextY, nextHue, nextSat, nextVal);
	}

	_hueIdx = 0;
	for (int ix = 0; ix < BANDS_COUNT; ix++) {
		for (int iy = 0; iy < DISPLAY_HEIGHT; iy++) {
			CHSV* currentPixel = ASD_DISP_getPixel(ix, iy);
			if(currentPixel != NULL) {
				if(currentPixel->val > 0)
					currentPixel->val--;
			}
		}
	}
}

void ASD_Animation_basic(bounds_t *bouds) {
	float32_t dt = bouds->dt_sec;

	/******************************************************
	 *                      GRAVITY                       *
	 ******************************************************/

	/* Acceleration */
	for (int ix = 0; ix < BANDS_COUNT; ix++) {
		_barAccelerations[ix] = - 1e-11;
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

	_hueIdx = 0;
	for (int ix = 0; ix < BANDS_COUNT; ix++) {
		int barHeight = (int)(60.0 * _barHeights[ix]); //drawable
		if(barHeight == 1)
			barHeight = 0;
		if(barHeight >= DISPLAY_HEIGHT)
			barHeight = DISPLAY_HEIGHT-1;

		for (int iy = 0; iy < barHeight; iy++)
			ASD_DISP_setPixel(ix, iy, (uint8_t)(_hueIdx++ * HUE_INCREMENT), 255, 255);

		for (int iy = barHeight; iy < DISPLAY_HEIGHT; iy++)
			ASD_DISP_setPixel(ix, iy, 0, 255, 0);

	}
}
