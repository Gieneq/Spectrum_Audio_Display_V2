#pragma once

#include "arm_math.h"
#include "arm_const_structs.h"
#include <stdio.h>

// If problem with __FPU_PRESENT then add in settings/preproc symbol: __FPU_PRESENT

// Data generated using Jupyter Notebook. The signal mixes 30 Hz, 19999 Hz and white noise.
#define TEST_SAMPLES_COUNT 1024
const float32_t test_signal[TEST_SAMPLES_COUNT] = {0.1624, -0.0287, -0.0983, -0.0188, 0.0127, -0.1097, 0.1012, 0.0448, -0.0093, 0.0676, 0.161, -0.1591, 0.0475, -0.037, 0.249, -0.1368, 0.1503, -0.114, 0.1721, 0.0642, 0.0293, 0.1764, 0.184, 0.1771, 0.1384, 0.1143, 0.0077, 0.1209, -0.006, 0.2677, -0.0163, 0.1464, 0.0402, 0.0559, 0.1067, 0.0936, 0.1178, 0.0901, 0.4271, 0.1416, 0.2421, 0.0108, 0.1578, 0.3248, 0.1918, 0.1567, 0.1603, 0.486, 0.125, 0.3692, 0.1437, 0.2722, 0.0316, 0.2436, 0.181, 0.2913, 0.3504, 0.2801, 0.3506, 0.2473, 0.2779, 0.2848, 0.4044, 0.1618, 0.3729, 0.24, 0.3912, 0.4642, 0.4509, 0.2279, 0.0596, 0.3482, 0.2208, 0.4858, 0.2684, 0.1667, 0.2621, 0.4056, 0.3802, 0.3532, 0.3901, 0.2286, 0.4619, 0.2903, 0.4624, 0.2933, 0.3461, 0.3749, 0.3791, 0.5144, 0.4408, 0.475, 0.255, 0.4232, 0.3355, 0.494, 0.2907, 0.4609, 0.3188, 0.4799, 0.4002, 0.4865, 0.5401, 0.3949, 0.4206, 0.353, 0.603, 0.2726, 0.4725, 0.4268, 0.3151, 0.519, 0.4908, 0.4561, 0.4126, 0.4409, 0.3741, 0.4092, 0.5219, 0.5815, 0.4627, 0.4162, 0.6564, 0.6441, 0.3975, 0.5422, 0.7759, 0.4527, 0.4915, 0.5369, 0.563, 0.4454, 0.4109, 0.6245, 0.5667, 0.5611, 0.5105, 0.5386, 0.5389, 0.6557, 0.4715, 0.6102, 0.6322, 0.648, 0.6616, 0.54, 0.6702, 0.559, 0.7149, 0.5654, 0.6583, 0.2851, 0.7622, 0.8021, 0.6548, 0.6366, 0.5501, 0.6881, 0.5362, 0.6168, 0.4827, 0.6266, 0.5905, 0.6653, 0.6698, 0.6296, 0.7818, 0.6212, 0.9554, 0.3808, 0.7002, 0.6603, 1.0147, 0.5763, 0.7346, 0.633, 0.8152, 0.6895, 0.7026, 0.7391, 0.4777, 0.8307, 0.6548, 0.9253, 0.6243, 0.7022, 0.7458, 0.7395, 0.7799, 0.6604, 0.9204, 0.6748, 1.0227, 0.7483, 0.8944, 0.5051, 0.8563, 0.7638, 0.8284, 0.8883, 0.6592, 0.9184, 0.613, 1.0589, 0.5351, 0.6832, 0.5336, 0.7375, 0.6405, 0.9731, 0.7815, 0.5949, 0.9774, 0.6402, 0.7693, 0.7853, 0.9508, 0.6844, 0.9961, 0.7942, 0.9676, 0.893, 0.9132, 0.9051, 0.6048, 1.1657, 0.6708, 0.896, 0.6852, 0.862, 0.8327, 0.8527, 0.9356, 0.9629, 0.9085, 0.6295, 0.8285, 0.6846, 0.774, 0.8633, 0.8577, 0.8026, 0.8571, 0.7547, 0.722, 1.0125, 0.8388, 0.9266, 0.9562, 0.8345, 0.77, 0.9077, 0.5777, 1.0739, 0.954, 0.7262, 1.1727, 0.8578, 1.036, 0.7364, 0.9974, 0.6736, 1.0315, 0.841, 0.9145, 1.0586, 0.8797, 1.0145, 0.8472, 0.9399, 0.9007, 1.1608, 0.9218, 1.0598, 0.8101, 0.8332, 0.8134, 0.993, 0.9814, 0.9777, 0.9531, 0.7913, 1.0337, 0.9557, 0.9946, 0.9363, 0.9385, 0.9921, 0.7746, 1.0315, 0.8353, 1.0417, 0.9002, 0.9717, 0.8707, 0.974, 0.9722, 1.03, 0.8937, 0.9593, 1.2444, 0.7209, 0.9784, 0.7767, 1.0253, 1.0549, 1.0181, 0.8741, 1.0264, 0.942, 1.0253, 1.0806, 1.0189, 1.0071, 1.1795, 1.1471, 0.9694, 1.0225, 0.882, 0.8879, 0.999, 0.8433, 1.0885, 0.8072, 1.145, 0.9815, 1.0032, 1.0324, 1.0126, 1.0789, 1.0268, 1.1333, 0.8313, 1.0575, 1.0425, 1.0286, 0.6895, 0.8865, 0.6695, 0.8315, 0.9288, 1.1169, 0.983, 0.9691, 1.063, 0.9037, 1.0788, 0.8809, 1.1317, 0.8073, 1.1483, 1.0664, 0.9735, 1.1118, 0.8701, 1.0238, 0.9216, 1.0797, 0.8563, 1.0209, 0.8717, 1.1433, 0.7823, 1.0299, 1.0094, 1.0144, 1.1304, 0.6287, 1.158, 0.9343, 1.0907, 0.881, 1.1346, 0.9353, 1.1776, 1.0891, 1.1545, 0.9995, 0.7302, 1.1697, 0.9856, 1.0902, 0.7721, 1.0021, 1.0362, 0.973, 1.0184, 0.92, 0.9815, 0.849, 0.952, 1.0733, 1.0351, 0.9696, 0.9402, 1.0494, 0.7991, 1.1172, 0.9287, 1.2807, 0.766, 1.0965, 0.9273, 1.1996, 0.8733, 1.0443, 0.749, 0.8963, 1.0632, 1.0351, 1.0339, 1.0944, 1.2569, 0.8763, 0.8265, 0.7293, 0.9489, 1.066, 1.001, 0.7994, 0.8921, 1.2137, 0.8413, 0.9957, 1.0775, 1.0626, 0.8485, 1.0506, 0.9451, 0.9155, 1.1183, 1.0147, 1.1246, 0.8562, 1.173, 0.8546, 1.0911, 0.987, 1.0833, 1.1092, 0.9899, 0.8155, 0.7731, 1.1616, 0.8191, 1.0826, 0.7598, 1.1296, 0.8302, 1.1328, 0.8618, 1.0408, 1.0357, 0.8008, 1.1204, 0.7456, 0.9451, 0.9004, 0.9499, 0.7923, 0.9352, 0.7976, 1.0157, 1.0113, 0.8479, 0.9815, 0.8623, 1.1853, 0.8965, 0.9426, 0.9103, 0.9382, 0.8584, 1.0779, 0.8888, 0.7867, 0.7769, 0.6565, 1.0332, 0.7192, 1.0239, 0.7, 0.8518, 0.9243, 1.0155, 0.9682, 0.9322, 1.1204, 0.8783, 0.8737, 0.7554, 1.0123, 0.747, 0.9503, 0.6756, 0.7627, 0.9382, 0.5645, 0.8151, 0.7481, 0.7691, 0.7469, 0.8444, 0.7344, 0.8538, 0.8272, 0.7635, 0.8687, 0.7021, 0.9555, 0.893, 0.9343, 0.7317, 0.7811, 0.8061, 0.7767, 0.7003, 0.8481, 0.8504, 0.8451, 1.0164, 0.6415, 0.8992, 0.8624, 0.9656, 0.7795, 0.9542, 0.6919, 0.8266, 0.944, 0.8668, 0.762, 0.6405, 0.8947, 0.6274, 0.7994, 0.7463, 0.7575, 0.543, 0.7681, 0.7298, 0.6003, 0.6548, 0.7355, 0.6021, 0.4546, 0.779, 0.7688, 0.8914, 0.5741, 0.6815, 0.5887, 0.7416, 0.6308, 0.5866, 0.8949, 0.5689, 0.92, 0.5253, 0.7634, 0.7411, 0.651, 0.8442, 0.6608, 0.5803, 0.9621, 0.8217, 0.567, 0.598, 0.5854, 0.6451, 0.6849, 0.6664, 0.8553, 0.5843, 0.7595, 0.5673, 0.7057, 0.5016, 0.8114, 0.6188, 0.5912, 0.4724, 0.5854, 0.7492, 0.5299, 0.8455, 0.415, 0.6971, 0.2306, 0.6038, 0.472, 0.667, 0.7167, 0.5571, 0.7401, 0.5601, 0.7309, 0.407, 0.7826, 0.3359, 0.6736, 0.3685, 0.5246, 0.3602, 0.4622, 0.5903, 0.4472, 0.4577, 0.5607, 0.6377, 0.5039, 0.6622, 0.3569, 0.3412, 0.3743, 0.5955, 0.4091, 0.4946, 0.4903, 0.4117, 0.3803, 0.4785, 0.5382, 0.4706, 0.513, 0.5041, 0.4208, 0.5471, 0.2199, 0.4014, 0.4027, 0.5165, 0.2965, 0.4817, 0.3897, 0.3919, 0.4328, 0.2965, 0.3893, 0.4262, 0.5737, 0.1773, 0.5611, 0.1723, 0.5295, 0.1064, 0.2958, 0.2874, 0.3276, 0.5288, 0.3742, 0.5803, 0.3636, 0.4049, 0.2055, 0.5188, 0.2561, 0.3474, 0.1605, 0.289, 0.0629, 0.1935, 0.2802, 0.2674, 0.3406, 0.1544, 0.5017, 0.1023, 0.3496, 0.0596, 0.2633, 0.338, 0.2797, 0.2431, 0.1847, 0.3749, 0.1399, 0.3364, 0.2081, 0.3119, 0.104, 0.0888, 0.5019, 0.3397, 0.148, 0.1518, 0.3598, 0.171, 0.2893, 0.0231, 0.2076, 0.1085, 0.1755, 0.1784, 0.0882, 0.3428, 0.1834, 0.1326, 0.0035, 0.1496, 0.1918, 0.1733, 0.2561, 0.0675, 0.1614, -0.0803, 0.3246, -0.0226, 0.0555, -0.0565, -0.0487, 0.0195, 0.1435, 0.0933, 0.2181, 0.0819, 0.0883, 0.1787, -0.0527, -0.0507, 0.0506, 0.0843, -0.0224, -0.042, 0.0459, 0.0319, 0.068, -0.0531, 0.2055, 0.0161, 0.1825, 0.2409, 0.0275, -0.1091, -0.0637, 0.0142, -0.095, -0.2517, -0.2082, 0.0607, -0.0267, -0.0929, -0.1996, 0.0264, -0.191, 0.0437, -0.0759, -0.0413, -0.1013, 0.0196, 0.0065, -0.0454, -0.0281, -0.1263, -0.0747, -0.2601, -0.127, -0.1277, -0.1424, 0.0783, -0.296, -0.1493, -0.0517, 0.0298, -0.4202, -0.0039, -0.188, -0.3179, -0.2066, -0.1692, -0.049, -0.1324, -0.0772, -0.165, -0.0922, -0.3643, -0.1936, -0.2038, -0.3458, -0.1481, -0.3246, -0.2042, -0.2237, -0.0111, -0.5086, -0.2044, -0.3197, -0.2059, -0.2178, -0.4048, -0.2255, -0.2174, -0.2091, -0.21, -0.3016, -0.2495, -0.2397, -0.2977, -0.2244, -0.2679, -0.1637, -0.4534, -0.3209, -0.2684, -0.3894, -0.2993, -0.2204, -0.1936, -0.2597, -0.2939, -0.5003, -0.2735, -0.4079, -0.1113, -0.2791, -0.295, -0.2905, -0.4826, -0.2619, -0.4239, -0.1964, -0.4504, -0.399, -0.5022, -0.4021, -0.2901, -0.4084, -0.3135, -0.5537, -0.2877, -0.4457, -0.3285, -0.4701, -0.3894, -0.3469, -0.4815, -0.3717, -0.4578, -0.282, -0.3869, -0.2775, -0.4855, -0.5144, -0.463, -0.1874, -0.5635, -0.5819, -0.4536, -0.4372, -0.3438, -0.626, -0.3904, -0.4833, -0.3417, -0.3221, -0.3577, -0.4862, -0.4598, -0.5079, -0.6781, -0.4198, -0.57, -0.5669, -0.6797, -0.4864, -0.5786, -0.5246, -0.517, -0.5516, -0.4067, -0.7914, -0.3109, -0.5169, -0.4618, -0.6017, -0.4281, -0.7179, -0.5212, -0.5224, -0.5693, -0.4461, -0.6494, -0.5068, -0.7738, -0.5414, -0.7508, -0.3562, -0.6578, -0.6755, -0.5978, -0.6571, -0.8938, -0.6482, -0.7072, -0.6762, -0.638, -0.8873, -0.514, -0.8676, -0.6567, -0.6533, -0.6129, -0.5498, -0.7358, -0.6708, -0.5772, -0.6378, -0.5963, -0.6439, -0.6369, -0.54, -0.8129, -0.6734, -0.583, -0.6965, -0.6415, -0.7735, -0.6506, -0.9276, -0.534, -0.8424, -0.5425, -0.6811, -0.8314, -0.7074, -0.8281, -0.7412, -0.7861, -0.6913, -0.6794, -0.5784, -0.9062, -0.7143, -0.7955, -0.9302, -0.6293, -0.7358, -0.5925, -0.9128, -0.5672, -0.894, -0.6015, -0.6671, -0.7286, -0.9444, -0.8353, -0.6878, -0.7383, -0.8276, -0.9153, -0.6798, -0.8583, -0.6326, -0.9715, -0.8134, -0.7297, -0.7925, -0.7348, -0.7756, -0.7313, -0.8709, -0.7617, -1.0633, -0.8801, -0.8958, -0.8177, -0.9222, -0.8263, -0.8945, -0.9029, -0.7692, -1.0332, -0.9854, -0.8082, -0.744, -1.1943, -0.8652, -0.8417, -0.9054, -0.7714, -1.0355, -0.7734, -0.9782, -0.7974, -0.9992, -0.7789, -0.8575, -0.8984, -0.9442, -0.889, -0.8635, -0.9217, -0.7409, -0.8655, -0.8122, -1.2261, -0.827, -0.9362, -0.885, -0.9392, -1.1689, -0.8208, -1.0128, -0.9836, -1.1014, -0.9065, -0.9567, -0.7831, -0.8389, -0.8204, -1.0774, -1.0851, -0.7766, -0.8419, -0.874, -0.9761, -0.9879, -1.2292, -0.9738, -1.0428, -0.9541, -0.9816, -1.0097};

