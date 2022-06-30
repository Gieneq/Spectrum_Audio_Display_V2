#include "ASD_FFT.h"

/* DAC is used to generate sine with variable frequency to test FFT evaluation
 * and to sompare the display with simulation.
 * 128 samples is fine*/
const uint16_t DAC_SINE_SAMPLES[128] = {2048, 2142, 2236, 2329, 2422, 2514, 2605, 2694, 2782, 2868, 2952, 3034, 3114, 3191, 3265, 3337, 3405, 3470, 3531, 3589, 3644, 3694, 3740, 3783, 3821, 3855, 3884, 3909, 3930, 3946, 3958, 3965, 3967, 3965, 3958, 3946, 3930, 3909, 3884, 3855, 3821, 3783, 3740, 3694, 3644, 3589, 3531, 3470, 3405, 3337, 3265, 3191, 3114, 3034, 2952, 2868, 2782, 2694, 2605, 2514, 2422, 2329, 2236, 2142, 2048, 1953, 1859, 1766, 1673, 1581, 1490, 1401, 1313, 1227, 1143, 1061, 981, 904, 830, 758, 690, 625, 564, 506, 451, 401, 355, 312, 274, 240, 211, 186, 165, 149, 137, 130, 128, 130, 137, 149, 165, 186, 211, 240, 274, 312, 355, 401, 451, 506, 564, 625, 690, 758, 830, 904, 981, 1061, 1143, 1227, 1313, 1401, 1490, 1581, 1673, 1766, 1859, 1953};

/* ADC samples used to test. In this signal there are 2 spikes at 210 Hz and 12kHz. First lobe is much higher. There should he high spike at 2nd band and lower spike at 7th bound.
 * */
