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

//Docs : https://arm-software.github.io/CMSIS_5/DSP/html/group__ComplexFFT.html#gade0f9c4ff157b6b9c72a1eafd86ebf80

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define INTERVAL 10000
#define TEST_SAMPLES_COUNT 512
const float test_signal[TEST_SAMPLES_COUNT] = {0.0, 0.0325, -0.0455, 0.0885, -0.0739, 0.1204, -0.0733, 0.1209, -0.0412, 0.0925, 0.0148, 0.0469, 0.0797, 0.0014, 0.1356, -0.0268, 0.1675, -0.0262, 0.1679, 0.0059, 0.1394, 0.062, 0.0938, 0.1269, 0.0483, 0.1827, 0.02, 0.2144, 0.0207, 0.2147, 0.0529, 0.1861, 0.1089, 0.1404, 0.1738, 0.0949, 0.2295, 0.0667, 0.2611, 0.0674, 0.2612, 0.0996, 0.2325, 0.1556, 0.1868, 0.2204, 0.1412, 0.276, 0.1129, 0.3075, 0.1137, 0.3074, 0.1458, 0.2785, 0.2018, 0.2327, 0.2665, 0.187, 0.322, 0.1588, 0.3533, 0.1595, 0.3531, 0.1916, 0.324, 0.2476, 0.278, 0.3122, 0.2323, 0.3675, 0.204, 0.3986, 0.2047, 0.3982, 0.2369, 0.369, 0.2927, 0.3228, 0.3572, 0.277, 0.4124, 0.2486, 0.4432, 0.2493, 0.4426, 0.2814, 0.4132, 0.3372, 0.3669, 0.4015, 0.3209, 0.4565, 0.2925, 0.4871, 0.2931, 0.4862, 0.3251, 0.4566, 0.3808, 0.4101, 0.445, 0.364, 0.4997, 0.3355, 0.5301, 0.336, 0.529, 0.3679, 0.4991, 0.4235, 0.4524, 0.4875, 0.4062, 0.542, 0.3776, 0.5722, 0.378, 0.5708, 0.4098, 0.5406, 0.4652, 0.4937, 0.529, 0.4473, 0.5833, 0.4186, 0.6132, 0.4189, 0.6115, 0.4506, 0.5811, 0.5058, 0.5339, 0.5694, 0.4874, 0.6235, 0.4585, 0.653, 0.4587, 0.651, 0.4902, 0.6203, 0.5453, 0.573, 0.6086, 0.5262, 0.6624, 0.4971, 0.6917, 0.4972, 0.6893, 0.5286, 0.6583, 0.5834, 0.6107, 0.6466, 0.5637, 0.7, 0.5345, 0.729, 0.5344, 0.7263, 0.5656, 0.695, 0.6203, 0.6471, 0.6831, 0.5999, 0.7363, 0.5704, 0.7649, 0.5702, 0.7619, 0.6012, 0.7302, 0.6557, 0.682, 0.7183, 0.6346, 0.7711, 0.6049, 0.7993, 0.6045, 0.7959, 0.6353, 0.764, 0.6895, 0.7155, 0.7518, 0.6677, 0.8043, 0.6379, 0.8322, 0.6372, 0.8284, 0.6678, 0.7961, 0.7218, 0.7473, 0.7838, 0.6993, 0.836, 0.6692, 0.8635, 0.6683, 0.8593, 0.6987, 0.8266, 0.7524, 0.7774, 0.8141, 0.7292, 0.8659, 0.6988, 0.893, 0.6977, 0.8885, 0.7279, 0.8554, 0.7813, 0.8059, 0.8427, 0.7573, 0.8941, 0.7267, 0.9208, 0.7254, 0.9158, 0.7553, 0.8824, 0.8084, 0.8325, 0.8695, 0.7836, 0.9205, 0.7528, 0.9468, 0.7512, 0.9414, 0.7808, 0.9075, 0.8337, 0.8573, 0.8944, 0.8081, 0.945, 0.777, 0.9709, 0.7751, 0.965, 0.8045, 0.9307, 0.857, 0.8802, 0.9174, 0.8307, 0.9676, 0.7992, 0.993, 0.7971, 0.9868, 0.8262, 0.952, 0.8784, 0.9011, 0.9384, 0.8512, 0.9882, 0.8195, 1.0132, 0.8171, 1.0065, 0.8459, 0.9713, 0.8978, 0.92, 0.9574, 0.8698, 1.0068, 0.8378, 1.0313, 0.8351, 1.0242, 0.8636, 0.9886, 0.9152, 0.9368, 0.9744, 0.8863, 1.0234, 0.8539, 1.0474, 0.851, 1.0398, 0.8792, 1.0037, 0.9304, 0.9516, 0.9893, 0.9007, 1.0378, 0.868, 1.0614, 0.8648, 1.0533, 0.8927, 1.0168, 0.9436, 0.9642, 1.002, 0.9129, 1.0501, 0.88, 1.0732, 0.8764, 1.0646, 0.904, 1.0277, 0.9546, 0.9747, 1.0126, 0.9231, 1.0603, 0.8898, 1.0829, 0.8859, 1.0738, 0.9132, 1.0364, 0.9634, 0.983, 1.021, 0.931, 1.0682, 0.8974, 1.0904, 0.8932, 1.0808, 0.9201, 1.0429, 0.97, 0.9891, 1.0272, 0.9367, 1.074, 0.9028, 1.0956, 0.8983, 1.0856, 0.9249, 1.0472, 0.9744, 0.993, 1.0313, 0.9403, 1.0775, 0.906, 1.0987, 0.9012, 1.0882, 0.9275, 1.0494, 0.9766, 0.9947, 1.0331, 0.9416, 1.0789, 0.907, 1.0996, 0.9019, 1.0885, 0.9278, 1.0493, 0.9766, 0.9942, 1.0326, 0.9407, 1.078, 0.9057, 1.0982, 0.9003, 1.0867, 0.926, 1.0469, 0.9744, 0.9914, 1.03, 0.9376, 1.0749, 0.9023, 1.0946, 0.8965, 1.0826, 0.9219, 1.0424, 0.9699, 0.9865, 1.0251, 0.9322, 1.0696, 0.8966, 1.0888, 0.8906, 1.0763, 0.9156, 1.0357, 0.9633, 0.9793, 1.0181, 0.9247, 1.0621, 0.8888, 1.0808, 0.8824, 1.0679, 0.9071, 1.0267, 0.9544, 0.97, 1.0088, 0.915, 1.0524, 0.8787, 1.0707, 0.872, 1.0572, 0.8964, 1.0156, 0.9434, 0.9584, 0.9974, 0.9031, 1.0406, 0.8665, 1.0584, 0.8595, 1.0444, 0.8836, 1.0024, 0.9303, 0.9448, 0.9839, 0.8891, 1.0266, 0.8522, 1.0439, 0.8449, 1.0295, 0.8687, 0.987, 0.915, 0.929, 0.9682, 0.873, 1.0105, 0.8358, 1.0274, 0.8282, 1.0125, 0.8517, 0.9695, 0.8976, 0.9112, 0.9505, 0.8548, 0.9923, 0.8173, 1.0087, 0.8094, 0.9934, 0.8326, 0.9501, 0.8783, 0.8913, 0.9307, 0.8346, 0.9721, 0.7968, 0.9881, 0.7886, 0.9723, 0.8115, 0.9286, 0.8569, 0.8694, 0.909, 0.8124, 0.95, 0.7743, 0.9655, 0.7659, 0.9493, 0.7885, 0.9051, 0.8335, 0.8456, 0.8853, 0.7882, 0.9259, 0.7499, 0.941, 0.7412, 0.9243, 0.7636, 0.8797, 0.8083, 0.8199, 0.8597, 0.7622, 0.8999, 0.7236, 0.9146};

