/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "arm_math.h" //https://community.st.com/s/article/configuring-dsp-libraries-on-stm32cubeide
#include "arm_const_structs.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


//#define TEST_LENGTH_SAMPLES 2048


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define INTERVAL 10000

#define TEST_SAMPLES_COUNT 1024
const float test_signal[TEST_SAMPLES_COUNT] = {0.1624, -0.0287, -0.0983, -0.0188, 0.0127, -0.1097, 0.1012, 0.0448, -0.0093, 0.0676, 0.161, -0.1591, 0.0475, -0.037, 0.249, -0.1368, 0.1503, -0.114, 0.1721, 0.0642, 0.0293, 0.1764, 0.184, 0.1771, 0.1384, 0.1143, 0.0077, 0.1209, -0.006, 0.2677, -0.0163, 0.1464, 0.0402, 0.0559, 0.1067, 0.0936, 0.1178, 0.0901, 0.4271, 0.1416, 0.2421, 0.0108, 0.1578, 0.3248, 0.1918, 0.1567, 0.1603, 0.486, 0.125, 0.3692, 0.1437, 0.2722, 0.0316, 0.2436, 0.181, 0.2913, 0.3504, 0.2801, 0.3506, 0.2473, 0.2779, 0.2848, 0.4044, 0.1618, 0.3729, 0.24, 0.3912, 0.4642, 0.4509, 0.2279, 0.0596, 0.3482, 0.2208, 0.4858, 0.2684, 0.1667, 0.2621, 0.4056, 0.3802, 0.3532, 0.3901, 0.2286, 0.4619, 0.2903, 0.4624, 0.2933, 0.3461, 0.3749, 0.3791, 0.5144, 0.4408, 0.475, 0.255, 0.4232, 0.3355, 0.494, 0.2907, 0.4609, 0.3188, 0.4799, 0.4002, 0.4865, 0.5401, 0.3949, 0.4206, 0.353, 0.603, 0.2726, 0.4725, 0.4268, 0.3151, 0.519, 0.4908, 0.4561, 0.4126, 0.4409, 0.3741, 0.4092, 0.5219, 0.5815, 0.4627, 0.4162, 0.6564, 0.6441, 0.3975, 0.5422, 0.7759, 0.4527, 0.4915, 0.5369, 0.563, 0.4454, 0.4109, 0.6245, 0.5667, 0.5611, 0.5105, 0.5386, 0.5389, 0.6557, 0.4715, 0.6102, 0.6322, 0.648, 0.6616, 0.54, 0.6702, 0.559, 0.7149, 0.5654, 0.6583, 0.2851, 0.7622, 0.8021, 0.6548, 0.6366, 0.5501, 0.6881, 0.5362, 0.6168, 0.4827, 0.6266, 0.5905, 0.6653, 0.6698, 0.6296, 0.7818, 0.6212, 0.9554, 0.3808, 0.7002, 0.6603, 1.0147, 0.5763, 0.7346, 0.633, 0.8152, 0.6895, 0.7026, 0.7391, 0.4777, 0.8307, 0.6548, 0.9253, 0.6243, 0.7022, 0.7458, 0.7395, 0.7799, 0.6604, 0.9204, 0.6748, 1.0227, 0.7483, 0.8944, 0.5051, 0.8563, 0.7638, 0.8284, 0.8883, 0.6592, 0.9184, 0.613, 1.0589, 0.5351, 0.6832, 0.5336, 0.7375, 0.6405, 0.9731, 0.7815, 0.5949, 0.9774, 0.6402, 0.7693, 0.7853, 0.9508, 0.6844, 0.9961, 0.7942, 0.9676, 0.893, 0.9132, 0.9051, 0.6048, 1.1657, 0.6708, 0.896, 0.6852, 0.862, 0.8327, 0.8527, 0.9356, 0.9629, 0.9085, 0.6295, 0.8285, 0.6846, 0.774, 0.8633, 0.8577, 0.8026, 0.8571, 0.7547, 0.722, 1.0125, 0.8388, 0.9266, 0.9562, 0.8345, 0.77, 0.9077, 0.5777, 1.0739, 0.954, 0.7262, 1.1727, 0.8578, 1.036, 0.7364, 0.9974, 0.6736, 1.0315, 0.841, 0.9145, 1.0586, 0.8797, 1.0145, 0.8472, 0.9399, 0.9007, 1.1608, 0.9218, 1.0598, 0.8101, 0.8332, 0.8134, 0.993, 0.9814, 0.9777, 0.9531, 0.7913, 1.0337, 0.9557, 0.9946, 0.9363, 0.9385, 0.9921, 0.7746, 1.0315, 0.8353, 1.0417, 0.9002, 0.9717, 0.8707, 0.974, 0.9722, 1.03, 0.8937, 0.9593, 1.2444, 0.7209, 0.9784, 0.7767, 1.0253, 1.0549, 1.0181, 0.8741, 1.0264, 0.942, 1.0253, 1.0806, 1.0189, 1.0071, 1.1795, 1.1471, 0.9694, 1.0225, 0.882, 0.8879, 0.999, 0.8433, 1.0885, 0.8072, 1.145, 0.9815, 1.0032, 1.0324, 1.0126, 1.0789, 1.0268, 1.1333, 0.8313, 1.0575, 1.0425, 1.0286, 0.6895, 0.8865, 0.6695, 0.8315, 0.9288, 1.1169, 0.983, 0.9691, 1.063, 0.9037, 1.0788, 0.8809, 1.1317, 0.8073, 1.1483, 1.0664, 0.9735, 1.1118, 0.8701, 1.0238, 0.9216, 1.0797, 0.8563, 1.0209, 0.8717, 1.1433, 0.7823, 1.0299, 1.0094, 1.0144, 1.1304, 0.6287, 1.158, 0.9343, 1.0907, 0.881, 1.1346, 0.9353, 1.1776, 1.0891, 1.1545, 0.9995, 0.7302, 1.1697, 0.9856, 1.0902, 0.7721, 1.0021, 1.0362, 0.973, 1.0184, 0.92, 0.9815, 0.849, 0.952, 1.0733, 1.0351, 0.9696, 0.9402, 1.0494, 0.7991, 1.1172, 0.9287, 1.2807, 0.766, 1.0965, 0.9273, 1.1996, 0.8733, 1.0443, 0.749, 0.8963, 1.0632, 1.0351, 1.0339, 1.0944, 1.2569, 0.8763, 0.8265, 0.7293, 0.9489, 1.066, 1.001, 0.7994, 0.8921, 1.2137, 0.8413, 0.9957, 1.0775, 1.0626, 0.8485, 1.0506, 0.9451, 0.9155, 1.1183, 1.0147, 1.1246, 0.8562, 1.173, 0.8546, 1.0911, 0.987, 1.0833, 1.1092, 0.9899, 0.8155, 0.7731, 1.1616, 0.8191, 1.0826, 0.7598, 1.1296, 0.8302, 1.1328, 0.8618, 1.0408, 1.0357, 0.8008, 1.1204, 0.7456, 0.9451, 0.9004, 0.9499, 0.7923, 0.9352, 0.7976, 1.0157, 1.0113, 0.8479, 0.9815, 0.8623, 1.1853, 0.8965, 0.9426, 0.9103, 0.9382, 0.8584, 1.0779, 0.8888, 0.7867, 0.7769, 0.6565, 1.0332, 0.7192, 1.0239, 0.7, 0.8518, 0.9243, 1.0155, 0.9682, 0.9322, 1.1204, 0.8783, 0.8737, 0.7554, 1.0123, 0.747, 0.9503, 0.6756, 0.7627, 0.9382, 0.5645, 0.8151, 0.7481, 0.7691, 0.7469, 0.8444, 0.7344, 0.8538, 0.8272, 0.7635, 0.8687, 0.7021, 0.9555, 0.893, 0.9343, 0.7317, 0.7811, 0.8061, 0.7767, 0.7003, 0.8481, 0.8504, 0.8451, 1.0164, 0.6415, 0.8992, 0.8624, 0.9656, 0.7795, 0.9542, 0.6919, 0.8266, 0.944, 0.8668, 0.762, 0.6405, 0.8947, 0.6274, 0.7994, 0.7463, 0.7575, 0.543, 0.7681, 0.7298, 0.6003, 0.6548, 0.7355, 0.6021, 0.4546, 0.779, 0.7688, 0.8914, 0.5741, 0.6815, 0.5887, 0.7416, 0.6308, 0.5866, 0.8949, 0.5689, 0.92, 0.5253, 0.7634, 0.7411, 0.651, 0.8442, 0.6608, 0.5803, 0.9621, 0.8217, 0.567, 0.598, 0.5854, 0.6451, 0.6849, 0.6664, 0.8553, 0.5843, 0.7595, 0.5673, 0.7057, 0.5016, 0.8114, 0.6188, 0.5912, 0.4724, 0.5854, 0.7492, 0.5299, 0.8455, 0.415, 0.6971, 0.2306, 0.6038, 0.472, 0.667, 0.7167, 0.5571, 0.7401, 0.5601, 0.7309, 0.407, 0.7826, 0.3359, 0.6736, 0.3685, 0.5246, 0.3602, 0.4622, 0.5903, 0.4472, 0.4577, 0.5607, 0.6377, 0.5039, 0.6622, 0.3569, 0.3412, 0.3743, 0.5955, 0.4091, 0.4946, 0.4903, 0.4117, 0.3803, 0.4785, 0.5382, 0.4706, 0.513, 0.5041, 0.4208, 0.5471, 0.2199, 0.4014, 0.4027, 0.5165, 0.2965, 0.4817, 0.3897, 0.3919, 0.4328, 0.2965, 0.3893, 0.4262, 0.5737, 0.1773, 0.5611, 0.1723, 0.5295, 0.1064, 0.2958, 0.2874, 0.3276, 0.5288, 0.3742, 0.5803, 0.3636, 0.4049, 0.2055, 0.5188, 0.2561, 0.3474, 0.1605, 0.289, 0.0629, 0.1935, 0.2802, 0.2674, 0.3406, 0.1544, 0.5017, 0.1023, 0.3496, 0.0596, 0.2633, 0.338, 0.2797, 0.2431, 0.1847, 0.3749, 0.1399, 0.3364, 0.2081, 0.3119, 0.104, 0.0888, 0.5019, 0.3397, 0.148, 0.1518, 0.3598, 0.171, 0.2893, 0.0231, 0.2076, 0.1085, 0.1755, 0.1784, 0.0882, 0.3428, 0.1834, 0.1326, 0.0035, 0.1496, 0.1918, 0.1733, 0.2561, 0.0675, 0.1614, -0.0803, 0.3246, -0.0226, 0.0555, -0.0565, -0.0487, 0.0195, 0.1435, 0.0933, 0.2181, 0.0819, 0.0883, 0.1787, -0.0527, -0.0507, 0.0506, 0.0843, -0.0224, -0.042, 0.0459, 0.0319, 0.068, -0.0531, 0.2055, 0.0161, 0.1825, 0.2409, 0.0275, -0.1091, -0.0637, 0.0142, -0.095, -0.2517, -0.2082, 0.0607, -0.0267, -0.0929, -0.1996, 0.0264, -0.191, 0.0437, -0.0759, -0.0413, -0.1013, 0.0196, 0.0065, -0.0454, -0.0281, -0.1263, -0.0747, -0.2601, -0.127, -0.1277, -0.1424, 0.0783, -0.296, -0.1493, -0.0517, 0.0298, -0.4202, -0.0039, -0.188, -0.3179, -0.2066, -0.1692, -0.049, -0.1324, -0.0772, -0.165, -0.0922, -0.3643, -0.1936, -0.2038, -0.3458, -0.1481, -0.3246, -0.2042, -0.2237, -0.0111, -0.5086, -0.2044, -0.3197, -0.2059, -0.2178, -0.4048, -0.2255, -0.2174, -0.2091, -0.21, -0.3016, -0.2495, -0.2397, -0.2977, -0.2244, -0.2679, -0.1637, -0.4534, -0.3209, -0.2684, -0.3894, -0.2993, -0.2204, -0.1936, -0.2597, -0.2939, -0.5003, -0.2735, -0.4079, -0.1113, -0.2791, -0.295, -0.2905, -0.4826, -0.2619, -0.4239, -0.1964, -0.4504, -0.399, -0.5022, -0.4021, -0.2901, -0.4084, -0.3135, -0.5537, -0.2877, -0.4457, -0.3285, -0.4701, -0.3894, -0.3469, -0.4815, -0.3717, -0.4578, -0.282, -0.3869, -0.2775, -0.4855, -0.5144, -0.463, -0.1874, -0.5635, -0.5819, -0.4536, -0.4372, -0.3438, -0.626, -0.3904, -0.4833, -0.3417, -0.3221, -0.3577, -0.4862, -0.4598, -0.5079, -0.6781, -0.4198, -0.57, -0.5669, -0.6797, -0.4864, -0.5786, -0.5246, -0.517, -0.5516, -0.4067, -0.7914, -0.3109, -0.5169, -0.4618, -0.6017, -0.4281, -0.7179, -0.5212, -0.5224, -0.5693, -0.4461, -0.6494, -0.5068, -0.7738, -0.5414, -0.7508, -0.3562, -0.6578, -0.6755, -0.5978, -0.6571, -0.8938, -0.6482, -0.7072, -0.6762, -0.638, -0.8873, -0.514, -0.8676, -0.6567, -0.6533, -0.6129, -0.5498, -0.7358, -0.6708, -0.5772, -0.6378, -0.5963, -0.6439, -0.6369, -0.54, -0.8129, -0.6734, -0.583, -0.6965, -0.6415, -0.7735, -0.6506, -0.9276, -0.534, -0.8424, -0.5425, -0.6811, -0.8314, -0.7074, -0.8281, -0.7412, -0.7861, -0.6913, -0.6794, -0.5784, -0.9062, -0.7143, -0.7955, -0.9302, -0.6293, -0.7358, -0.5925, -0.9128, -0.5672, -0.894, -0.6015, -0.6671, -0.7286, -0.9444, -0.8353, -0.6878, -0.7383, -0.8276, -0.9153, -0.6798, -0.8583, -0.6326, -0.9715, -0.8134, -0.7297, -0.7925, -0.7348, -0.7756, -0.7313, -0.8709, -0.7617, -1.0633, -0.8801, -0.8958, -0.8177, -0.9222, -0.8263, -0.8945, -0.9029, -0.7692, -1.0332, -0.9854, -0.8082, -0.744, -1.1943, -0.8652, -0.8417, -0.9054, -0.7714, -1.0355, -0.7734, -0.9782, -0.7974, -0.9992, -0.7789, -0.8575, -0.8984, -0.9442, -0.889, -0.8635, -0.9217, -0.7409, -0.8655, -0.8122, -1.2261, -0.827, -0.9362, -0.885, -0.9392, -1.1689, -0.8208, -1.0128, -0.9836, -1.1014, -0.9065, -0.9567, -0.7831, -0.8389, -0.8204, -1.0774, -1.0851, -0.7766, -0.8419, -0.874, -0.9761, -0.9879, -1.2292, -0.9738, -1.0428, -0.9541, -0.9816, -1.0097};
int __io_putchar(int ch)
{
  if (ch == '\n') {
    __io_putchar('\r');
  }

  HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);

  return 1;
}