const uint16_t ADC_SAMPLES[1024*2] = {2263, 2117, 1980, 1845, 2415, 2004, 2442, 2133, 2569, 2429, 2542, 2195, 2660, 2497, 2677, 2598, 2816, 2514, 2729, 3076, 2758, 2946, 3099, 3226, 3126, 2819, 3163, 3103, 3004, 3191, 3256, 3233, 3019, 3173, 3378, 3307, 3062, 3516, 3789, 3433, 3339, 3472, 3411, 3605, 3517, 3574, 3515, 3721, 3646, 3762, 3483, 3418, 3521, 3547, 3370, 3643, 3831, 3643, 3439, 3747, 3517, 3583, 3489, 3574, 3584, 3283, 3605, 3799, 3685, 3013, 3207, 3362, 3206, 3323, 3433, 2947, 2986, 3283, 3312, 3165, 2882, 3075, 3133, 2897, 2861, 3034, 2776, 2702, 2776, 3043, 2816, 2520, 2615, 2564, 2451, 2387, 2501, 2419, 2075, 2386, 2316, 2332, 2062, 2269, 1995, 1911, 1986, 1902, 1865, 1669, 1559, 1927, 1767, 1361, 1728, 1460, 1379, 1125, 1729, 1479, 1174, 1170, 1599, 1469, 742, 1406, 1462, 992, 752, 1260, 967, 672, 696, 1093, 904, 559, 932, 681, 722, 614, 779, 673, 606, 720, 821, 547, 425, 718, 678, 502, 372, 258, 690, 665, 543, 608, 404, 309, 554, 413, 277, 240, 663, 489, 424, 483, 827, 524, 747, 355, 598, 622, 926, 741, 711, 496, 914, 842, 822, 598, 704, 1012, 838, 1026, 1066, 924, 945, 1084, 1279, 1066, 1198, 1338, 1649, 1333, 1337, 1250, 1540, 1358, 1614, 1847, 1472, 1609, 1664, 2131, 1435, 1448, 1735, 1802, 1616, 2290, 2137, 1830, 2159, 2166, 2145, 2284, 2323, 2429, 2662, 2313, 2740, 2764, 2774, 2496, 2557, 3199, 2544, 2671, 2858, 2876, 2787, 2971, 3232, 3246, 2888, 2974, 3048, 2927, 2835, 3475, 3202, 3063, 3290, 3253, 3163, 3327, 3564, 3454, 3588, 3158, 3547, 3483, 2905, 3802, 3724, 3319, 3710, 3715, 3730, 3341, 3488, 3462, 3724, 3346, 3575, 3889, 3546, 3439, 3658, 3526, 3524, 3655, 3745, 3653, 3168, 3306, 3352, 3549, 3201, 3659, 3331, 3127, 3216, 3541, 3283, 3081, 3174, 3320, 2892, 2947, 3095, 3114, 2929, 2744, 3023, 2855, 2729, 2899, 2743, 2743, 2833, 2468, 2557, 2273, 2355, 2828, 2438, 2087, 2398, 2317, 2341, 2071, 2416, 2087, 2377, 2023, 2175, 1923, 1576, 1661, 1881, 1537, 1561, 1569, 1782, 1556, 1288, 1762, 1402, 1378, 1379, 1597, 1032, 1033, 1459, 1135, 645, 656, 758, 686, 719, 1101, 956, 847, 653, 867, 846, 585, 691, 638, 856, 624, 585, 873, 426, 338, 654, 619, 333, 321, 553, 679, 30, 531, 589, 538, 407, 121, 676, 405, 395, 549, 663, 279, 788, 756, 815, 279, 368, 799, 604, 530, 531, 624, 614, 667, 855, 675, 488, 803, 727, 1017, 735, 1139, 844, 962, 738, 1359, 1052, 1324, 1059, 1345, 1197, 1404, 1414, 1438, 939, 1338, 1733, 1681, 1414, 2044, 2077, 1608, 1323, 1691, 1795, 1937, 2012, 1840, 1978, 2212, 2175, 2196, 2442, 2212, 2399, 2475, 2272, 2400, 2850, 2683, 2587, 2708, 2976, 2599, 2753, 3105, 3012, 3006, 2990, 2850, 2771, 3097, 3096, 3274, 2881, 3232, 3273, 3490, 3014, 3449, 3560, 3172, 3380, 3318, 3385, 3410, 3254, 3500, 3458, 3175, 3657, 3755, 3465, 3371, 3690, 3933, 3567, 3391, 3817, 3582, 3373, 3844, 3641, 3431, 3101, 3403, 3714, 3294, 3503, 3462, 3405, 3417, 3675, 3676, 3554, 3515, 3615, 3323, 3191, 3313, 3349, 3359, 2820, 3059, 3391, 2736, 2781, 3140, 2875, 2881, 2745, 3011, 2881, 2715, 2712, 2925, 2581, 2622, 2979, 2739, 2458, 2241, 2708, 2342, 2093, 2412, 2461, 2362, 2271, 2143, 2233, 2205, 2069, 2208, 2156, 1619, 1917, 2144, 1934, 1417, 1682, 1768, 1386, 1360, 1706, 1406, 946, 1389, 1379, 1094, 829, 1412, 906, 716, 933, 1353, 1233, 622, 893, 807, 969, 458, 859, 1046, 591, 860, 698, 769, 625, 604, 973, 628, 176, 1249, 756, 426, 214, 657, 467, 433, 537, 914, 449, 407, 609, 562, 325, 560, 739, 430, 166, 489, 842, 473, 663, 512, 702, 75, 423, 710, 761, 771, 688, 1084, 791, 771, 798, 1146, 562, 869, 901, 904, 596, 929, 1252, 1027, 770, 1468, 1365, 1275, 1314, 1355, 1102, 1107, 1633, 1477, 1613, 1340, 1764, 1500, 1774, 1666, 2079, 1920, 1864, 1924, 2254, 1756, 1771, 2321, 2282, 2065, 2152, 2527, 2306, 2325, 2302, 2578, 2640, 2600, 2532, 2907, 2425, 2773, 2631, 2694, 2631, 2875, 3311, 3071, 3114, 3316, 3153, 2955, 3226, 3322, 3225, 2875, 3246, 3011, 3201, 3047, 3553, 3427, 3237, 3549, 3421, 3552, 3029, 3503, 3718, 3603, 3245, 3666, 3706, 3427, 3491, 3767, 3662, 3251, 3372, 4095, 3804, 3190, 3693, 3746, 3522, 3451, 3498, 3503, 3245, 3478, 3552, 3358, 3420, 3656, 3294, 3149, 3106, 3616, 3294, 3303, 3129, 3330, 2890, 3170, 3104, 2930, 2799, 2532, 3070, 2958, 2750, 3051, 2886, 2821, 2606, 2710, 2410, 2601, 2366, 2627, 2287, 2285, 2366, 2462, 2194, 2234, 2399, 2349, 2471, 1852, 2064, 1822, 1804, 1737, 1533, 1520, 1576, 1900, 1492, 1360, 1422, 1511, 1565, 1245, 1404, 1354, 1466, 1091, 1476, 1202, 1090, 889, 1035, 941, 811, 904, 1295, 652, 533, 1159, 995, 349, 723, 882, 393, 448, 633, 882, 700, 453, 805, 641, 284, 292, 733, 240, 442, 312, 575, 507, 517, 252, 460, 360, 296, 749, 202, 390, 561, 665, 642, 197, 795, 563, 567, 455, 874, 791, 269, 647, 833, 639, 488, 1141, 949, 953, 688, 867, 987, 717, 1360, 1217, 1197, 924, 1170, 1287, 1153, 1303, 1417, 1275, 1061, 1409, 1706, 1535, 1409, 1587, 1781, 1658, 1642, 1935, 1844, 1858, 1848, 2143, 2026, 2026, 2415, 2368, 2169, 1928, 2519, 2728, 2094, 2263, 2584, 2623, 2493, 2605, 2749, 2724, 2742, 3278, 3002, 2744, 2976, 3018, 2761, 2878, 3187, 2963, 2898, 2987, 3341, 3193, 3135, 3263, 3592, 2993, 3442, 3653, 3497, 3378, 3424, 3460, 3519, 3434, 3530, 3811, 3479, 3391, 3493, 3597, 3356, 3729, 3731, 3445, 3466, 3528, 3237, 3584, 3168, 3716, 3504, 3186, 3511, 3417, 3469, 3360, 3561, 3718, 3383, 3144, 3774, 3395, 3511, 3172, 3620, 3483, 2932, 3273, 3458, 3223, 2955, 3224, 3116, 2728, 3059, 3008, 3174, 2819, 2702, 2929, 2673, 2445, 2839, 2679, 2729, 2600, 2511, 2503, 2230, 2131, 2625, 2386, 2239, 2204, 2427, 1949, 2113, 2426, 2025, 1541, 1818, 2073, 1920, 1414, 1738, 1792, 1545, 1607, 1500, 1440, 1422, 1437, 1557, 1424, 1128, 1378, 1242, 811, 814, 1212, 1037, 735, 1004, 937, 863, 715, 782, 560, 879, 709, 447, 671, 577, 612, 869, 412, 474, 646, 643, 389, 474, 799, 466, 279, 511, 614, 491, 442, 752, 566, 0, 376, 668, 492, 307, 115, 731, 416, 147, 482, 531, 540, 583, 972, 760, 275, 441, 1009, 904, 554, 927, 669, 397, 579, 960, 869, 751, 897};

