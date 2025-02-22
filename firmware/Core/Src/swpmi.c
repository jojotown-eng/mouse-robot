/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    swpmi.c
  * @brief   This file provides code for the configuration
  *          of the SWPMI instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "swpmi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SWPMI_HandleTypeDef hswpmi1;

/* SWPMI1 init function */
void MX_SWPMI1_Init(void)
{

  /* USER CODE BEGIN SWPMI1_Init 0 */

  /* USER CODE END SWPMI1_Init 0 */

  /* USER CODE BEGIN SWPMI1_Init 1 */

  /* USER CODE END SWPMI1_Init 1 */
  hswpmi1.Instance = SWPMI1;
  hswpmi1.Init.VoltageClass = SWPMI_VOLTAGE_CLASS_B;
  hswpmi1.Init.BitRate = 0;
  hswpmi1.Init.TxBufferingMode = SWPMI_TX_NO_SOFTWAREBUFFER;
  hswpmi1.Init.RxBufferingMode = SWPMI_RX_NO_SOFTWAREBUFFER;
  if (HAL_SWPMI_Init(&hswpmi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SWPMI1_Init 2 */

  /* USER CODE END SWPMI1_Init 2 */

}

void HAL_SWPMI_MspInit(SWPMI_HandleTypeDef* swpmiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(swpmiHandle->Instance==SWPMI1)
  {
  /* USER CODE BEGIN SWPMI1_MspInit 0 */

  /* USER CODE END SWPMI1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SWPMI1;
    PeriphClkInit.Swpmi1ClockSelection = RCC_SWPMI1CLKSOURCE_PCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* SWPMI1 clock enable */
    __HAL_RCC_SWPMI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SWPMI1 GPIO Configuration
    PA8     ------> SWPMI1_IO
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SWPMI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN SWPMI1_MspInit 1 */

  /* USER CODE END SWPMI1_MspInit 1 */
  }
}

void HAL_SWPMI_MspDeInit(SWPMI_HandleTypeDef* swpmiHandle)
{

  if(swpmiHandle->Instance==SWPMI1)
  {
  /* USER CODE BEGIN SWPMI1_MspDeInit 0 */

  /* USER CODE END SWPMI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SWPMI1_CLK_DISABLE();

    /**SWPMI1 GPIO Configuration
    PA8     ------> SWPMI1_IO
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8);

  /* USER CODE BEGIN SWPMI1_MspDeInit 1 */

  /* USER CODE END SWPMI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
