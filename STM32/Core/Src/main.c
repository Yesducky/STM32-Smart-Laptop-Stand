/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "lcd.h"
#include "xpt2046.h"
#include "bsp_ov7725.h"
#include "bsp_sccb.h"
#include "stdio.h"
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
 TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;

SRAM_HandleTypeDef hsram1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_FSMC_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
volatile uint8_t Ov7725_vsync ;
#define TRIG_PIN GPIO_PIN_12
#define TRIG_PORT GPIOA
#define ECHO_PIN GPIO_PIN_11
#define ECHO_PORT GPIOA
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void led_blink(){
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_Delay(100);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_Delay(50);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_Delay(100);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_Delay(50);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_Delay(100);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_Delay(50);
}

void stepper_up(){
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);
	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1);
	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1);
}

void stepper_stop(){
	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
}

int fanspeed = 0;
int fan_speed_arr[4] = {0, 399, 699, 999};
int fan_mode = 0;
void fan(){
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, fan_speed_arr[3]);
	HAL_Delay(100);
	if(fanspeed == 0){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
		fanspeed = 1;
	}
	else if(fanspeed == 1){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
		fanspeed = 2;
	}
	else if(fanspeed == 2){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		fanspeed = 3;
	}
	else if(fanspeed == 3){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
		fanspeed = 0;
	}
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, fan_speed_arr[fanspeed]);
}

uint16_t i, j;
uint16_t Camera_Data;
uint8_t color1;
uint8_t color2;
uint8_t message[2];
uint8_t strK1[]="Pressed\n";
uint8_t str2[]="\nStop";
uint16_t Distance  = 0;
uint32_t pMillis;
uint32_t Value1 = 0;
uint32_t Value2 = 0;
int take_photo () {

		LCD_DisplayInterface1();
		HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);
		__HAL_TIM_SET_COUNTER(&htim1, 0);
		while (__HAL_TIM_GET_COUNTER (&htim1) < 10);
		HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);

		pMillis = HAL_GetTick();

		while (!(HAL_GPIO_ReadPin (ECHO_PORT, ECHO_PIN)) && pMillis + 10 >  HAL_GetTick());
		Value1 = __HAL_TIM_GET_COUNTER (&htim1);

		pMillis = HAL_GetTick();

		while ((HAL_GPIO_ReadPin (ECHO_PORT, ECHO_PIN)) && pMillis + 50 > HAL_GetTick());
		Value2 = __HAL_TIM_GET_COUNTER (&htim1);

		Distance = (Value2-Value1)* 0.034/2;
		HAL_Delay(50);
		uint8_t Rxstr[4] = "";
		int pixel_data = 0;
		int Calcu_data = 0;
		HAL_UART_Transmit(&huart1,strK1,sizeof(strK1)-1,100);
		if (Ov7725_vsync == 2)
		{
			FIFO_PREPARE;
			for(i = 0; i < 240; i++)
			{
				for(j = 0; j < 320; j++)
				{
					READ_FIFO_PIXEL(Camera_Data);
					color1 = (uint8_t) (Camera_Data);
					color2 = (uint8_t) (Camera_Data>>8);
					message[0] = color1;
					message[1] = color2;
					HAL_UART_Transmit(&huart1,message,2,100);
				}
			}
			HAL_UART_Transmit(&huart1,str2,sizeof(str2)-1,100);
			HAL_Delay(50);
			Ov7725_vsync = 0;
			int temp_time = HAL_GetTick();
			while (HAL_UART_Receive(&huart1,Rxstr,2,100) != HAL_OK && Check_mainsrc_touchkey() == 0);
			LCD_DisplayInterface2();
			sscanf(Rxstr, "%d", &pixel_data);
			if (pixel_data == 0) {LCD_DisplayInterface(); return 0;}
			Calcu_data = pixel_data + ((int)(Distance)-30)*2/40;
			if (Calcu_data > 25) {Calcu_data = 25;}
			else if (Calcu_data < 15) {Calcu_data = 15;}
			LCD_DisplayNum(Calcu_data);
			HAL_Delay(4000);
			LCD_DisplayInterface();

		}
		return Calcu_data;
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
  MX_FSMC_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  //LCD
  LCD_INIT();
  LCD_DisplayInterface();
  //timer
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_Base_Start(&htim1);
  HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);

  // camera
  while(Ov7725_Init() != SUCCESS){HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);}
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
  Ov7725_vsync = 0;

  //HMC5883L