#define SAMPLES					TEST_SAMPLES_COUNT*2 	/* TEST_SAMPLES_COUNT real party and TEST_SAMPLES_COUNT imaginary parts */
#define FFT_SIZE				TEST_SAMPLES_COUNT		/* FFT size is always the same size as we have samples, so TEST_SAMPLES_COUNT in our case */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
int __io_putchar(int ch)
{
  if (ch == '\n') {
    __io_putchar('\r');
  }

  HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);

  return 1;
}

float32_t Input[SAMPLES];
float32_t Output[FFT_SIZE];
int led = 0;


void benchmark(){
//	https://www.keil.com/pack/doc/CMSIS/DSP/html/group__ComplexFFT.html
	arm_cfft_instance_f32 S;	/* ARM CFFT module */
	float32_t maxValue;				/* Max FFT value is stored here */
	uint32_t maxIndex;				/* Index in Output array where max value is */
	int i = 0;

	for (i = 0; i < SAMPLES; i+=2) {
		/* Real part, make offset by ADC / 2 */
		Input[i] = (float32_t)(test_signal[i/2]);
	}

	for (i = 1; i < SAMPLES; i+=2) {
		/* Imaginary part */
		Input[i] = 0;
	}

	/* Initialize the CFFT/CIFFT module, intFlag = 0, doBitReverse = 1 */
	//arm_cfft_radix4_init_f32(&S, FFT_SIZE, 0, 1);

	/* Process the data through the CFFT/CIFFT module */
	//arm_cfft_radix4_f32(&S, Input);
	arm_cfft_f32(&S, Input, 0, 1);

	/* Process the data through the Complex Magniture Module for calculating the magnitude at each bin */
	arm_cmplx_mag_f32(Input, Output, FFT_SIZE);

	/* Calculates maxValue and returns corresponding value */
	arm_max_f32(Output, FFT_SIZE, &maxValue, &maxIndex);

	printf("START INPUT SIGNAL %d:\n", TEST_SAMPLES_COUNT);
	for (i = 0; i < TEST_SAMPLES_COUNT; i++) {
		printf("%f, ",  test_signal[i]);
	}
	printf("\n");
	printf("STOP INPUT SIGNAL\n\n");


	printf("START MAGNITUDES %d:\n", FFT_SIZE / 2);
	for (i = 0; i < FFT_SIZE / 2; i++) {
		printf("%f, ",  Output[i]);
	}
	printf("\n");
	printf("STOP MAGNITUDES\n\n");


	printf("START REAL %d:\n", SAMPLES / 2);
	for (i = 0; i < SAMPLES; i+=2) {
		printf("%f, ",  Input[i]);
	}
	printf("\n");
	printf("STOP REAL\n\n");


	printf("START IMAG %d:\n", SAMPLES / 2);
	for (i = 1; i < SAMPLES; i+=2) {
		printf("%f, ",  Input[i]);
	}
	printf("\n");
	printf("STOP IMAG\n\n");


	printf("START TEST, IT WILL TAKE %d MS...\n", INTERVAL);
	uint32_t start_millis = HAL_GetTick();
	float delta_millis = 0;
	int counter = 0;

	while(HAL_GetTick() - start_millis < INTERVAL) {
		/* Process the data through the CFFT/CIFFT module */
//		arm_cfft_radix4_f32(&S, Input);

		/* Process the data through the Complex Magniture Module for calculating the magnitude at each bin */
		arm_cmplx_mag_f32(Input, Output, FFT_SIZE);

		/* Calculates maxValue and returns corresponding value */
		arm_max_f32(Output, FFT_SIZE, &maxValue, &maxIndex);
		++counter;
	}

	delta_millis = HAL_GetTick() - start_millis;
	printf("STOP TEST! DONE %d ITERATIONS AND WITH %d FFT POINTS GOT %d Hz, T = %d US.\n", counter, FFT_SIZE, (int)(counter*1000.0/delta_millis), (int)(delta_millis*1000.0/counter));

}


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const float fs = 1.0 * 36e6/(601.5 + 12.5);

//HAL_ADC
/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption and DMA) */
//void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);
//void                    HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
//void                    HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc);
//void                    HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc);
//void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);

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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  volatile static uint16_t value[2048];

  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)value, 2048);

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

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
