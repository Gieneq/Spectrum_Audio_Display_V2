#include "ASD_FFT.h"

/*
 * ADC sampels buffer. Shound not be any concurrency - doublebuffering protects.
 */
volatile uint16_t _samplesBuffer_hole[FFT_SAMPLES_COUNT*2];
volatile uint16_t _samplesBuffer[FFT_SAMPLES_COUNT*2];

const int BINS_IDXS[BINS_COUNT] = {0, 0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18};
//todo 8int
/*
 * ADC samples used to test. In this signal there are 2 spikes at 210 Hz and 12kHz. First lobe is much higher. There should he high spike at 2nd band and lower spike at 7th bound.
 */
const uint16_t ADC_SAMPLES[] = {2279, 2134, 1998, 1864, 2429, 2022, 2456, 2150, 2582, 2444, 2555, 2211, 2672, 2510, 2689, 2610, 2827, 2527, 2741, 3085, 2769, 2956, 3107, 3233, 3135, 2830, 3171, 3112, 3014, 3199, 3263, 3240, 3028, 3181, 3384, 3313, 3070, 3521, 3792, 3438, 3345, 3477, 3417, 3609, 3522, 3579, 3520, 3724, 3650, 3764, 3488, 3424, 3526, 3551, 3376, 3647, 3833, 3647, 3445, 3750, 3522, 3587, 3494, 3579, 3588, 3290, 3609, 3801, 3689, 3022, 3215, 3368, 3213, 3330, 3439, 2956, 2995, 3290, 3319, 3173, 2892, 3084, 3141, 2907, 2871, 3043, 2788, 2714, 2787, 3052, 2827, 2534, 2627, 2577, 2465, 2401, 2515, 2433, 2092, 2400, 2331, 2347, 2079, 2285, 2013, 1929, 2004, 1921, 1884, 1689, 1580, 1945, 1787, 1385, 1748, 1482, 1402, 1150, 1749, 1502, 1199, 1195, 1620, 1492, 771, 1429, 1484, 1019, 781, 1284, 994, 701, 725, 1119, 931, 589, 959, 710, 751, 644, 807, 702, 635, 749, 849, 577, 456, 746, 707, 533, 403, 291, 719, 694, 573, 638, 435, 341, 584, 445, 309, 273, 692, 520, 455, 514, 855, 554, 775, 387, 627, 651, 952, 770, 740, 527, 941, 870, 849, 627, 732, 1038, 866, 1052, 1091, 951, 972, 1109, 1303, 1091, 1222, 1362, 1669, 1356, 1361, 1274, 1561, 1381, 1635, 1866, 1494, 1630, 1684, 2148, 1458, 1470, 1755, 1821, 1637, 2306, 2154, 1849, 2175, 2182, 2161, 2299, 2338, 2443, 2674, 2328, 2751, 2776, 2786, 2510, 2570, 3207, 2557, 2683, 2868, 2887, 2798, 2981, 3239, 3253, 2898, 2984, 3057, 2936, 2846, 3480, 3210, 3071, 3297, 3260, 3171, 3333, 3569, 3459, 3592, 3166, 3552, 3489, 2915, 3804, 3727, 3326, 3713, 3718, 3733, 3347, 3493, 3467, 3727, 3352, 3579, 3891, 3551, 3445, 3662, 3531, 3529, 3659, 3748, 3657, 3176, 3312, 3358, 3553, 3209, 3662, 3338, 3135, 3224, 3546, 3290, 3090, 3182, 3327, 2902, 2957, 3104, 3122, 2939, 2756, 3032, 2865, 2741, 2909, 2754, 2755, 2844, 2482, 2570, 2288, 2370, 2839, 2452, 2104, 2412, 2332, 2355, 2088, 2431, 2104, 2392, 2041, 2191, 1941, 1597, 1681, 1900, 1559, 1583, 1591, 1801, 1577, 1312, 1782, 1424, 1401, 1402, 1618, 1058, 1059, 1482, 1160, 674, 685, 786, 715, 748, 1126, 983, 875, 683, 895, 873, 615, 720, 668, 884, 654, 614, 900, 457, 370, 683, 649, 365, 353, 583, 707, 64, 562, 619, 569, 438, 155, 705, 436, 427, 579, 692, 311, 816, 784, 842, 312, 400, 827, 634, 560, 561, 653, 644, 696, 883, 704, 519, 830, 756, 1043, 764, 1164, 871, 989, 767, 1382, 1078, 1348, 1085, 1368, 1221, 1427, 1437, 1460, 966, 1362, 1753, 1702, 1437, 2062, 2094, 1629, 1347, 1712, 1814, 1955, 2030, 1859, 1996, 2228, 2191, 2212, 2456, 2227, 2413, 2489, 2287, 2415, 2861, 2695, 2600, 2720, 2986, 2612, 2764, 3113, 3022, 3015, 3000, 2861, 2782, 3106, 3104, 3280, 2892, 3239, 3280, 3495, 3023, 3455, 3564, 3180, 3386, 3324, 3391, 3416, 3261, 3505, 3463, 3183, 3661, 3758, 3470, 3378, 3693, 3935, 3571, 3397, 3819, 3587, 3380, 3846, 3645, 3437, 3109, 3409, 3717, 3300, 3508, 3468, 3411, 3422, 3678, 3679, 3558, 3520, 3619, 3329, 3199, 3319, 3355, 3365, 2831, 3068, 3397, 2747, 2792, 3148, 2886, 2891, 2757, 3020, 2891, 2726, 2724, 2935, 2594, 2634, 2989, 2750, 2472, 2257, 2720, 2357, 2110, 2426, 2475, 2377, 2286, 2159, 2249, 2221, 2087, 2224, 2173, 1640, 1936, 2160, 1953, 1440, 1702, 1788, 1409, 1383, 1727, 1429, 972, 1412, 1402, 1120, 856, 1435, 933, 745, 959, 1376, 1258, 651, 920, 835, 996, 489, 886, 1071, 621, 887, 727, 797, 654, 633, 999, 657, 209, 1273, 784, 457, 247, 686, 497, 464, 567, 941, 480, 439, 638, 592, 357, 590, 767, 461, 199, 520, 870, 504, 692, 542, 731, 109, 454, 739, 789, 799, 717, 1110, 819, 799, 826, 1171, 592, 896, 928, 931, 625, 956, 1276, 1053, 798, 1490, 1388, 1298, 1337, 1378, 1127, 1132, 1654, 1499, 1634, 1363, 1784, 1522, 1793, 1687, 2096, 1939, 1883, 1942, 2269, 1775, 1791, 2336, 2297, 2082, 2168, 2540, 2321, 2340, 2317, 2591, 2653, 2613, 2545, 2917, 2439, 2784, 2643, 2706, 2643, 2885, 3318, 3080, 3122, 3322, 3161, 2964, 3234, 3329, 3232, 2886, 3253, 3020, 3208, 3056, 3557, 3432, 3244, 3553, 3426, 3556, 3038, 3508, 3722, 3607, 3252, 3669, 3710, 3432, 3496, 3770, 3665, 3258, 3378, 4095, 3806, 3198, 3696, 3749, 3527, 3456, 3503, 3508, 3252, 3484, 3557, 3365, 3425, 3659, 3301, 3157, 3115, 3620, 3301, 3309, 3137, 3336, 2900, 3178, 3112, 2940, 2810, 2545, 3079, 2968, 2762, 3060, 2896, 2831, 2618, 2722, 2424, 2613, 2381, 2639, 2302, 2301, 2381, 2475, 2210, 2250, 2414, 2364, 2484, 1871, 2081, 1841, 1823, 1757, 1555, 1542, 1598, 1919, 1514, 1383, 1444, 1533, 1587, 1269, 1427, 1377, 1488, 1117, 1498, 1227, 1115, 917, 1061, 967, 839, 931, 1319, 681, 563, 1183, 1021, 381, 752, 909, 424, 479, 663, 909, 729, 484, 833, 670, 316, 324, 762, 273, 473, 344, 604, 538, 548, 284, 491, 391, 328, 777, 235, 421, 591, 694, 671, 230, 823, 593, 597, 486, 901, 819, 302, 676, 860, 668, 518, 1166, 976, 979, 717, 895, 1014, 745, 1383, 1241, 1221, 951, 1195, 1311, 1178, 1326, 1440, 1299, 1087, 1432, 1726, 1557, 1431, 1608, 1800, 1678, 1663, 1954, 1863, 1877, 1867, 2160, 2043, 2043, 2430, 2383, 2185, 1947, 2532, 2740, 2111, 2278, 2597, 2635, 2506, 2618, 2761, 2735, 2754, 3285, 3011, 2755, 2985, 3027, 2773, 2888, 3194, 2973, 2908, 2997, 3348, 3201, 3144, 3270, 3596, 3003, 3447, 3656, 3502, 3384, 3430, 3465, 3524, 3440, 3534, 3813, 3484, 3397, 3498, 3601, 3362, 3732, 3734, 3450, 3471, 3532, 3244, 3588, 3176, 3719, 3509, 3194, 3516, 3423, 3475, 3366, 3565, 3721, 3389, 3152, 3776, 3401, 3516, 3179, 3624, 3488, 2942, 3280, 3464, 3230, 2965, 3231, 3124, 2740, 3068, 3017, 3181, 2830, 2714, 2939, 2685, 2459, 2850, 2691, 2740, 2612, 2525, 2517, 2246, 2148, 2637, 2400, 2255, 2220, 2441, 1968, 2130, 2441, 2042, 1563, 1837, 2090, 1939, 1437, 1758, 1811, 1566, 1628, 1522, 1463, 1445, 1460, 1579, 1446, 1154, 1401, 1266, 838, 842, 1237, 1063, 764, 1030, 964, 890, 743, 810, 590, 906, 738, 478, 700, 607, 641, 896, 444, 505, 675, 672, 420, 505, 827, 496, 311, 542, 644, 521, 473, 780, 596, 34, 407, 697, 523, 339, 149, 759, 447, 180, 513, 561, 570, 612, 998, 788, 308, 472, 1035, 931, 584, 954, 698, 428, 608, 986, 896, 779, 924, 1289, 1245, 971, 1536, 1199, 1022, 1235, 1383, 1562, 1130, 1624, 1646, 1857, 1340, 1646, 1777, 1233, 1738, 1986, 1879, 1476, 1673, 2197, 2139, 2153, 2039, 2097, 2028, 1845, 2325, 2495, 2465, 2454, 2858, 2519, 2433, 2642, 2773, 2516, 2607, 2791, 2876, 2683, 2644, 3024, 2772, 2530, 3175, 3407, 3334, 3276, 3157, 3405, 3232, 2936, 3552, 3347, 3206, 3471, 3492, 3523, 3265, 3538, 3491, 3354, 3209, 3858, 3498, 3466, 3641, 3624, 3375, 3483, 3718, 3779, 3463, 3541, 4017, 3320, 3211, 3688, 3628, 3150, 3398, 3549, 3723, 3247, 3640, 3686, 3372, 3293, 3558, 3151, 3301, 3203, 3735, 3232, 3291, 2855, 3488, 3181, 2974, 3184, 3163, 3002, 2915, 2848, 2961, 3100, 2878, 3029, 2683, 2640, 2822, 2746, 2645, 2362, 2662, 2620, 2263, 2224, 2604, 2128, 2068, 2187, 2284, 1958, 1938, 2291, 2315, 1749, 1990, 1961, 1791, 1807, 1819, 1674, 1411, 1417, 1688, 1682, 1104, 1263, 1390, 1028, 1362, 1335, 1626, 846, 1258, 1137, 1050, 731, 854, 915, 923, 561, 917, 956, 799, 718, 948, 856, 556, 743, 668, 484, 778, 690, 600, 673, 457, 591, 361, 498, 355, 583, 564, 392, 570, 582, 558, 758, 557, 636, 655, 683, 572, 425, 314, 500, 590, 509, 428, 891, 698, 443, 812, 899, 719, 766, 943, 898, 854, 820, 1472, 1128, 974, 1179, 1179, 1208, 950, 1078, 1190, 1163, 915, 1448, 1249, 1317, 1285, 1880, 1559, 1194, 1924, 1696, 1433, 1465, 1976, 2068, 1600, 1733, 1909, 2164, 2140, 2099, 2314, 2045, 2115, 2539, 2409, 2242, 2343, 2709, 2390, 2388, 2680, 2538, 2487, 2560, 2886, 2645, 2478, 3100, 3218, 3020, 3104, 3147, 3137, 3027, 2732, 3106, 3325, 3050, 3030, 3506, 3391, 3270, 3410, 3343, 3278, 3381, 3503, 3573, 3352, 3522, 3327, 3622, 3637, 3544, 3422, 3523, 3394, 3545, 3787, 3197, 3672, 3522, 3741, 3497, 3597, 3687, 3515, 3577, 3790, 3640, 3276, 3589, 3423, 3567, 3433, 3716, 3425, 3291, 3405, 3521, 3286, 3178, 3265, 3531, 3058, 3080, 3264, 3336, 2944, 2973, 3130, 3014, 2778, 2841, 3437, 2641, 2455, 2694, 2699, 2536, 2745, 2963, 2602, 1944, 2493, 2341, 2225, 1985, 2403, 2229, 2166, 2108, 2174, 2081, 1969, 1877, 2180, 1796, 1699, 1957, 2026, 1626, 1544, 1823, 1336, 1586, 1241, 1692, 1231, 1258, 1344, 1401, 962, 748, 1326, 1039, 801, 906, 1439, 818, 829, 792, 1206, 627, 319, 1328, 622, 772, 812, 929, 578, 526, 889, 671, 508, 630, 709, 523, 606, 578, 650, 349, 212, 722, 761, 50, 322, 788, 918, 686, 658, 883, 405, 518, 444, 593, 510, 841, 862, 711, 467, 463, 931, 613, 631, 705, 919, 461, 835, 1211, 1083, 1104, 1014, 1227, 1068, 793, 1516, 1408, 1025, 996, 1484, 1471, 1206, 1406, 1543, 1419, 1570, 1846, 1478, 1542, 1414, 1661, 1904, 1536, 1379, 2158, 2107, 2172, 2068, 2429, 1620, 1940, 2447, 2389, 2370, 2511, 2548, 2644, 2463, 2887, 2576, 2557, 2520, 2973, 2760, 2601, 2627, 3068, 3035, 2960, 2602, 2884, 3243, 2974, 3234, 3371, 3059, 3113, 3359, 3514, 2942, 3601, 3411, 3209, 3590, 3449, 3599, 3239, 3244, 3605, 3629, 3338, 3684, 3672, 3428, 3398, 3710, 3287, 3339, 3285, 3755, 3572, 3298, 3761, 3728, 3474, 3399, 3740, 3723, 3254, 3369, 3814, 3066, 2908, 3235, 3554, 3298, 3361, 3496, 3600, 3386, 3447, 3216, 3226, 2911, 3159, 3080, 2974, 3055, 3171, 2845, 2563, 2794, 2905, 2911, 2607, 2809, 2806, 2725, 2798, 2793, 2550, 2565, 2525, 2500, 2480, 2216, 2142, 2445, 2118, 1774, 1906, 2114, 1957, 2051, 1855, 1770, 1784, 1623, 1859, 1602, 1699, 1360, 1618, 1667, 1371, 1527, 1485, 1084, 1560, 1458, 864, 1114, 1060, 1296, 662, 758, 978, 801, 997, 983, 1033, 892, 625, 838, 674, 704, 962, 880, 529, 428, 540, 838, 315, 456, 524, 304, 0, 394, 707, 422, 335, 423, 474, 220, 448, 952, 524, 144, 705, 516, 567, 327, 640, 1198, 339, 411, 796, 656, 421, 549, 917, 819, 435, 654, 1167, 463, 852, 1061, 758, 880, 778, 965, 758, 1037, 1098, 1403, 918, 1208, 1590, 1305, 991, 1304, 1742, 1510, 1284, 1341, 1795, 1747, 1827, 1908, 1761, 1521, 1750, 1783, 2213, 1832, 2469, 2172, 1750, 2361, 2212, 2226, 2397, 2564, 2227, 2387, 2168, 2683, 2955, 2409, 2792, 2685, 3105, 2492, 2739, 3046, 2630, 3023, 2881, 3208, 2720, 3001, 3239, 3117, 3088, 3024, 3609, 3240, 2713, 3696, 3516, 3476, 3267, 3191, 3397, 3097, 3448, 3548, 3474, 3090, 3603, 3568, 3514, 3199, 3622, 3850, 3225, 3673, 3917, 3517, 3573, 3800, 3910, 3376, 3442, 3796, 3453, 3369, 3394, 3282, 3481, 3578, 3465, 3549, 3216, 3183, 3518, 3541, 3497, 3410, 3261, 2967, 3260, 3300, 3160, 2828, 2866, 3366, 3043, 2601, 3064, 3092, 2767, 2769, 2732, 2999, 2360, 2431, 2539, 2547, 2257, 2425, 2589, 2434, 2230, 2424, 2618, 2055, 1859, 2405, 2398, 1905, 2111, 1987, 1876, 1803, 1940, 1787, 1843, 1608, 1901, 1681, 1514, 1632, 1564, 1488, 1554, 1710, 1514, 1384, 919, 1529, 1181, 664, 1079, 1320, 835, 1109, 1209, 809, 897, 764, 856, 769, 529, 538, 784, 741, 737, 944, 647, 468, 372, 868, 349, 186, 438, 716, 426, 377, 596, 654, 225, 364, 726, 586, 519, 393, 804, 702, 368, 662, 700, 529, 553, 956, 729, 606, 695, 656, 709, 534, 718, 736, 657, 635, 1291, 1156, 706, 1039, 1291, 926, 1174, 1290, 1202, 747, 946, 1403, 1230, 1139, 1214, 1565, 1304, 1083, 1534, 1575, 1237, 1770, 1807, 1717, 1732, 1802, 2129, 1636, 1653, 2164, 2388, 1978, 2085, 2194, 2265, 2012, 2293, 2624, 2058, 2344, 2455, 2555, 2640, 2587, 2949, 2481, 2534, 2720, 2890, 2892, 2903, 2856, 2948, 2707, 3143, 3144, 3144, 2946, 3032, 3418, 3253, 3270, 3340, 3388, 3136, 3510, 3681, 3445, 3375, 3356, 3929, 3344, 3295, 3531, 3893, 3434, 3620, 3667, 3408, 3522, 3463, 3511, 3455, 3519, 3912, 3459, 3099, 3605, 3723, 3486, 3432, 3619, 3939, 3418, 3522, 3462, 3468, 3361, 3137, 3309, 3537, 2870, 3314, 3373, 3143, 2871, 2956, 3169, 2828, 2942, 3209, 2951, 2670, 2994, 2948, 2685, 2651, 2923, 3195, 2847, 2398, 2569, 2643, 2481, 2483, 2944, 2552, 2483, 2345, 2259, 1955, 2089, 2090, 2044, 1834, 2151, 2039, 1656, 1661, 1935, 1979, 1475, 1704, 1995, 1717, 1440, 1443, 1526, 1072, 1338, 1371, 1441, 1223, 1019, 1479, 1206, 1186, 1098, 1237, 917, 1056, 697, 939, 711, 527, 833, 499, 640, 522, 921, 607, 401, 493, 640, 543, 492, 820, 487, 646, 504, 553, 679, 583, 578, 546, 524, 279, 781, 330, 337, 507, 847};

