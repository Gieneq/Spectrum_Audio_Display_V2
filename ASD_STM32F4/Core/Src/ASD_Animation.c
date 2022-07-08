#include "ASD_Animation.h"

//hsv_t* _draw_hsv_buff;
int _hsv_buff_len;

#define COOLING_SPEED 0.981
float _heat[BANDS_COUNT];



//#define GRAVITY_FACTOR 0.001*9.81/4096.0
//#define GRAVITY_FACTOR 9.81
float _barHeights[BANDS_COUNT];
float _barVelocity[BANDS_COUNT];
float _barAccelerations[BANDS_COUNT];


//int barHeights[BANDS_COUNT] = { 21, 20, 19, 6, 1, 5, 0, 0, 0, 0, 0, 3, 0, 11, 18, 16, 15, 12, 4 };

void ASD_animate(bounds_t *bouds) {
	float32_t dt = bouds->dt_sec;

	//todo uciac zeby nie migalo na dole - minimalna zmiana to 2 wysokosci albo cos takiego - hisereza?

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


	//clear
	for (int ix = 0; ix < BANDS_COUNT; ix++) {
		for (int iy = 0; iy < DISPLAY_HEIGHT; iy++) {
			ASD_DISP_setPixel(ix, iy, 0, 255, 0);
		}
	}


	uint16_t i = 0;
	for (int ix = 0; ix < BANDS_COUNT; ix++) {
		int barHeight = (int)(60.0 * _barHeights[ix]); //drawable
		if(barHeight >= DISPLAY_HEIGHT)
			barHeight = DISPLAY_HEIGHT-1;

		//err barHeight
		for (int iy = 0; iy < barHeight; iy++) {
			ASD_DISP_setPixel(ix, iy, i % 255, 255, 255);
			i++;
		}
	}
	//reszta wypalana
}



//	for (int i = 0; i < BANDS_COUNT; i++) {
//		printf("%.3f, ", bouds->heights[i]);
//	}
//	printf("\n");