// Len of mags = 1024 should be equal to len of time samples = 1024. Use half.
const float32_t test_megs[TEST_SAMPLES_COUNT] = {311.6108, 420.9747, 98.1827, 58.7931, 42.6959, 34.219, 27.1659, 22.0502, 23.3506, 17.9231, 15.8833, 14.1972, 12.3149, 9.6207, 10.1801, 9.0002, 8.7943, 10.5024, 10.5264, 5.5023, 11.1991, 4.9225, 7.8062, 7.1913, 13.1039, 4.4101, 9.9518, 6.3973, 6.7241, 3.149, 4.5222, 0.6644, 4.6058, 7.3791, 6.3518, 2.9223, 4.0499, 2.7941, 4.9068, 6.0233, 4.4422, 4.77, 3.4824, 5.504, 5.6993, 3.8774, 1.5853, 6.0804, 4.3953, 5.0896, 4.2738, 8.0319, 3.4311, 7.9545, 4.4783, 5.2772, 1.7574, 6.4118, 4.0888, 7.6756, 5.3031, 1.6197, 3.8307, 4.2655, 2.3716, 0.722, 9.7994, 2.1851, 2.4172, 5.9522, 1.7307, 3.1994, 4.5306, 4.7869, 2.3295, 1.4003, 4.6656, 3.0256, 1.1518, 1.6292, 4.0426, 2.7388, 0.8741, 3.3136, 2.3722, 4.3943, 0.6707, 2.1085, 4.6515, 2.259, 2.5692, 3.0955, 1.0122, 9.0954, 2.2558, 2.0602, 3.2562, 1.8393, 1.2012, 0.6562, 0.3439, 0.9197, 3.9044, 1.451, 2.188, 5.0063, 1.3889, 4.0494, 6.7305, 3.9075, 3.5518, 1.8386, 4.9126, 3.7124, 1.7073, 4.1683, 2.1382, 1.5808, 5.0458, 2.0394, 3.0745, 2.2109, 0.6649, 4.3345, 1.9702, 3.8338, 2.2001, 2.7501, 4.9474, 4.3986, 2.0946, 2.5009, 3.5014, 4.7707, 2.7591, 0.6874, 3.0314, 3.1774, 2.0434, 1.3153, 4.4043, 3.6352, 2.2673, 3.5481, 3.0106, 1.1147, 1.9989, 1.5892, 5.2201, 2.2846, 3.7718, 1.2564, 2.8054, 4.1849, 1.5984, 4.8359, 3.5108, 0.4124, 3.6033, 3.1398, 2.7881, 1.2856, 4.4943, 4.3662, 3.4733, 3.0472, 6.424, 1.565, 1.2437, 2.6507, 1.6997, 1.7195, 1.79, 4.0129, 3.6855, 3.4183, 4.6705, 1.4748, 2.3958, 7.7707, 0.5827, 3.3105, 1.4582, 1.3667, 3.3534, 1.9595, 6.5458, 4.3826, 2.853, 2.4043, 1.8086, 2.6814, 1.9948, 2.0331, 1.9051, 2.9223, 2.9586, 2.771, 2.9498, 4.8844, 2.7796, 6.959, 1.4358, 3.2186, 1.2096, 2.2191, 1.2564, 5.514, 4.2728, 2.8996, 2.1884, 2.8282, 0.5673, 6.0928, 4.1292, 2.5701, 4.5313, 2.1051, 4.5235, 3.0244, 5.4397, 4.3493, 4.7557, 3.485, 1.3155, 1.651, 2.5024, 5.861, 4.8972, 3.2807, 1.9251, 1.2385, 0.5015, 1.6974, 3.8992, 4.8739, 1.7195, 3.3696, 3.0309, 2.823, 1.9586, 2.3946, 3.5827, 4.5869, 2.1237, 0.6364, 3.6495, 1.2968, 2.7684, 3.8806, 1.6461, 3.1698, 1.0508, 1.9404, 3.4878, 3.6373, 1.7944, 5.816, 1.7748, 2.955, 1.8751, 2.4893, 2.2969, 1.4231, 3.0328, 2.6372, 2.1749, 3.8454, 3.9373, 2.8874, 6.9572, 0.7432, 4.7133, 1.9131, 1.3479, 5.8772, 3.1974, 1.7937, 1.9655, 3.0787, 2.9717, 3.8232, 3.7198, 3.7399, 1.8021, 2.5644, 4.4624, 1.2171, 2.6244, 2.0792, 1.7722, 4.7616, 4.9726, 1.8396, 4.2537, 0.9052, 2.0701, 1.1192, 2.5353, 4.8091, 1.7981, 2.3744, 1.5788, 4.1779, 4.4236, 4.2225, 1.8718, 5.3465, 0.6626, 5.0614, 3.8146, 2.8711, 3.1649, 1.4738, 2.5725, 1.9077, 3.7732, 1.2178, 3.7166, 3.3076, 5.3301, 1.6394, 0.1218, 2.2191, 1.7268, 5.1133, 2.1151, 1.2005, 4.3829, 5.3225, 0.3948, 4.4797, 1.021, 3.9465, 1.4513, 0.9106, 2.509, 1.9162, 0.6334, 2.568, 2.2611, 2.9302, 1.4571, 4.4202, 2.4106, 1.1283, 2.7618, 3.9695, 3.1966, 3.6596, 0.5695, 3.7839, 5.0881, 3.1789, 2.9691, 4.6648, 3.1249, 5.82, 2.3771, 1.5066, 3.892, 2.9354, 1.5686, 1.534, 4.8932, 1.6049, 2.0565, 3.5459, 2.7961, 3.5313, 4.4978, 2.1809, 5.4716, 2.5314, 2.5573, 3.557, 4.4005, 2.7785, 2.0948, 0.0925, 2.3295, 2.1477, 4.2406, 1.0237, 3.3906, 1.8969, 2.9302, 3.2841, 3.0061, 0.5637, 5.0713, 1.9909, 5.3942, 3.2318, 1.6428, 1.2055, 3.1963, 3.8739, 2.7945, 2.1983, 5.1736, 1.9763, 4.7131, 2.3103, 4.6165, 1.6042, 3.783, 2.1442, 0.4252, 1.7583, 2.9823, 2.3048, 3.7012, 2.7407, 5.1226, 1.5522, 0.7243, 4.3973, 2.0092, 2.6955, 1.5201, 2.2242, 2.4149, 2.0621, 5.865, 1.4811, 0.8113, 1.1452, 4.1035, 1.2779, 3.3832, 3.5239, 3.5794, 3.9472, 2.8715, 3.1244, 1.9429, 1.6383, 4.9651, 0.3385, 0.0298, 1.6292, 0.7156, 2.9082, 3.3213, 1.7543, 1.1321, 4.4275, 1.5036, 3.4588, 3.1097, 1.9215, 3.3643, 4.7569, 4.4667, 4.9951, 2.4764, 1.0265, 3.8958, 4.2415, 5.0849, 3.0643, 5.3472, 6.6461, 9.0152, 34.897, 25.8908, 8.6655, 7.3503, 2.6189, 3.8599, 5.2356, 5.4645, 6.0467, 3.0574, 2.4671, 1.4503, 2.2922, 3.4262, 4.9365, 6.0654, 3.3842, 6.1064, 4.6119, 3.4057, 0.3909, 5.132, 5.8713, 0.5634, 1.4078, 1.7656, 2.1139, 6.4606, 3.5035, 4.1631, 5.9917, 2.4068, 1.4743, 3.3603, 1.336, 4.1456, 2.6493, 1.5876, 0.6444, 3.068, 5.6983, 3.617, 3.0196, 2.3273, 1.5612, 0.4296, 5.1089, 0.8862, 5.1089, 0.4296, 1.5612, 2.3273, 3.0196, 3.617, 5.6983, 3.068, 0.6444, 1.5876, 2.6493, 4.1456, 1.336, 3.3603, 1.4743, 2.4068, 5.9917, 4.1631, 3.5035, 6.4606, 2.1139, 1.7656, 1.4078, 0.5634, 5.8713, 5.132, 0.3909, 3.4057, 4.6119, 6.1064, 3.3842, 6.0654, 4.9365, 3.4262, 2.2922, 1.4503, 2.4671, 3.0574, 6.0467, 5.4645, 5.2356, 3.8599, 2.6189, 7.3503, 8.6655, 25.8908, 34.897, 9.0152, 6.6461, 5.3472, 3.0643, 5.0849, 4.2415, 3.8958, 1.0265, 2.4764, 4.9951, 4.4667, 4.7569, 3.3643, 1.9215, 3.1097, 3.4588, 1.5036, 4.4275, 1.1321, 1.7543, 3.3213, 2.9082, 0.7156, 1.6292, 0.0298, 0.3385, 4.9651, 1.6383, 1.9429, 3.1244, 2.8715, 3.9472, 3.5794, 3.5239, 3.3832, 1.2779, 4.1035, 1.1452, 0.8113, 1.4811, 5.865, 2.0621, 2.4149, 2.2242, 1.5201, 2.6955, 2.0092, 4.3973, 0.7243, 1.5522, 5.1226, 2.7407, 3.7012, 2.3048, 2.9823, 1.7583, 0.4252, 2.1442, 3.783, 1.6042, 4.6165, 2.3103, 4.7131, 1.9763, 5.1736, 2.1983, 2.7945, 3.8739, 3.1963, 1.2055, 1.6428, 3.2318, 5.3942, 1.9909, 5.0713, 0.5637, 3.0061, 3.2841, 2.9302, 1.8969, 3.3906, 1.0237, 4.2406, 2.1477, 2.3295, 0.0925, 2.0948, 2.7785, 4.4005, 3.557, 2.5573, 2.5314, 5.4716, 2.1809, 4.4978, 3.5313, 2.7961, 3.5459, 2.0565, 1.6049, 4.8932, 1.534, 1.5686, 2.9354, 3.892, 1.5066, 2.3771, 5.82, 3.1249, 4.6648, 2.9691, 3.1789, 5.0881, 3.7839, 0.5695, 3.6596, 3.1966, 3.9695, 2.7618, 1.1283, 2.4106, 4.4202, 1.4571, 2.9302, 2.2611, 2.568, 0.6334, 1.9162, 2.509, 0.9106, 1.4513, 3.9465, 1.021, 4.4797, 0.3948, 5.3225, 4.3829, 1.2005, 2.1151, 5.1133, 1.7268, 2.2191, 0.1218, 1.6394, 5.3301, 3.3076, 3.7166, 1.2178, 3.7732, 1.9077, 2.5725, 1.4738, 3.1649, 2.8711, 3.8146, 5.0614, 0.6626, 5.3465, 1.8718, 4.2225, 4.4236, 4.1779, 1.5788, 2.3744, 1.7981, 4.8091, 2.5353, 1.1192, 2.0701, 0.9052, 4.2537, 1.8396, 4.9726, 4.7616, 1.7722, 2.0792, 2.6244, 1.2171, 4.4624, 2.5644, 1.8021, 3.7399, 3.7198, 3.8232, 2.9717, 3.0787, 1.9655, 1.7937, 3.1974, 5.8772, 1.3479, 1.9131, 4.7133, 0.7432, 6.9572, 2.8874, 3.9373, 3.8454, 2.1749, 2.6372, 3.0328, 1.4231, 2.2969, 2.4893, 1.8751, 2.955, 1.7748, 5.816, 1.7944, 3.6373, 3.4878, 1.9404, 1.0508, 3.1698, 1.6461, 3.8806, 2.7684, 1.2968, 3.6495, 0.6364, 2.1237, 4.5869, 3.5827, 2.3946, 1.9586, 2.823, 3.0309, 3.3696, 1.7195, 4.8739, 3.8992, 1.6974, 0.5015, 1.2385, 1.9251, 3.2807, 4.8972, 5.861, 2.5024, 1.651, 1.3155, 3.485, 4.7557, 4.3493, 5.4397, 3.0244, 4.5235, 2.1051, 4.5313, 2.5701, 4.1292, 6.0928, 0.5673, 2.8282, 2.1884, 2.8996, 4.2728, 5.514, 1.2564, 2.2191, 1.2096, 3.2186, 1.4358, 6.959, 2.7796, 4.8844, 2.9498, 2.771, 2.9586, 2.9223, 1.9051, 2.0331, 1.9948, 2.6814, 1.8086, 2.4043, 2.853, 4.3826, 6.5458, 1.9595, 3.3534, 1.3667, 1.4582, 3.3105, 0.5827, 7.7707, 2.3958, 1.4748, 4.6705, 3.4183, 3.6855, 4.0129, 1.79, 1.7195, 1.6997, 2.6507, 1.2437, 1.565, 6.424, 3.0472, 3.4733, 4.3662, 4.4943, 1.2856, 2.7881, 3.1398, 3.6033, 0.4124, 3.5108, 4.8359, 1.5984, 4.1849, 2.8054, 1.2564, 3.7718, 2.2846, 5.2201, 1.5892, 1.9989, 1.1147, 3.0106, 3.5481, 2.2673, 3.6352, 4.4043, 1.3153, 2.0434, 3.1774, 3.0314, 0.6874, 2.7591, 4.7707, 3.5014, 2.5009, 2.0946, 4.3986, 4.9474, 2.7501, 2.2001, 3.8338, 1.9702, 4.3345, 0.6649, 2.2109, 3.0745, 2.0394, 5.0458, 1.5808, 2.1382, 4.1683, 1.7073, 3.7124, 4.9126, 1.8386, 3.5518, 3.9075, 6.7305, 4.0494, 1.3889, 5.0063, 2.188, 1.451, 3.9044, 0.9197, 0.3439, 0.6562, 1.2012, 1.8393, 3.2562, 2.0602, 2.2558, 9.0954, 1.0122, 3.0955, 2.5692, 2.259, 4.6515, 2.1085, 0.6707, 4.3943, 2.3722, 3.3136, 0.8741, 2.7388, 4.0426, 1.6292, 1.1518, 3.0256, 4.6656, 1.4003, 2.3295, 4.7869, 4.5306, 3.1994, 1.7307, 5.9522, 2.4172, 2.1851, 9.7994, 0.722, 2.3716, 4.2655, 3.8307, 1.6197, 5.3031, 7.6756, 4.0888, 6.4118, 1.7574, 5.2772, 4.4783, 7.9545, 3.4311, 8.0319, 4.2738, 5.0896, 4.3953, 6.0804, 1.5853, 3.8774, 5.6993, 5.504, 3.4824, 4.77, 4.4422, 6.0233, 4.9068, 2.7941, 4.0499, 2.9223, 6.3518, 7.3791, 4.6058, 0.6644, 4.5222, 3.149, 6.7241, 6.3973, 9.9518, 4.4101, 13.1039, 7.1913, 7.8062, 4.9225, 11.1991, 5.5023, 10.5264, 10.5024, 8.7943, 9.0002, 10.1801, 9.6207, 12.3149, 14.1972, 15.8833, 17.9231, 23.3506, 22.0502, 27.1659, 34.219, 42.6959, 58.7931, 98.1827, 420.9747};

