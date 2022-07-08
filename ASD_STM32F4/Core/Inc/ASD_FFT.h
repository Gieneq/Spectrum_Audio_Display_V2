#pragma once

#include "main.h"
#include "adc.h"
#include <ASD_Presets.h>

#define BINS_COUNT (FFT_SAMPLES_COUNT/2)


void ASD_FFT_init();
void ASD_FFT_toggleBuffers();
float32_t* ASD_FFT_evalFFT(float32_t* boundHeights);
void ASD_FFT_evalDynamics(float32_t* boundHeights, bounds_t* bounds, float32_t dts);
void ASD_FFT_printDebug();
