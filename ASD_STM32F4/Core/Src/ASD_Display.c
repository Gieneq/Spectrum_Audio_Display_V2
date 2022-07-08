#include "ASD_Display.h"

const uint32_t COLOR_LUT[256] = {2290649224, 2391312520, 3901261960, 4001925256, 2291042440, 2391705736, 3901655176, 4002318472, 2296940680, 2397603976, 3907553416, 4008216712, 2297333896, 2397997192, 3907946632, 4008609928, 2290650760, 2391314056, 3901263496, 4001926792, 2291043976, 2391707272, 3901656712, 4002320008, 2296942216, 2397605512, 3907554952, 4008218248, 2297335432, 2397998728, 3907948168, 4008611464, 2290673800, 2391337096, 3901286536, 4001949832, 2291067016, 2391730312, 3901679752, 4002343048, 2296965256, 2397628552, 3907577992, 4008241288, 2297358472, 2398021768, 3907971208, 4008634504, 2290675336, 2391338632, 3901288072, 4001951368, 2291068552, 2391731848, 3901681288, 4002344584, 2296966792, 2397630088, 3907579528, 4008242824, 2297360008, 2398023304, 3907972744, 4008636040, 2290649230, 2391312526, 3901261966, 4001925262, 2291042446, 2391705742, 3901655182, 4002318478, 2296940686, 2397603982, 3907553422, 4008216718, 2297333902, 2397997198, 3907946638, 4008609934, 2290650766, 2391314062, 3901263502, 4001926798, 2291043982, 2391707278, 3901656718, 4002320014, 2296942222, 2397605518, 3907554958, 4008218254, 2297335438, 2397998734, 3907948174, 4008611470, 2290673806, 2391337102, 3901286542, 4001949838, 2291067022, 2391730318, 3901679758, 4002343054, 2296965262, 2397628558, 3907577998, 4008241294, 2297358478, 2398021774, 3907971214, 4008634510, 2290675342, 2391338638, 3901288078, 4001951374, 2291068558, 2391731854, 3901681294, 4002344590, 2296966798, 2397630094, 3907579534, 4008242830, 2297360014, 2398023310, 3907972750, 4008636046, 2290649320, 2391312616, 3901262056, 4001925352, 2291042536, 2391705832, 3901655272, 4002318568, 2296940776, 2397604072, 3907553512, 4008216808, 2297333992, 2397997288, 3907946728, 4008610024, 2290650856, 2391314152, 3901263592, 4001926888, 2291044072, 2391707368, 3901656808, 4002320104, 2296942312, 2397605608, 3907555048, 4008218344, 2297335528, 2397998824, 3907948264, 4008611560, 2290673896, 2391337192, 3901286632, 4001949928, 2291067112, 2391730408, 3901679848, 4002343144, 2296965352, 2397628648, 3907578088, 4008241384, 2297358568, 2398021864, 3907971304, 4008634600, 2290675432, 2391338728, 3901288168, 4001951464, 2291068648, 2391731944, 3901681384, 4002344680, 2296966888, 2397630184, 3907579624, 4008242920, 2297360104, 2398023400, 3907972840, 4008636136, 2290649326, 2391312622, 3901262062, 4001925358, 2291042542, 2391705838, 3901655278, 4002318574, 2296940782, 2397604078, 3907553518, 4008216814, 2297333998, 2397997294, 3907946734, 4008610030, 2290650862, 2391314158, 3901263598, 4001926894, 2291044078, 2391707374, 3901656814, 4002320110, 2296942318, 2397605614, 3907555054, 4008218350, 2297335534, 2397998830, 3907948270, 4008611566, 2290673902, 2391337198, 3901286638, 4001949934, 2291067118, 2391730414, 3901679854, 4002343150, 2296965358, 2397628654, 3907578094, 4008241390, 2297358574, 2398021870, 3907971310, 4008634606, 2290675438, 2391338734, 3901288174, 4001951470, 2291068654, 2391731950, 3901681390, 4002344686, 2296966894, 2397630190, 3907579630, 4008242926, 2297360110, 2398023406, 3907972846, 4008636142};

uint32_t _transmit_buffer[1245]; //399*3+48//TRANSMIT_BUFFER_LEN_32T
CHSV _draw_hsv_buffer[399];//DRAW_BUFFER_LEN
CHSV hsvData;
CRGB rgbData;
float32_t _maxBrightness;

//todo cos podobnego do podstawy, tylko inne indexy np jakos wymatrycznie albo lewyprawy