#define BINS_COUNT 512
//const int bins[BINS_COUNT] = {0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18};
const int bins[BINS_COUNT] = {0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18};


volatile uint16_t sapling_time_micros;
volatile float32_t cycle_dt;

volatile uint16_t samples_buffer[1024*2];

volatile int state = STATE_FFT_DONE;

uint16_t * key_samples[2];
volatile int samplesBufferIndex = 1;

float32_t * key_magnitudes[2];
volatile int magnitudesBufferIndex = 0;

float32_t fft_input[1024 * 2];
float32_t fft_magnitudes[1024]; // twice long to calc derrivative - serio?2
float32_t fft_magnitudes_derivative[1024/2];
float32_t usable_magnitudes[512];
float32_t bounds_heights[19];

char *print_buffer[PRINT_BUFFER_SIZE];

float32_t maxMag;
uint32_t maxMagIndex;

static void mags_to_bounds() {
	for(int i = 0; i < 19; i++)
		bounds_heights[i] = 0;

	for(int i = 0; i < 512; i++) {
		if(usable_magnitudes[i] > 0.01)
			bounds_heights[bins[i]] += usable_magnitudes[i];
	}
}

static void calFFT() {
	for(int i = 1; i < 1024 * 2; i+=2)
		fft_input[i] = 0.0;

	for(int i = 0; i < 1024 * 2; i+=2)
		fft_input[i] = (2.0 * ADC_SAMPLES[i/2] / 4095.0) - 1.0;

	for(int i = 0; i < 1024; i++)
		fft_magnitudes[i] = 0.0;

	// 1024, 1024*2, 0, 1
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, fft_input, 0, 1);

	// 1024*2, 1024, 1024
	arm_cmplx_mag_f32(fft_input, fft_magnitudes, FFT_SAMPLES_COUNT);

	arm_max_f32(fft_magnitudes, FFT_SAMPLES_COUNT, &maxMag, &maxMagIndex);
	//efective magnitudes: fft_magnitudes.length / 2. For 1024 samples it is 512. Use this number in bounds
	//todo replace with more peaks.
	for(int i = 0; i < 512; i++)
		usable_magnitudes[i] = 2.0/1024 * fft_magnitudes[i];
}

