#pragma once

#include "main.h"

#define FFT_SAMPLES_COUNT 1024
//#define SAMPLES_BUFFER_LEN (2*FFT_SAMPLES_COUNT)

#define BANDS_COUNT 19
#define DISPLAY_HEIGHT 21

#define FRONT_LEDS_COUNT (BANDS_COUNT*DISPLAY_HEIGHT)
#define BASE_LEDS_COUNT (7*2)

// Remeber to change in Cube Configuration
#define SAMPLING_RATE 44e3
#define FFT_REFRESHRATE 30
#define DISPLAY_REFRESHRATE 30

typedef struct bounds_t {
	float32_t heights[BANDS_COUNT];
	float32_t velocities[BANDS_COUNT];
	float32_t accelerations[BANDS_COUNT];
	float32_t dt_sec;
	float32_t heightsSum;
	int isIdle;
} bounds_t;

//typedef void (*animation_stage_t)(bounds_t* bounds);
typedef void (*animation_t)(bounds_t* bounds);

typedef enum
{
    SOURCE_DAC,
	SOURCE_AUX
} source_t;

typedef void (*task_event_t)();

typedef struct task_t {
	uint32_t intervalTicks;
	uint32_t currentIntervalTicks;
	int active;
	task_event_t task;

} task_t;