/*
 * Double buffering keypoints and indices.
 */
uint16_t* _keySamples[2];
int _samplesBufferIndex = 1; //0 'done' 1 is filling
uint16_t* _selectedSamplesBuffer;

float32_t* _keyMagnitudes[2];
int _magnitudesBufferIndex = 0; // shifted - 0 input is done, 1 input is filling - mags are calculated using 0.
float32_t* _selectedMagnitudes;

float32_t mean;
/*
 * FFT arrays and data.
 */

float32_t _processingSamples[FFT_SAMPLES_COUNT * 2];
float32_t _magnitudes[FFT_SAMPLES_COUNT * 2]; // twice long to calc derrivative - serio?2
float32_t _usableMagnitudes[BINS_COUNT];

#define AVERAGING_COUNT 1
float32_t _boundsHeightsAveraging[BANDS_COUNT * AVERAGING_COUNT];
uint16_t _currentAveragingIndex;

float32_t _boundsMaxHeight;
uint32_t _boundsMaxHeightIndex;

/*
 * Bonds dynamics.
 */
float32_t bounds_last_heights[BANDS_COUNT];
float32_t bounds_heights[BANDS_COUNT];
float32_t bounds_last_velocity[BANDS_COUNT];
float32_t bounds_velocity[BANDS_COUNT];
float32_t bounds_acceleration[BANDS_COUNT];