void ASD_FFT_Init() {
	key_samples[0] = (uint16_t *)(&ADC_SAMPLES[0]);
	key_samples[1] = (uint16_t *)(&ADC_SAMPLES[1024]);

	key_magnitudes[0] = (float32_t *)(&fft_magnitudes[0]);
	key_magnitudes[1] = (float32_t *)(&fft_magnitudes[1024]);

//	for(int i = 0; i < 1024*2; i++)
//		samples_buffer[i] = ADC_SAMPLES[i];

//	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)samples_buffer, FFT_SAMPLES_COUNT * 2);
	HAL_TIM_Base_Start(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);

	// https://deepbluembedded.com/stm32-dac-sine-wave-generation-stm32-dac-dma-timer-example/
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)DAC_SINE_SAMPLES, DAC_SINE_SAMPLES_COUNT, DAC_ALIGN_12B_R);
    HAL_TIM_Base_Start(&htim2);

    ASD_set_frequency(1000);
}

void ASD_Next_Batch_Aquired() {
	sapling_time_micros = __HAL_TIM_GET_COUNTER(&htim6);
	cycle_dt = sapling_time_micros / (float32_t)(1e6);
	__HAL_TIM_SET_COUNTER(&htim6, 0);

	if(state == STATE_FFT_DONE) {
		samplesBufferIndex ^= 1;
		magnitudesBufferIndex ^= 1;
		state = STATE_SAMPL_DONE;
	}
}

void ASD_set_frequency(float32_t freq) {
	if(freq < 0) {
		//todo switch channel
	} else {
		if(freq > DAC_FREQ_D_SMP_CNT)
			freq = DAC_FREQ_D_SMP_CNT;
		uint32_t arr = (uint32_t)(DAC_FREQ_D_SMP_CNT/freq);
		__HAL_TIM_SET_AUTORELOAD(&htim2, arr);
	}
}

void ASD_update() {
}

