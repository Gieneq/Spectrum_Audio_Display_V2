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
//https://community.st.com/s/article/configuring-dsp-libraries-on-stm32cubeide
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define INTERVAL 10000
#define TEST_SAMPLES_COUNT 256
const float test_signal[TEST_SAMPLES_COUNT] = {0.0, 0.007102672476321459, 0.0031590645667165518, 0.020411916077136993, 0.00803642999380827, 0.031317539513111115, 0.015804117545485497, 0.03907559812068939, 0.026715202257037163, 0.04394194856286049, 0.04002317786216736, 0.047090742737054825, 0.05421900376677513, 0.05024106800556183, 0.06751048564910889, 0.05511043593287468, 0.07839161902666092, 0.06286873668432236, 0.08612103015184402, 0.07376626133918762, 0.09095736593008041, 0.08705394715070724, 0.09407689422369003, 0.1012212410569191, 0.09719949960708618, 0.11447595059871674, 0.10204189270734787, 0.12531360983848572, 0.10977182537317276, 0.13299541175365448, 0.12063682079315186, 0.13778278231620789, 0.1338852494955063, 0.1408541053533554, 0.14800505340099335, 0.1439300775527954, 0.16120405495166779, 0.14872658252716064, 0.17197933793067932, 0.15640926361083984, 0.17959463596343994, 0.16722284257411957, 0.18431417644023895, 0.1804131418466568, 0.18731848895549774, 0.19446662068367004, 0.19032900035381317, 0.20759110152721405, 0.1950608342885971, 0.2182851880788803, 0.20267748832702637, 0.22581523656845093, 0.21342089772224426, 0.23044823110103607, 0.22653435170650482, 0.23336683213710785, 0.24050278961658478, 0.2362932413816452, 0.25353407859802246, 0.24094177782535553, 0.2641283869743347, 0.24847379326820374, 0.2715545892715454, 0.2591284513473511, 0.27608248591423035, 0.2721465229988098, 0.27889686822891235, 0.2860114276409149, 0.28172069787979126, 0.2989310324192047, 0.2862675189971924, 0.309407114982605, 0.29369649291038513, 0.31671109795570374, 0.3042440712451935, 0.3211155831813812, 0.3171484172344208, 0.3238074779510498, 0.3308914601802826, 0.3265105187892914, 0.3436812162399292, 0.33093738555908203, 0.3540208637714386, 0.3382452130317688, 0.3611845076084137, 0.34866756200790405, 0.3654475212097168, 0.36144012212753296, 0.3679988980293274, 0.3750433623790741, 0.37056317925453186, 0.38768523931503296, 0.3748522400856018, 0.39787060022354126, 0.3820210099220276, 0.40487605333328247, 0.3923003673553467, 0.4089798331260681, 0.40492337942123413, 0.41137298941612244, 0.4183690547943115, 0.4137808680534363, 0.4308454394340515, 0.4179145097732544, 0.44085893034935, 0.4249267280101776, 0.4476887285709381, 0.4350455701351166, 0.4516158401966095, 0.44750162959098816, 0.4538334310054779, 0.46077242493629456, 0.45606762170791626, 0.4730660617351532, 0.46002861857414246, 0.48289045691490173, 0.4668671190738678, 0.48952746391296387, 0.4768083393573761, 0.49326083064079285, 0.48908042907714844, 0.49528589844703674, 0.5021593570709229, 0.4973294734954834, 0.5142533183097839, 0.501101016998291, 0.5238718390464783, 0.5077490210533142, 0.5302993655204773, 0.5174959897994995, 0.5338223576545715, 0.5295674204826355, 0.5356383323669434, 0.5424379706382751, 0.5374748110771179, 0.5543158650398254, 0.5410405397415161, 0.5637121200561523, 0.5474817156791687, 0.5699138045310974, 0.5570181608200073, 0.5732102990150452, 0.56887286901474, 0.5748010873794556, 0.5815189480781555, 0.5764145255088806, 0.5931646823883057, 0.5797584056854248, 0.6023228168487549, 0.5859769582748413, 0.6082829236984253, 0.5952871441841125, 0.6113371849060059, 0.6069093942642212, 0.6126871705055237, 0.6193154454231262, 0.6140620708465576, 0.6307135820388794, 0.6171687245368958, 0.6396182179450989, 0.6231493353843689, 0.6453214883804321, 0.6322179436683655, 0.6481183171272278, 0.6435926556587219, 0.6492124795913696, 0.6557435989379883, 0.650333821773529, 0.6668792963027954, 0.6531884074211121, 0.6755155324935913, 0.6589162945747375, 0.6809471845626831, 0.6677287220954895, 0.6834719777107239, 0.678841233253479, 0.6842958331108093, 0.690722644329071, 0.6851491928100586, 0.7015814185142517, 0.6877374649047852, 0.7099350094795227, 0.6931983828544617, 0.715080976486206, 0.701740562915802, 0.7173197269439697, 0.7125769257545471, 0.7178592681884766, 0.7241748571395874, 0.7184309959411621, 0.7347429394721985, 0.7207391858100891, 0.7428003549575806, 0.7259195446968079, 0.7476470470428467, 0.7341779470443726, 0.7495863437652588, 0.7447248101234436, 0.7498283386230469, 0.756026029586792, 0.7501051425933838, 0.7662903666496277, 0.7521202564239502, 0.7740384936332703, 0.7570071816444397, 0.7785730361938477, 0.7649689316749573, 0.780200183391571, 0.7752135992050171, 0.780131995677948, 0.786205530166626, 0.7801013588905334, 0.7961536049842834, 0.781810998916626, 0.803580105304718, 0.7863921523094177, 0.8077903389930725, 0.7940452098846436, 0.809093177318573, 0.8039755821228027, 0.8087028861045837, 0.814646303653717, 0.8083530068397522, 0.8242663145065308, 0.8097454905509949, 0.8313596248626709, 0.8140093684196472, 0.8352339863777161, 0.8213421702384949, 0.8362011909484863, 0.8309469819068909, 0.8354775309562683, 0.8412852883338928, 0.8347973823547363, 0.8505662083625793, 0.8358616232872009, 0.8573153018951416, 0.8397973775863647, 0.8608430624008179, 0.8467993140220642, 0.8614640235900879, 0.8560678958892822, 0.8603965044021606, 0.8660633563995361, 0.8593756556510925, 0.8749948740005493, 0.8601015210151672, 0.8813896179199219, 0.8636990189552307, 0.884560763835907, 0.8703600168228149, 0.8848255276679993, 0.8792825937271118, 0.8834044337272644, 0.8889255523681641, 0.8820332884788513};

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

	arm_cfft_radix4_instance_f32 S;	/* ARM CFFT module */
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
	arm_cfft_radix4_init_f32(&S, FFT_SIZE, 0, 1);

	/* Process the data through the CFFT/CIFFT module */
	arm_cfft_radix4_f32(&S, Input);

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
		arm_cfft_radix4_f32(&S, Input);

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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
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
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
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