#define IDLE_SUM_THRESHOLD 0.2

void ASD_FFT_init() {
	/* Key points used in double buffering */
	_keySamples[0] = (uint16_t *)(&_samplesBuffer[0]);
	_keySamples[1] = (uint16_t *)(&_samplesBuffer[FFT_SAMPLES_COUNT]);
	_samplesBufferIndex = 1;

	_keyMagnitudes[0] = (float32_t *)(&_magnitudes[0]);
	_keyMagnitudes[1] = (float32_t *)(&_magnitudes[FFT_SAMPLES_COUNT]);
	_magnitudesBufferIndex = 0;

	/* Preset samples of test signal. 2x1024 samples for 1024FFT feed */
	for(int i = 0; i < 2048; i++)
		_samplesBuffer[i] = ADC_SAMPLES[i];

	/* Use _samplesBuffer_hole to use test data */
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)_samplesBuffer, FFT_SAMPLES_COUNT * 2);
}


void ASD_FFT_toggleBuffers() {
	/* Toggle buffers */
	_samplesBufferIndex ^= 1;
	_selectedSamplesBuffer = _keySamples[_samplesBufferIndex];

	_magnitudesBufferIndex ^= 1;
	_selectedMagnitudes = _keyMagnitudes[_magnitudesBufferIndex];
}