void ASD_Print_Results() {
	calFFT();
	mags_to_bounds();

	float32_t sapling_time_millis = 46.5455;//sapling_time_micros/1000.0;
	float32_t sampling_freq_kHz = 44000;//1.0/(sapling_time_millis/FFT_SAMPLES_COUNT); //todo lol
//	int bidx = magnitudesBufferIndex;


	printf("\nSampling time: %.2f us. Sampling frequency: %.2f kHz, idx %d\n", sapling_time_millis, sampling_freq_kHz, samplesBufferIndex);
//	printf("\nMAGNITUDES CURRENT:\n");
//	for(int i = 0; i < FFT_SAMPLES_COUNT/2; i++)
//		printf("%.3f, ", *(key_magnitudes[bidx] + i));
//
//	printf("\n\nMAGNITUDES LAST:\n");
//	for(int i = 0; i < FFT_SAMPLES_COUNT/2; i++)
//		printf("%.3f, ", *(key_magnitudes[bidx^1] + i));
//
//	printf("\n\nMAGNITUDES DERIVATIVE:\n");
//	for(int i = 0; i < FFT_SAMPLES_COUNT/2; i++)
//		printf("%.4f, ", fft_magnitudes_derivative[i]);


//	printf("\n\nLAST mmmm:\n");
//	for(int i = 0; i < 512; i++)
//		printf("%.3f, ", usable_magnitudes[i]);
//
	printf("\n\nLAST bbbb:\n");
	for(int i = 0; i < 19; i++)
		printf("%.3f, ", bounds_heights[i]);

//	printf("\n\nLAST SAMPLES:\n");
//	for(int i = 0; i < FFT_SAMPLES_COUNT*2; i++)
//		printf("%.3f, ", fft_input[i]);

//		printf("\n\nLAST real:\n");
//		for(int i = 0; i < 1024 * 2; i+=2)
//			printf("%.3f, ", fft_input[i]);
//
//		printf("\n\nLAST imag:\n");
//		for(int i = 1; i < 1024 * 2; i+=2)
//			printf("%.3f, ", fft_input[i]);


//		printf("\n\nLAST mmmm:\n");
//		for(int i = 0; i < FFT_SAMPLES_COUNT; i++)
//			printf("%.3f, ", fft_magnitudes[i]);


//	printf("v: %.3f i: %lu f: %.3f kHz.\n", maxMag, maxMagIndex, maxMagIndex * sampling_freq_kHz);
//	sprintf(print_buffer, "Sampling time: %.2f us. Sampling frequency: %.2f kHz, idx %d\n", sapling_time_millis, sampling_freq_kHz, samplesBufferIndex);

//	printf(print_buffer);
}










//todo :
// sampling na 2 bufory
// jak koniec bufora 0 to uzupelnia pierwszy
// fft liczy sie na próbkach z 1 pozniej z 0
//magnitudy tez na zmiane
//animacje licze z ostatnich magnitud, startowane od przerwania z DMA


//	if(state == STATE_SAMPL_DONE) {
////		uint16_t * startSamplesBuffer = key_samples[samplesBufferIndex];
////		float32_t * startMagnitudesBuffer = key_magnitudes[magnitudesBufferIndex];
//
//		for(int i = 0; i < FFT_SAMPLES_COUNT * 2; i+=2)
//			fft_input[i] = (2.0 * ADC_SAMPLES[i/2] / 4095.0) - 1.0;
//
//		for(int i = 1; i < FFT_SAMPLES_COUNT * 2; i+=2)
//			fft_input[i] = 0.0;
//
//		for(int i = 0; i < FFT_SAMPLES_COUNT; i++)
//			fft_magnitudes[i] = 0.0;
//
//
//		// 1024, 1024*2, 0, 1
//		arm_cfft_f32(&arm_cfft_sR_f32_len1024, fft_input, 0, 1);
//
//		// 1024*2, 1024, 1024
//		arm_cmplx_mag_f32(fft_input, fft_magnitudes, FFT_SAMPLES_COUNT);
//
////		for(int i = 0; i < FFT_SAMPLES_COUNT/2; i++)
////			*(startMagnitudesBuffer + i) = 2.0/(FFT_SAMPLES_COUNT/2) * *(startMagnitudesBuffer + i);
////
////		int previous_magnitudesBufferIndex = magnitudesBufferIndex ^ 1;
////		for(int i = 0; i < FFT_SAMPLES_COUNT/2; i++)
////			fft_magnitudes_derivative[i] = (*(key_magnitudes[magnitudesBufferIndex] + i) - *(key_magnitudes[previous_magnitudesBufferIndex] + i)) / cycle_dt;
////
//		arm_max_f32(fft_magnitudes, FFT_SAMPLES_COUNT, &maxMag, &maxMagIndex);
//
//		state = STATE_FFT_DONE;
//	}


