#include "gpio.h"

#include "digital.hpp"

Digital::Digital(GPIO_TypeDef *digital_port_, uint16_t digital_pin_
                  ):digital_port(digital_port_),digital_pin(digital_pin_){}

Digital::~Digital(){}

void Digital::on(){
  HAL_GPIO_WritePin(digital_port, digital_pin, GPIO_PIN_SET);
}

void Digital::off(){
  HAL_GPIO_WritePin(digital_port, digital_pin, GPIO_PIN_RESET);
}

uint8 Digital::value(){
  return HAL_GPIO_ReadPin(digital_port,digital_pin);
}