float32_t* ASD_FFT_evalFFT(float32_t* boundHeights) {

	/* Image part */
	for(int i = 1; i < FFT_SAMPLES_COUNT * 2; i+=2)
		_processingSamples[i] = 0.0;

	/* Real part */
	mean = 0.0;
	for(int i = 0; i < FFT_SAMPLES_COUNT * 2; i+=2) {
		float32_t smple = (float32_t)(_selectedSamplesBuffer[i/2]) / 2048.0 ;
		_processingSamples[i] = smple;
		mean += smple;
	}
	mean /= FFT_SAMPLES_COUNT;

	for(int i = 0; i < FFT_SAMPLES_COUNT * 2; i+=2)
		_processingSamples[i] -= mean;

	/* Magnitudes */
	for(int i = 0; i < FFT_SAMPLES_COUNT; i++)
		_selectedMagnitudes[i] = 0.0;

	// 1024, 1024*2, 0, 1
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, _processingSamples, 0, 1);

	// 1024*2, 1024, 1024
	arm_cmplx_mag_f32(_processingSamples, _selectedMagnitudes, FFT_SAMPLES_COUNT);

	arm_max_f32(_selectedMagnitudes, FFT_SAMPLES_COUNT, &_boundsMaxHeight, &_boundsMaxHeightIndex);
	//efective magnitudes: fft_magnitudes.length / 2. For 1024 samples it is 512. Use this number in bounds
	for(int i = 0; i < BINS_COUNT; i++)
		_usableMagnitudes[i] = 2.0/FFT_SAMPLES_COUNT * _selectedMagnitudes[i];

	//rodo evaerage filtering
	_currentAveragingIndex++;
	if(_currentAveragingIndex >= AVERAGING_COUNT)
		_currentAveragingIndex = 0;

	for(int i = 0; i < BANDS_COUNT; i++)
		_boundsHeightsAveraging[i + BANDS_COUNT * _currentAveragingIndex] = 0;

	for(int i = 0; i < BINS_COUNT; i++) {
		/* Nosie removal, 0.01 should be fine */
		float32_t threshold = 0.005;//0.075*(BINS_COUNT-i-1)/BINS_COUNT;
		if(_usableMagnitudes[i] > threshold)
			_boundsHeightsAveraging[BINS_IDXS[i] + BANDS_COUNT * _currentAveragingIndex] += _usableMagnitudes[i];
	}

	float32_t average = 0.0;
	for(int i = 0; i < BANDS_COUNT; i++) {
		average = 0.0;
		for(int j = 0; j < AVERAGING_COUNT; j++)
			average += _boundsHeightsAveraging[i + BANDS_COUNT * j];
		boundHeights[i] = average / AVERAGING_COUNT;
	}

	return boundHeights;
}