#define INTERVAL 10000

float32_t Input[TEST_SAMPLES_COUNT*2];
float32_t Output[TEST_SAMPLES_COUNT];

/* Reference index at which max energy of bin ocuurs */
uint32_t refIndex = 213, testIndex = 0;

static float32_t get_comparison_error(const float32_t* ref_mags, const float32_t* test_mags, int count) {
	static float32_t cmp_error = 0, rel_error=0;

	for (int i = 0; i < count; ++i) {
		rel_error = (ref_mags[i] - test_mags[i]) / ref_mags[i];
		cmp_error += rel_error < 0 ? -rel_error : rel_error;
	}
	return 100*cmp_error/count;
}

void execute_testbench() {
	float32_t maxValue;				/* Max FFT value is stored here */
	uint32_t maxIndex;				/* Index in Output array where max value is */
	int i = 0;

	/* Real part, make offset by ADC / 2 */
	for (i = 0; i < TEST_SAMPLES_COUNT*2; i+=2)
		Input[i] = (float32_t)(test_signal[i/2]);

	/* Imaginary part, make offset by ADC / 2 + 1 */
	for (i = 1; i < TEST_SAMPLES_COUNT*2; i+=2)
		Input[i] = 0;

	/* Process the data through the CFFT/CIFFT module */
	assert(TEST_SAMPLES_COUNT == 1024);
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, Input, 0, 1);

	/* Process the data through the Complex Magniture Module for calculating the magnitude at each bin */
	arm_cmplx_mag_f32(Input, Output, TEST_SAMPLES_COUNT);

	/* Calculates maxValue and returns corresponding value */
	arm_max_f32(Output, TEST_SAMPLES_COUNT, &maxValue, &maxIndex);

	float32_t mean_rel_error = get_comparison_error(test_megs, Output, TEST_SAMPLES_COUNT);
	printf("FFT EVALUATION DONE with error: %.3f %%\n\n", mean_rel_error);

	printf("START INPUT SIGNAL %d:\n", TEST_SAMPLES_COUNT);
	for (i = 0; i < TEST_SAMPLES_COUNT; i++)
		printf("%f, ",  test_signal[i]);
	printf("\n");
	printf("STOP INPUT SIGNAL\n\n");


	//retrive half
	printf("START MAGNITUDES %d:\n", TEST_SAMPLES_COUNT/2);
	for (i = 0; i < TEST_SAMPLES_COUNT/2; i++)
		printf("%f, ",  Output[i]);
	printf("\n");
	printf("STOP MAGNITUDES\n\n");


	//full to reconstruct
	printf("START REAL %d:\n", TEST_SAMPLES_COUNT);
	for (i = 0; i < TEST_SAMPLES_COUNT*2; i+=2)
		printf("%f, ",  Input[i]);
	printf("\n");
	printf("STOP REAL\n\n");


	//full to reconstruct
	printf("START IMAG %d:\n", TEST_SAMPLES_COUNT);
	for (i = 1; i < TEST_SAMPLES_COUNT*2; i+=2)
		printf("%f, ",  Input[i]);
	printf("\n");
	printf("STOP IMAG\n\n");


	printf("START TEST, IT WILL TAKE %d MS...\n", INTERVAL);
	uint32_t start_millis = HAL_GetTick();
	float delta_millis = 0;
	int counter = 0;

	while(HAL_GetTick() - start_millis < INTERVAL) {
		arm_cmplx_mag_f32(Input, Output, TEST_SAMPLES_COUNT);
		++counter;
	}

	delta_millis = HAL_GetTick() - start_millis;
	printf("STOP TEST! DONE %d ITERATIONS AND (WITH %d FFT POINTS) GOT %d Hz REFRESH RATE (T = %d US), ERROR: %.3f%%.\n", counter, TEST_SAMPLES_COUNT, (int)(counter*1000.0/delta_millis), (int)(delta_millis*1000.0/counter), mean_rel_error);
}