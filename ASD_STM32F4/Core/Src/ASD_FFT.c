#include "ASD_FFT.h"

volatile static uint16_t samples_buffer[SAMPLES_BUFFER_LEN];


void ASD_FFT_Init(){
//	  HAL_ADCEx_Calibration_Start(&hadc1);
	  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)samples_buffer, 2048);
//jakis index do sledzenia gdzie jest onwersja
}