#define APPLY_DIMMING(X) (X)
#define HSV_SECTION_6 (0x20)
#define HSV_SECTION_3 (0x40)


void hsv2rgb_raw_C (const struct CHSV* hsv, struct CRGB* rgb)
{
    // Convert hue, saturation and brightness ( HSV/HSB ) to RGB
    // "Dimming" is used on saturation and brightness to make
    // the output more visually linear.

    // Apply dimming curves
    uint8_t value = APPLY_DIMMING( hsv->val);
    uint8_t saturation = hsv->sat;

    // The brightness floor is minimum number that all of
    // R, G, and B will be set to.
    uint8_t invsat = APPLY_DIMMING( 255 - saturation);
    uint8_t brightness_floor = (value * invsat) / 256;

    // The color amplitude is the maximum amount of R, G, and B
    // that will be added on top of the brightness_floor to
    // create the specific hue desired.
    uint8_t color_amplitude = value - brightness_floor;

    // Figure out which section of the hue wheel we're in,
    // and how far offset we are withing that section
    uint8_t section = hsv->hue / HSV_SECTION_3; // 0..2
    uint8_t offset = hsv->hue % HSV_SECTION_3;  // 0..63

    uint8_t rampup = offset; // 0..63
    uint8_t rampdown = (HSV_SECTION_3 - 1) - offset; // 63..0


    //  //rampdown *= 4; // 0..252

    // compute color-amplitude-scaled-down versions of rampup and rampdown
    uint8_t rampup_amp_adj   = (rampup   * color_amplitude) / (256 / 4);
    uint8_t rampdown_amp_adj = (rampdown * color_amplitude) / (256 / 4);

    // add brightness_floor offset to everything
    uint8_t rampup_adj_with_floor   = rampup_amp_adj   + brightness_floor;
    uint8_t rampdown_adj_with_floor = rampdown_amp_adj + brightness_floor;


    if( section ) {
        if( section == 1) {
            // section 1: 0x40..0x7F
            rgb->r = brightness_floor;
            rgb->g = rampdown_adj_with_floor;
            rgb->b = rampup_adj_with_floor;
        } else {
            // section 2; 0x80..0xBF
            rgb->r = rampup_adj_with_floor;
            rgb->g = brightness_floor;
            rgb->b = rampdown_adj_with_floor;
        }
    } else {
        // section 0: 0x00..0x3F
        rgb->r = rampdown_adj_with_floor;
        rgb->g = rampup_adj_with_floor;
        rgb->b = brightness_floor;
    }
}

void ASD_DISP_setPixel(int x, int y, uint8_t hue, uint8_t saturation, uint8_t value) {
	x = BANDS_COUNT - x - 1;
	y = (x%2?DISPLAY_HEIGHT-y-1:y);
	int idx = y + x * DISPLAY_HEIGHT;

	if(idx > 399)
		return;

	_draw_hsv_buffer[idx].hue = hue;
	_draw_hsv_buffer[idx].saturation = saturation;
	_draw_hsv_buffer[idx].value = value;
}

void ASD_DISP_prepare() {
	/* Clear transmit buffer */
	for(int i = 0; i < 1245; i++)
		_transmit_buffer[i] = 0;
//
	for(int pixel_idx = 0; pixel_idx < 399; pixel_idx++) {
		hsvData = _draw_hsv_buffer[pixel_idx];
		hsv2rgb_raw_C(&hsvData, &rgbData);
//
//		hsv_data.value *= _maxBrightness; //todo

//		//convert rgb to protocol data each pixel send as 3xuint32_t
		int green_transmit_data_idx = pixel_idx * 3 + 0;
		int red_transmit_data_idx   = pixel_idx * 3 + 1;
		int blue_transmit_data_idx  = pixel_idx * 3 + 2;
//
		_transmit_buffer[green_transmit_data_idx] |=  COLOR_LUT[rgbData.g];
		_transmit_buffer[red_transmit_data_idx]   |=  COLOR_LUT[rgbData.r];
		_transmit_buffer[blue_transmit_data_idx]  |=  COLOR_LUT[rgbData.b];
	}
//	//RES always zeros
}

void ASD_DISP_render() {
	if (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_BUSY)
		HAL_SPI_Transmit_DMA(&hspi2, (uint8_t*)(_transmit_buffer), 4980);
}

void ASD_DISP_setMaxBrightness(float32_t brightness) {
	_maxBrightness = brightness;
}