void ASD_FFT_evalDynamics(float32_t* boundHeights, bounds_t* bounds, float32_t dts) {
		//current ACCELERATION evaluated on previous values
		for(int i = 0; i < BANDS_COUNT; i++)
			bounds_acceleration[i] = (bounds_velocity[i] - bounds_last_velocity[i]) / dts;

		//current VELOCITY evaluated on previous values and save discarded as last
		for(int i = 0; i < BANDS_COUNT; i++) {
			bounds_last_velocity[i] = bounds_velocity[i];
			bounds_velocity[i] = (boundHeights[i] - bounds_last_heights[i]) / dts;
		}

		//current HEIGHT(POSITION) and save discarded as last
		for(int i = 0; i < BANDS_COUNT; i++) {
			bounds_last_heights[i] = bounds_heights[i];
			bounds_heights[i] = 0;
		}

		float boundsSum = 0;
		for(int i = 0; i < BANDS_COUNT; i++) {
			bounds->heights[i] = boundHeights[i];
			boundsSum += bounds->heights[i];
			bounds->velocities[i] = bounds_velocity[i];
			bounds->accelerations[i] = bounds_acceleration[i];
		}
		bounds->heightsSum = boundsSum;
		bounds->isIdle = boundsSum < IDLE_SUM_THRESHOLD;

		bounds->dt_sec = dts;
}