float32_t Input[TEST_SAMPLES_COUNT*2]; //samples x2 (512 complex points)
float32_t Output[TEST_SAMPLES_COUNT]; //normal, but retrive half

/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;

/* Reference index at which max energy of bin ocuurs */
uint32_t refIndex = 213, testIndex = 0;


void benchmark() {
//	https://www.keil.com/pack/doc/CMSIS/DSP/html/group__ComplexFFT.html
	float32_t maxValue;				/* Max FFT value is stored here */
	uint32_t maxIndex;				/* Index in Output array where max value is */
	int i = 0;


	for (i = 0; i < TEST_SAMPLES_COUNT*2; i+=2) {
		/* Real part, make offset by ADC / 2 */
		Input[i] = (float32_t)(test_signal[i/2]);
	}


	for (i = 1; i < TEST_SAMPLES_COUNT*2; i+=2) {
		/* Imaginary part */
		Input[i] = 0;
	}

	/* Process the data through the CFFT/CIFFT module */
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, Input, 0, 1); //512 , 2x512 (512 complex points)

	/* Process the data through the Complex Magniture Module for calculating the magnitude at each bin */
	arm_cmplx_mag_f32(Input, Output, TEST_SAMPLES_COUNT); //2x array, full array

	/* Calculates maxValue and returns corresponding value */
	arm_max_f32(Output, TEST_SAMPLES_COUNT, &maxValue, &maxIndex); //full array, full length

	printf("START INPUT SIGNAL %d:\n", TEST_SAMPLES_COUNT);
	for (i = 0; i < TEST_SAMPLES_COUNT; i++) {
		printf("%f, ",  test_signal[i]);
	}
	printf("\n");
	printf("STOP INPUT SIGNAL\n\n");


	//retrive half
	printf("START MAGNITUDES %d:\n", TEST_SAMPLES_COUNT/2);
	for (i = 0; i < TEST_SAMPLES_COUNT/2; i++) {
		printf("%f, ",  Output[i]);
	}
	printf("\n");
	printf("STOP MAGNITUDES\n\n");


	//full to reconstruct
	printf("START REAL %d:\n", TEST_SAMPLES_COUNT);
	for (i = 0; i < TEST_SAMPLES_COUNT*2; i+=2) {
		printf("%f, ",  Input[i]);
	}
	printf("\n");
	printf("STOP REAL\n\n");


	//full to reconstruct
	printf("START IMAG %d:\n", TEST_SAMPLES_COUNT);
	for (i = 1; i < TEST_SAMPLES_COUNT*2; i+=2) {
		printf("%f, ",  Input[i]);
	}
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
	printf("STOP TEST! DONE %d ITERATIONS AND WITH %d FFT POINTS GOT %d Hz, T = %d US.\n", counter, TEST_SAMPLES_COUNT, (int)(counter*1000.0/delta_millis), (int)(delta_millis*1000.0/counter));








