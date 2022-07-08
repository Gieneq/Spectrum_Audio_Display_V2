#pragma once

#include <ASD_AnimationBasic.h>
#include "main.h"
#include <ASD_Presets.h>
#include <ASD_FFT.h>
#include <ASD_Display.h>


/* DAC is used to generate sine with variable frequency to test FFT evaluation
 * and to sompare the display with simulation.
 * 128 samples is fine
 */
#define BASE_DAC_FREQ 15e3
#define DAC_SINE_SAMPLES_COUNT 128
#define DAC_TIM2_FREQ ((float32_t)(52e6))
#define DAC_TIM2_FREQ_SINE (DAC_TIM2_FREQ/DAC_SINE_SAMPLES_COUNT)

#define SWIPE_STEPS 50

void ASD_CORE_init();
void ASD_CORE_asyncUpdate();
void ASD_CORE_processSignal();
void ASD_CORE_render();
void ASD_CORE_setGeneratorFrequency(float32_t freq);
void ASD_CORE_setSwipe(int swipesCount);
void ASD_CORE_selectSignalSource(source_t source);
void ASD_CORE_attachAnimation(animation_t animation);