void ASD_FFT_printDebug() {
//	int b_in_idx = samplesBufferIndex;
//	int b_mag_idx = magnitudesBufferIndex;
//
//	//freeze state
//	volatile uint16_t samples_buffer_print[FFT_SAMPLES_COUNT];
//	for(int i = 0; i < FFT_SAMPLES_COUNT; i++)
//		samples_buffer_print[i] = *(key_samples[b_in_idx] + i);
//
//	float32_t real_print[FFT_SAMPLES_COUNT];
//	float32_t imag_print[FFT_SAMPLES_COUNT];
//	for(int i = 0; i < FFT_SAMPLES_COUNT; i++){
//		real_print[i] = fft_input[i*2];
//		imag_print[i] = fft_input[i*2 + 1];
//	}
//
//	float32_t usable_magnitudes_print[BINS_COUNT];
//	for(int i = 0; i < BINS_COUNT; i++)
//		usable_magnitudes_print[i] = usable_magnitudes[i];
//
//	//print results
//	printf("\n\n\n\nSTART\n");
//	printf("\n\nSampling time o 1024 samples: %.2f ms. Sampling frequency: %.2f kHz, s_idx %d, m_idx %d\n", sampling_time_micros/1000.0, sampling_frequency, b_in_idx, b_mag_idx);
//	for(int i = 0; i < FFT_SAMPLES_COUNT; i++)
//		printf("%d, ", samples_buffer_print[i]);
//
//	printf("\n\nReal part, count: 1024\n");
//	for(int i = 0; i < FFT_SAMPLES_COUNT; i++)
//		printf("%.3f, ", real_print[i]);
//
//	printf("\n\nImaginary part, count: 1024\n");
//	for(int i = 0; i < FFT_SAMPLES_COUNT; i++)
//		printf("%.3f, ", imag_print[i]);
//
//	printf("\n\nMagnitudes, count: 512\n");
//	for(int i = 0; i < BINS_COUNT; i++)
//		printf("%.3f, ", usable_magnitudes_print[i]);
//
//	printf("\n\nBounds heights/velocity/acceleration, count: 19\n");
//	for(int i = 0; i < BANDS_COUNT; i++)
//		printf("%.3f, ", bounds.heights[i]);
//	printf("\n");
//	for(int i = 0; i < BANDS_COUNT; i++)
//		printf("%.3f, ", bounds.velocities[i]);
//	printf("\n");
//	for(int i = 0; i < BANDS_COUNT; i++)
//		printf("%.3f, ", bounds.accelerations[i]);
//	printf("\nTime dt: %.3f [s], \n", bounds.dt_sec);
}





















