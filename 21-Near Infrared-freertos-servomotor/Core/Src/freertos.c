/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "PWR_ON_OFF.h"
#include "Control_fan.h"
#include "Display_temperature.h"
#include "string.h"
#include "stdio.h"
#include "sys.h"
#include "usart.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId LED_TaskHandle;
osThreadId PWR_TaskHandle;
osThreadId Display_temperaHandle;
osThreadId Control_fan_TasHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_LED_Task(void const * argument);
void Start_PWR_Task(void const * argument);
void Start_Display_temperature_Task(void const * argument);
void Start_Control_fan_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of LED_Task */
  osThreadDef(LED_Task, Start_LED_Task, osPriorityBelowNormal, 0, 128);
  LED_TaskHandle = osThreadCreate(osThread(LED_Task), NULL);

  /* definition and creation of PWR_Task */
  osThreadDef(PWR_Task, Start_PWR_Task, osPriorityNormal, 0, 128);
  PWR_TaskHandle = osThreadCreate(osThread(PWR_Task), NULL);

  /* definition and creation of Display_tempera */
  osThreadDef(Display_tempera, Start_Display_temperature_Task, osPriorityBelowNormal, 0, 128);
  Display_temperaHandle = osThreadCreate(osThread(Display_tempera), NULL);

  /* definition and creation of Control_fan_Tas */
  osThreadDef(Control_fan_Tas, Start_Control_fan_Task, osPriorityBelowNormal, 0, 128);
  Control_fan_TasHandle = osThreadCreate(osThread(Control_fan_Tas), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Start_LED_Task */
/**
  * @brief  Function implementing the LED_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_LED_Task */
void Start_LED_Task(void const * argument)
{
  /* USER CODE BEGIN Start_LED_Task */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
	  HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	  osDelay(500);
  }
  /* USER CODE END Start_LED_Task */
}

/* USER CODE BEGIN Header_Start_PWR_Task */
/**
* @brief Function implementing the PWR_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_PWR_Task */
void Start_PWR_Task(void const * argument)
{
  /* USER CODE BEGIN Start_PWR_Task */
  /* Infinite loop */
  for(;;)
  {
      PWR_ON_OFF();
	  osDelay(20);
  }
  /* USER CODE END Start_PWR_Task */
}

/* USER CODE BEGIN Header_Start_Display_temperature_Task */
/**
* @brief Function implementing the Display_tempera thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Display_temperature_Task */
void Start_Display_temperature_Task(void const * argument)
{
  /* USER CODE BEGIN Start_Display_temperature_Task */
  /* Infinite loop */
  for(;;)
  {
	  Display_temperature();
//	  printf("wset numTf.valf -2.32\r\n");
//	  osDelay(100);
//	  printf("wset numTf.valf 26.36\r\n");
	  osDelay(100);
  }
  /* USER CODE END Start_Display_temperature_Task */
}

/* USER CODE BEGIN Header_Start_Control_fan_Task */
/**
* @brief Function implementing the Control_fan_Tas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Control_fan_Task */
void Start_Control_fan_Task(void const * argument)
{
  /* USER CODE BEGIN Start_Control_fan_Task */
  /* Infinite loop */
  for(;;)
  {
     Control_fan();
     osDelay(200);
  }
  /* USER CODE END Start_Control_fan_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
