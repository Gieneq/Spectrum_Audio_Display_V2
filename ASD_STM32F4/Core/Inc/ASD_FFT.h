#pragma once

#include <arm_math.h>
#include <arm_const_structs.h>
#include "adc.h"
#include "main.h"
#include "tim.h"
#include "dac.h"
#include "ASD_presets.h"
#include "stdio.h"

#define STATE_SAMPL_DONE 0
#define STATE_FFT_DONE 1

#define PRINT_BUFFER_SIZE 64

#define DAC_SINE_SAMPLES_COUNT 128
#define DAC_FREQ ((float32_t)(90e6))
#define DAC_FREQ_D_SMP_CNT ((float32_t)(90e6)/DAC_SINE_SAMPLES_COUNT)

void ASD_FFT_Init();
void ASD_Next_Batch_Aquired();
void ASD_update();
void ASD_set_frequency(float32_t freq);

void ASD_Print_Results();
