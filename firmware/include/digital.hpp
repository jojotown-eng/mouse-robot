#ifndef DIGITAL_H_
#define DIGITAL_H_

#include "gpio.h"

class Digital {
public:
  Digital(GPIO_TypeDef *digital_port_, uint16_t digital_pin_);
  ~Digital();
  void on();
  void off();

private:
  GPIO_TypeDef *digital_port;
  uint16_t digital_pin;
};

#endif // DIGITAL_H_