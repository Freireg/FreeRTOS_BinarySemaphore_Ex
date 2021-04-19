/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
osThreadId NormalTaskHandle;
osThreadId HighTaskHandle;
osThreadId LowTaskHandle;
osSemaphoreId BinSemHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Startnormaltask(void const * argument);
void Starthightask(void const * argument);
void Startlowtask(void const * argument);

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

  /* Create the semaphores(s) */
  /* definition and creation of BinSem */
  osSemaphoreDef(BinSem);
  BinSemHandle = osSemaphoreCreate(osSemaphore(BinSem), 1);

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
  /* definition and creation of NormalTask */
  osThreadDef(NormalTask, Startnormaltask, osPriorityNormal, 0, 128);
  NormalTaskHandle = osThreadCreate(osThread(NormalTask), NULL);

  /* definition and creation of HighTask */
  osThreadDef(HighTask, Starthightask, osPriorityAboveNormal, 0, 128);
  HighTaskHandle = osThreadCreate(osThread(HighTask), NULL);

  /* definition and creation of LowTask */
  osThreadDef(LowTask, Startlowtask, osPriorityBelowNormal, 0, 128);
  LowTaskHandle = osThreadCreate(osThread(LowTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Startnormaltask */
/**
  * @brief  Function implementing the NormalTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Startnormaltask */
void Startnormaltask(void const * argument)
{
  /* USER CODE BEGIN Startnormaltask */
  /* Infinite loop */
  for(;;)
  {

	  osSemaphoreWait(BinSemHandle, osWaitForever);
	  char *str1 = "Entered NormalTask\n";
	  HAL_UART_Transmit(&huart2, (uint8_t*) str1, strlen(str1), 100);


	  char *str3 = "Waiting button to be pressed\n";
	  HAL_UART_Transmit(&huart2, (uint8_t*) str3, strlen(str3), 100);

	  while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));

	  char *str2 = "Leaving NormalTask\n\n";
	  HAL_UART_Transmit(&huart2, (uint8_t*) str2, strlen(str2), 100);

	  osSemaphoreRelease(BinSemHandle);
	  osDelay(1000);
  }
  /* USER CODE END Startnormaltask */
}

/* USER CODE BEGIN Header_Starthightask */
/**
* @brief Function implementing the HighTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Starthightask */
void Starthightask(void const * argument)
{
  /* USER CODE BEGIN Starthightask */
  /* Infinite loop */
  for(;;)
  {
	  osSemaphoreWait(BinSemHandle, osWaitForever);
	  char *str1 = "Entered HighTask\n";
	  HAL_UART_Transmit(&huart2, (uint8_t*) str1, strlen(str1), 100);

	  char *str3 = "Waiting button to be pressed\n";
	  HAL_UART_Transmit(&huart2, (uint8_t*) str3, strlen(str3), 100);

	  while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));

	  char *str2 = "Leaving HighTask\n\n";
	  HAL_UART_Transmit(&huart2, (uint8_t*) str2, strlen(str2), 100);

	  osSemaphoreRelease(BinSemHandle);
	  osDelay(1000);
  }
  /* USER CODE END Starthightask */
}

/* USER CODE BEGIN Header_Startlowtask */
/**
* @brief Function implementing the LowTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Startlowtask */
void Startlowtask(void const * argument)
{
  /* USER CODE BEGIN Startlowtask */
  /* Infinite loop */
  for(;;)
  {
	  osSemaphoreWait(BinSemHandle, osWaitForever);
	  char *str1 = "Entered LowTask\n";
	  HAL_UART_Transmit(&huart2, (uint8_t*) str1, strlen(str1), 100);

	  char *str3 = "Waiting button to be pressed\n";
	  HAL_UART_Transmit(&huart2, (uint8_t*) str3, strlen(str3), 100);

	  while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));

	  char *str2 = "Leaving LowTask\n\n";
	  HAL_UART_Transmit(&huart2, (uint8_t*) str2, strlen(str2), 100);
	  osDelay(1000);
  }
  /* USER CODE END Startlowtask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