//static void magnitudesToBounds() {
//	//current ACCELERATION evaluated on previous values
//	for(int i = 0; i < BANDS_COUNT; i++)
//		bounds_acceleration[i] = (bounds_velocity[i] - bounds_last_velocity[i]) / fft_dts;
//
//	//current VELOCITY evaluated on previous values and save discarded as last
//	for(int i = 0; i < BANDS_COUNT; i++) {
//		bounds_last_velocity[i] = bounds_velocity[i];
//		bounds_velocity[i] = (bounds_heights[i] - bounds_last_heights[i]) / fft_dts;
//	}
//
//	//current HEIGHT(POSITION) and save discarded as last
//	for(int i = 0; i < BANDS_COUNT; i++) {
//		bounds_last_heights[i] = bounds_heights[i];
//		bounds_heights[i] = 0;
//	}
//
//	for(int i = 0; i < BINS_COUNT; i++) {
//		if(usable_magnitudes[i] > 0.01)
//			bounds_heights[bins[i]] += usable_magnitudes[i];
//	}
//
//	for(int i = 0; i < BANDS_COUNT; i++) {
//		bounds.heights[i] = bounds_heights[i];
//		bounds.velocities[i] = bounds_velocity[i];
//		bounds.accelerations[i] = bounds_acceleration[i];
//	}
//	bounds.dt_sec = fft_dts;
//}



