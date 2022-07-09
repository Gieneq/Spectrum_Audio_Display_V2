#include "ASD_Utils.h"

uint32_t ASD_UTILS_getRandom() {
	uint32_t rnd = __HAL_TIM_GET_COUNTER(&htim10);
//	rnd *= _rnd_mix_1;
//	rnd ^= _rnd_mix_2;
	rnd ^= 0x8F567891;
//	rnd += _rnd_mix_1<<8;
//	rnd ^= HAL_GetTick();
	return rnd;
}