//  char str3[] = "Z:";
//  char str6[10];
  char str7[10];
//
//  LCD_DrawString(50, 60, str3);

//  uint16_t HMC5883L_Addr = 0x1E;
//  uint8_t CRA = 0x70;
//  uint8_t CRB = 0xA0;
//  uint8_t mode = 0x00;
//  HAL_I2C_Mem_Write(&hi2c2,HMC5883L_Addr<<1,0x00,1,&CRA,1,100);
//  HAL_I2C_Mem_Write(&hi2c2,HMC5883L_Addr<<1,0x01,1,&CRB,1,100);
//  HAL_I2C_Mem_Write(&hi2c2,HMC5883L_Addr<<1,0x02,1,&mode,1,100);
//  int8_t mx, my, mz, lx, ly, lz, status;
//  int16_t z;
//  int init = 0;
//  int16_t init_z;
//  int counter_size = 50;
//  int counter = 0;

  //touch screeen
  int touch_received;

  //stepper
  int stepper_dir = 0;
  double current_height = 26;
  LCD_DisplayNum(current_height-1);
  current_height = 25.1;
  uint32_t timer_temp;
  int temp_height = current_height;
  int haveTarget = 0;
  int Calcu_Data = 0;


//  int rgb_state = 0;
//  uint16_t gpioPin[] = {GPIO_PIN_1, GPIO_PIN_5, GPIO_PIN_0};
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  touch_received = Check_mainsrc_touchkey();

	  //If stepper is moving, get the time update. If time change by 2, update height by 1.
	  if(stepper_dir != 0){
		  //adjust the last no. to get better range. Max: 2000
		  current_height += stepper_dir*(double)(HAL_GetTick()-timer_temp)/1950.0;
		  timer_temp = HAL_GetTick();

		  if(current_height >= 25 && stepper_dir == 1){
			  current_height = 25;
			  stepper_dir = 0;

			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
			  led_blink();
		  }

		  if(current_height <= 15 && stepper_dir == -1){
			  current_height = 15;
			  stepper_dir = 0;

			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
			  led_blink();
		  }


		  //have target
		  if(current_height >= Calcu_Data && stepper_dir == 1 && haveTarget){
			  current_height = Calcu_Data;
			  stepper_dir = 0;
			  haveTarget = 0;

			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
			  led_blink();
		  }

		  if(current_height <= Calcu_Data && stepper_dir == -1 && haveTarget){
			  current_height = Calcu_Data;
			  stepper_dir = 0;
			  haveTarget = 0;

			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
			  led_blink();
		  }


		 //update display
		  if((int)current_height != temp_height){
			  temp_height = current_height;
			  LCD_DisplayNum((int)current_height);
		  }

	  }



	  //stepper up down
	  //reset button
	  if(touch_received == 1){
		  fan();
	  }
	  // auto button
	  if(touch_received == 2){
		  Calcu_Data = take_photo();
		  LCD_DisplayNum(current_height);
		  if(Calcu_Data != 0){
			  haveTarget = 1;
			  if (Calcu_Data < current_height) {
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
				  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1);
				  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1);
				  stepper_dir = -1;
				  timer_temp = HAL_GetTick();
			  } else if (Calcu_Data > current_height) {
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);
				  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1);
				  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1);
				  stepper_dir = 1;
				  timer_temp = HAL_GetTick();
			  }
		  }

	  }
	  //up button
	  if(touch_received == 3){
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1);
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1);
		  stepper_dir = 1;
		  timer_temp = HAL_GetTick();
	  }
	  //down button
	  if(touch_received == 4){
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1);
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1);
		  stepper_dir = -1;
		  timer_temp = HAL_GetTick();
	  }
	  //pause button
	  if(touch_received == 5){
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
		  stepper_dir = 0;
		  timer_temp = HAL_GetTick();
	  }


