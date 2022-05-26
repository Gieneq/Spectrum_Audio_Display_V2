#pragma once

#include <arm_math.h>
#include <arm_const_structs.h>
#include "adc.h"
#include "main.h"
#include "tim.h"
#include "ASD_presets.h"
#include "stdio.h"

//#define STATE_SAMPLING 0
#define STATE_READY 1
//#define STATE_PROCESSING 2
#define STATE_FINISHED 3

void ASD_FFT_Init();
void ASD_Next_Sample_Aquired();
void ASD_update();

void ASD_Print_Results();
