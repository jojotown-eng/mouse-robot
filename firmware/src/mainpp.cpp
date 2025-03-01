#include "mainpp.h"

#include "main.h"
#include "gpio.h"
// #include "stm32l4xx_hal_conf"
// #include "stm32l4xx_it.h"

#include <stdio.h>

#include "digital.hpp"

Digital *led=nullptr;

void mainsetup(void){
  led = new Digital(LED_GPIO_Port, LED_Pin);
}

void maintask(void){
  led->on();
  HAL_Delay(500);
  led->off();
  HAL_Delay(500);
}