//void ASD_update() {
//	if(state == STATE_SAMPL_DONE) {
//
//		uint16_t * startSamplesBuffer = key_samples[samplesBufferIndex];
//		float32_t * startMagnitudesBuffer = key_magnitudes[magnitudesBufferIndex];
//
////		for(int i = 0; i < FFT_SAMPLES_COUNT * 2; i++)
////			fft_input[i] = (i%2 == 0 ? (2.0*startSamplesBuffer[i/2]/4095.0) - 1.0: 0.0);
//
//		for(int i = 0; i < FFT_SAMPLES_COUNT * 2; i+=2)
//			fft_input[i] = 2.0 * *(startSamplesBuffer + i/2)/4095.0 - 1.0;
//
//		for(int i = 1; i < FFT_SAMPLES_COUNT * 2; i+=2)
//			fft_input[i] = 0.0;
//
//
//		arm_cmplx_mag_f32(fft_input, startMagnitudesBuffer, FFT_SAMPLES_COUNT);
//
//		for(int i = 0; i < FFT_SAMPLES_COUNT/2; i++)
//			*(startMagnitudesBuffer + i) = 2.0/(FFT_SAMPLES_COUNT/2) * *(startMagnitudesBuffer + i);
//
//		int previous_magnitudesBufferIndex = magnitudesBufferIndex ^ 1;
//		for(int i = 0; i < FFT_SAMPLES_COUNT/2; i++)
//			fft_magnitudes_derivative[i] = (*(key_magnitudes[magnitudesBufferIndex] + i) - *(key_magnitudes[previous_magnitudesBufferIndex] + i)) / cycle_dt;
//
//		arm_max_f32(startMagnitudesBuffer, FFT_SAMPLES_COUNT, &maxMag, &maxMagIndex);
//
//		state = STATE_FFT_DONE;
//	}
//}











////	if(state == STATE_SAMPL_DONE) {
//	//		uint16_t * startSamplesBuffer = key_samples[samplesBufferIndex];
//	//		float32_t * startMagnitudesBuffer = key_magnitudes[magnitudesBufferIndex];
//
//			for(int i = 0; i < FFT_SAMPLES_COUNT * 2; i+=2)
//				fft_input[i] = (2.0 * ADC_SAMPLES[i/2] / 4095.0) - 1.0;
//
//			for(int i = 1; i < FFT_SAMPLES_COUNT * 2; i+=2)
//				fft_input[i] = 0.0;
//
//			for(int i = 0; i < FFT_SAMPLES_COUNT; i++)
//				fft_magnitudes[i] = 0.0;
//
//
//			// 1024, 1024*2, 0, 1
//			arm_cfft_f32(&arm_cfft_sR_f32_len1024, fft_input, 0, 1);
//
//			// 1024*2, 1024, 1024
//			arm_cmplx_mag_f32(fft_input, fft_magnitudes, FFT_SAMPLES_COUNT);
//
//	//		for(int i = 0; i < FFT_SAMPLES_COUNT/2; i++)
//	//			*(startMagnitudesBuffer + i) = 2.0/(FFT_SAMPLES_COUNT/2) * *(startMagnitudesBuffer + i);
//	//
//	//		int previous_magnitudesBufferIndex = magnitudesBufferIndex ^ 1;
//	//		for(int i = 0; i < FFT_SAMPLES_COUNT/2; i++)
//	//			fft_magnitudes_derivative[i] = (*(key_magnitudes[magnitudesBufferIndex] + i) - *(key_magnitudes[previous_magnitudesBufferIndex] + i)) / cycle_dt;
//	//
//			arm_max_f32(fft_magnitudes, FFT_SAMPLES_COUNT, &maxMag, &maxMagIndex);
//
//			state = STATE_FFT_DONE;
////		}
