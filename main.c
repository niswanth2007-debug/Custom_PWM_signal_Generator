/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
uint16_t x1,d1,d2;
uint8_t r, c, i, j;
uint8_t b[4][3] = {{1,2,3},{4,5,6},{7,8,9},{0,0,0}};
uint16_t row[4] = {GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4};
uint16_t co[3]  = {GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t Keypad_WaitForKey(void)
{


    while (1) {
        for (r = 0; r < 4; r++) {
            // set all rows HIGH
            for (i = 0; i < 4; i++)
                HAL_GPIO_WritePin(GPIOA, row[i], GPIO_PIN_SET);

            // pull current row LOW
            HAL_GPIO_WritePin(GPIOA, row[r], GPIO_PIN_RESET);
            HAL_Delay(5);

            for (c = 0; c < 3; c++) {
                if (HAL_GPIO_ReadPin(GPIOA, co[c]) == GPIO_PIN_RESET) {
                    // wait for key release
                    while (HAL_GPIO_ReadPin(GPIOA, co[c]) == GPIO_PIN_RESET);
                    HAL_Delay(20);
                    return b[r][c];
                }
            }
        }
    }
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(100);

  GPIOB->ODR &= ~(0xFF << 3);
    GPIOB->ODR |=  (0x38 << 3);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0); // RS=0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1); // E=1
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0); // E=0
    HAL_Delay(5);

    GPIOB->ODR &= ~(0xFF << 3);
    GPIOB->ODR |=  (0x38 << 3);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
    HAL_Delay(5);

    GPIOB->ODR &= ~(0xFF << 3);
    GPIOB->ODR |=  (0x38 << 3);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
    HAL_Delay(5);

    // --- 0x08 display OFF ---
    GPIOB->ODR &= ~(0xFF << 3);
    GPIOB->ODR |=  (0x08 << 3);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
    HAL_Delay(5);

    // --- 0x01 clear display ---
    GPIOB->ODR &= ~(0xFF << 3);
    GPIOB->ODR |=  (0x01 << 3);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
    HAL_Delay(5);

    // --- 0x06 entry mode ---
    GPIOB->ODR &= ~(0xFF << 3);
    GPIOB->ODR |=  (0x06 << 3);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
    HAL_Delay(5);

    // --- 0x0C display ON cursor OFF ---
    GPIOB->ODR &= ~(0xFF << 3);
    GPIOB->ODR |=  (0x0C << 3);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
    HAL_Delay(5);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  TIM2->CCR1 = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
	 		    d1 = Keypad_WaitForKey();
	 		    // LED ON briefly = 1st digit received
	 		    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
	 		    HAL_Delay(1000);
	 		    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
	 		    // --- Step 2: Wait for second digit ---
	 		    d2 = Keypad_WaitForKey();
	 		    // LED ON briefly = 2nd digit received
	 		    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
	 		    HAL_Delay(1000);
	 		    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
	 		    // --- Step 3: Compute and apply ---
	 		    x1 = (d1 * 10) + d2;
	 		    if (x1 > 100) x1 = 100;    // clamp to 100%
	 		    TIM2->CCR1 = x1 * 120;
	 		    // Long blink = duty cycle applied
	 		    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
	 		      d1 = Keypad_WaitForKey();

	 		      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
	 		      HAL_Delay(1000);
	 		      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);

	 		      d2 = Keypad_WaitForKey();

	 		      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
	 		      HAL_Delay(1000);
	 		      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);

	 		      x1 = (d1 * 10) + d2;
	 		      if (x1 > 100) x1 = 100;
	 		      TIM2->CCR1 = x1 * 360;

	 		      // --- LCD clear ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  (0x01 << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0); // RS=0
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1); // E=1
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0); // E=0
	 		      HAL_Delay(5);

	 		      // --- cursor to row1 col0 (0x80) ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  (0x80 << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0); // RS=0
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1); // E=1
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0); // E=0
	 		      HAL_Delay(5);

	 		      // --- print 'D' ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  ('D' << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1); // RS=1
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1); // E=1
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0); // E=0
	 		      HAL_Delay(5);

	 		      // --- print 'U' ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  ('U' << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		      HAL_Delay(5);

	 		      // --- print 'T' ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  ('T' << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		      HAL_Delay(5);

	 		      // --- print 'Y' ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  ('Y' << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		      HAL_Delay(5);

	 		     GPIOB->ODR &= ~(0xFF << 3);
	 		         GPIOB->ODR |=  (' ' << 3);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		         HAL_Delay(10);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		         HAL_Delay(5);

	 		         // --- print 'C' ---
	 		         GPIOB->ODR &= ~(0xFF << 3);
	 		         GPIOB->ODR |=  ('C' << 3);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		         HAL_Delay(10);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		         HAL_Delay(5);

	 		         // --- print 'Y' ---
	 		         GPIOB->ODR &= ~(0xFF << 3);
	 		         GPIOB->ODR |=  ('Y' << 3);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		         HAL_Delay(10);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		         HAL_Delay(5);

	 		         // --- print 'C' ---
	 		         GPIOB->ODR &= ~(0xFF << 3);
	 		         GPIOB->ODR |=  ('C' << 3);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		         HAL_Delay(10);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		         HAL_Delay(5);

	 		         // --- print 'L' ---
	 		         GPIOB->ODR &= ~(0xFF << 3);
	 		         GPIOB->ODR |=  ('L' << 3);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		         HAL_Delay(10);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		         HAL_Delay(5);

	 		         // --- print 'E' ---
	 		         GPIOB->ODR &= ~(0xFF << 3);
	 		         GPIOB->ODR |=  ('E' << 3);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		         HAL_Delay(10);
	 		         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		         HAL_Delay(5);
	 		      // --- print ':' ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  (':' << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		      HAL_Delay(5);

	 		      // --- print ' ' ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  (' ' << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		      HAL_Delay(5);

	 		      // --- print tens digit ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  (('0' + (x1 / 10)) << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		      HAL_Delay(5);

	 		      // --- print units digit ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  (('0' + (x1 % 10)) << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		      HAL_Delay(5);

	 		      // --- print '%' ---
	 		      GPIOB->ODR &= ~(0xFF << 3);
	 		      GPIOB->ODR |=  ('%' << 3);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	 		      HAL_Delay(10);
	 		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	 		      HAL_Delay(5);

	 		      HAL_Delay(1000);
	 		      HAL_Delay(5000);
	 		    HAL_Delay(1000);
	 		   // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
	 		    HAL_Delay(5000 );
  /* USER CODE END 3 */
}}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 35999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB3 PB4 PB5
                           PB6 PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
