#include "ASD_FFT.h"

uint32_t current_sample;
volatile static uint16_t samples_buffer[SAMPLES_BUFFER_LEN];


void ASD_FFT_Init(){
//	  HAL_ADCEx_Calibration_Start(&hadc1);
	  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)samples_buffer, SAMPLES_BUFFER_LEN);
//jakis index do sledzenia gdzie jest onwersja
}

void ASD_Next_Sample_Aquired(){
	current_sample++;
	if(current_sample >= SAMPLES_BUFFER_LEN)
		current_sample = 0;
	while(1);
	//shift 2 wskaznikow jednoczesnie
}