//	sampling_time_micros = __HAL_TIM_GET_COUNTER(&htim6);
//	__HAL_TIM_SET_COUNTER(&htim6, 0);
//
////	sapling_frequency = 1.0/((sapling_time_micros/1000)/FFT_SAMPLES_COUNT);
//	sampling_frequency = 1000.0 * FFT_SAMPLES_COUNT / sampling_time_micros;
//
//	samplesBufferIndex ^= 1;
//	magnitudesBufferIndex ^= 1;

//	int b_in_idx = samplesBufferIndex;
//	int b_mag_idx = magnitudesBufferIndex;
//	calFFT(b_in_idx, b_mag_idx);
//	mags_to_bounds();


//	fft_dts = 22.3e-3; //todo timer
//	if(fft_dts < 1e-3)
//		fft_dts = 1e-3; //no zero protection




//	fft_time_micros = __HAL_TIM_GET_COUNTER(&htim6);
//	ASD_lock_render(1);
//	_next_stage(&bounds); //todo trzeba wydzielic, nie ma sensu. to musi byc w osobnym pliku scalajacym, ale fft musi miec osobna funkcjonalnosc
//	ASD_lock_render(0);
//	animation_time_micros = __HAL_TIM_GET_COUNTER(&htim6) - fft_time_micros;