//
//
//
//
//
//
//	  arm_status status;
//	  float32_t maxValue;
//
//	  status = ARM_MATH_SUCCESS;
//
//	  /* Process the data through the CFFT/CIFFT module ee chyba zla dlugosc*/
//	  arm_cfft_f32(&arm_cfft_sR_f32_len256, test_signal, ifftFlag, doBitReverse);
//
//	  /* Process the data through the Complex Magnitude Module for
//	  calculating the magnitude at each bin */
//	  arm_cmplx_mag_f32(test_signal, testOutput, fftSize);
//
//	  /* Calculates maxValue and returns corresponding BIN value */
//	  arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);
//
////	  status = ARM_MATH_TEST_FAILURE;
//
//	  printf("Status %d\n", status);
//	  printf("ref %lu, test %lu\n", refIndex, testIndex);
//
//
////	  if (testIndex != refIndex)
////	  {
////
////	  }
//
//	  /* ----------------------------------------------------------------------
//	  ** Loop here if the signals fail the PASS check.
//	  ** This denotes a test failure
//	  ** ------------------------------------------------------------------- */
//
////	  if ( status == ARM_MATH_SUCCESS)
////	  {
////	    while (1);
////	  }

	  while (1);

}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

//  volatile static uint16_t value[2048];

//  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
//  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)value, 2048);
	printf("Hello!\n");

  benchmark();


  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
