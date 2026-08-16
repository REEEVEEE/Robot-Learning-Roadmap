/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "FreeRTOS.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can_bus.h"
#include "m3508.h"
#include "motor_manager.h"
#include "pid.h"
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
CanRxMessage_t CanRxMessage;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for CanRxTask */
osThreadId_t CanRxTaskHandle;
const osThreadAttr_t CanRxTask_attributes = {
  .name = "CanRxTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for MotorControlTas */
osThreadId_t MotorControlTasHandle;
const osThreadAttr_t MotorControlTas_attributes = {
  .name = "MotorControlTas",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for CanRxQueue */
osMessageQueueId_t CanRxQueueHandle;
const osMessageQueueAttr_t CanRxQueue_attributes = {
  .name = "CanRxQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartCanRxTask(void *argument);
void StartMotorControlTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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

  /* Create the queue(s) */
  /* creation of CanRxQueue */
  CanRxQueueHandle = osMessageQueueNew (16, sizeof(CanRxMessage_t), &CanRxQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of CanRxTask */
  CanRxTaskHandle = osThreadNew(StartCanRxTask, NULL, &CanRxTask_attributes);

  /* creation of MotorControlTas */
  MotorControlTasHandle = osThreadNew(StartMotorControlTask, NULL, &MotorControlTas_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  CAN_Init();

  PID_Init(&motor_pid_1, 0, 0, 0, 0.001f, 2000, 2000);
  PID_Init(&motor_pid_2, 0, 0, 0, 0.001f, 2000, 2000);
  PID_Init(&motor_pid_3, 0, 0, 0, 0.001f, 2000, 2000);
  PID_Init(&motor_pid_4, 0, 0, 0, 0.001f, 2000, 2000);

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartCanRxTask */
/**
* @brief Function implementing the CanRxTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCanRxTask */
void StartCanRxTask(void *argument)
{
  /* USER CODE BEGIN StartCanRxTask */
  /* Infinite loop */
  for(;;)
  {
      osStatus_t status = osMessageQueueGet(CanRxQueueHandle, &CanRxMessage, NULL, osWaitForever);
      if (status == osOK) {
          switch (CanRxMessage.id) {
              case 0x201:
                  M3508_UpdateFeedback(&motor_1, CanRxMessage.data);
                  break;
              case 0x202:
                  M3508_UpdateFeedback(&motor_2, CanRxMessage.data);
                  break;
              case 0x203:
                  M3508_UpdateFeedback(&motor_3, CanRxMessage.data);
                  break;
              case 0x204:
                  M3508_UpdateFeedback(&motor_4, CanRxMessage.data);
                  break;
          }
      }
  }
  /* USER CODE END StartCanRxTask */
}

/* USER CODE BEGIN Header_StartMotorControlTask */
/**
* @brief Function implementing the MotorControlTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMotorControlTask */
void StartMotorControlTask(void *argument)
{
  /* USER CODE BEGIN StartMotorControlTask */
  uint32_t last_wake_time = osKernelGetTickCount();
  /* Infinite loop */
  for(;;)
  {
    motor_1.targetCurrent = (int16_t)PID_Calculate(&motor_pid_1, motor_1.targetSpeed, motor_1.speed);
    motor_2.targetCurrent = (int16_t)PID_Calculate(&motor_pid_2, motor_2.targetSpeed, motor_2.speed);
    motor_3.targetCurrent = (int16_t)PID_Calculate(&motor_pid_3, motor_3.targetSpeed, motor_3.speed);
    motor_4.targetCurrent = (int16_t)PID_Calculate(&motor_pid_4, motor_4.targetSpeed, motor_4.speed);

    M3508_SendCurrent(&motor_1, &motor_2, &motor_3, &motor_4);

    last_wake_time += 1;
    osDelayUntil(last_wake_time);
  }
  /* USER CODE END StartMotorControlTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

