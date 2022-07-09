#pragma once

#include <ASD_Utils.h>
#include "main.h"
#include "spi.h"

/*
 * 1 bit of WS2812B protocol is encoded with 4 bits of SPI. SPI works in 8 bit mode so in each dataframe 2 bits are encoded.
 * 1 bit of WS2812B has period of 4/fclk = 4/(26/8) = 1.23 us so RES needs minimum 41 WS2812B bits. It is better to use 48 bits.
 * 1 uint8_t can store 2 bits
 * 1 uint32_t can store 8 bits = 1 channel
 * 1 led needs 3x uint32_t (24 bits)
 * RES needs 48/8 = 6 uint32_t
 * entire matrix needs (399+14)*3 + 6 = 1245
 * color format GRB
 */
#define COLOR_CHANNELS 3
#define BITS_PER_CHANNEL 8
#define SPI_RES_LENGTH_BITS 48
#define SPI_RES_LENGTH_32T 6
#define SPI_DATA_PER_BIT 4

#define BIT_0 0x8
#define BIT_1 0xE

//#define TRANSMIT_BUFFER_LEN_32T ((FRONT_LEDS_COUNT + BASE_LEDS_COUNT) * COLOR_CHANNELS + SPI_RES_LENGTH_32T)
//#define TRANSMIT_BUFFER_LEN_8T (TRANSMIT_BUFFER_LEN_32T * 4)
//
//#define DRAW_BUFFER_LEN (FRONT_LEDS_COUNT + BASE_LEDS_COUNT)


CHSV* ASD_DISP_getPixel(int x, int y);
void ASD_DISP_setPixel(int x, int y, uint8_t hue, uint8_t saturation, uint8_t value);
void ASD_DISP_prepare();
void ASD_DISP_render();
void ASD_DISP_setMaxBrightness(float32_t brightness); //0-1