//	  HAL_I2C_Mem_Read(&hi2c2,HMC5883L_Addr<<1,0x09,1,&status,1,100);
//	  if(status%2 == 0){
//		  continue;
//	  }
//
//
//	  HAL_I2C_Mem_Read(&hi2c2,HMC5883L_Addr<<1,0x03,1,&mx,1,100);
//	  HAL_I2C_Mem_Read(&hi2c2,HMC5883L_Addr<<1,0x04,1,&lx,1,100);
//	  HAL_I2C_Mem_Read(&hi2c2,HMC5883L_Addr<<1,0x05,1,&mz,1,100);
//	  HAL_I2C_Mem_Read(&hi2c2,HMC5883L_Addr<<1,0x06,1,&lz,1,100);
//	  HAL_I2C_Mem_Read(&hi2c2,HMC5883L_Addr<<1,0x07,1,&my,1,100);
//	  HAL_I2C_Mem_Read(&hi2c2,HMC5883L_Addr<<1,0x08,1,&ly,1,100);
//
//	  z = lz + (mz << 8);
//	  if(init == 0){
//		  init_z = z;
//		  init = 1;
//	  }
//	  z = z-init_z;
//	  int t = 25+z;
//	  snprintf(str6,5,"%d", t);
//	  snprintf(str7,5,"%d", adc_value);
//	  LCD_Clear(70,60,50,40,0xFFFF);
//	  LCD_DrawString(70, 60, str6);
//	  LCD_DrawString(70, 80, str7);

//	  if(counter == 0){
//		  LCD_DisplayNum(temp_d);
//		  counter = counter_size;
//	  }
//	  counter--;


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
  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_1);
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 71;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 719;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 49;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 7199;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LCD_TP_Pin|dir1_Pin|dir2_Pin|LCD_TPE0_Pin
                          |LCD_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, onboard_led_Pin|onboard_ledB1_Pin|onboard_ledB5_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LCD_BL_Pin|LCD_TPD13_Pin|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, fan_state_Pin|fan_stateC10_Pin|fan_stateC11_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LCD_TP_Pin dir1_Pin dir2_Pin LCD_TPE0_Pin
                           LCD_RST_Pin */
  GPIO_InitStruct.Pin = LCD_TP_Pin|dir1_Pin|dir2_Pin|LCD_TPE0_Pin
                          |LCD_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_TPE3_Pin */
  GPIO_InitStruct.Pin = LCD_TPE3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LCD_TPE3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_TP_EXT14_Pin */
  GPIO_InitStruct.Pin = LCD_TP_EXT14_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LCD_TP_EXT14_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : key2_Pin */
  GPIO_InitStruct.Pin = key2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(key2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : key1_Pin */
  GPIO_InitStruct.Pin = key1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(key1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC4 PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : onboard_led_Pin onboard_ledB1_Pin onboard_ledB5_Pin */
  GPIO_InitStruct.Pin = onboard_led_Pin|onboard_ledB1_Pin|onboard_ledB5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 PB12 PB13
                           PB14 PB15 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_BL_Pin LCD_TPD13_Pin PD3 */
  GPIO_InitStruct.Pin = LCD_BL_Pin|LCD_TPD13_Pin|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : btn_Pin */
  GPIO_InitStruct.Pin = btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : fan_state_Pin fan_stateC10_Pin fan_stateC11_Pin */
  GPIO_InitStruct.Pin = fan_state_Pin|fan_stateC10_Pin|fan_stateC11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* FSMC initialization function */
static void MX_FSMC_Init(void)
{

  /* USER CODE BEGIN FSMC_Init 0 */

  /* USER CODE END FSMC_Init 0 */

  FSMC_NORSRAM_TimingTypeDef Timing = {0};

  /* USER CODE BEGIN FSMC_Init 1 */

  /* USER CODE END FSMC_Init 1 */

  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FSMC_NORSRAM_DEVICE;
  hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FSMC_NORSRAM_BANK1;
  hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 15;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 255;
  Timing.BusTurnAroundDuration = 15;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Disconnect NADV
  */

  __HAL_AFIO_FSMCNADV_DISCONNECTED();

  /* USER CODE BEGIN FSMC_Init 2 */

  /* USER CODE END FSMC_Init 2 */
}

/* USER CODE BEGIN 4 */
int step_counter(){

}
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
