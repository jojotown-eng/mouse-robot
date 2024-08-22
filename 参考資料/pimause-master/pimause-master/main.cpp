/**
 * main.cpp
 * @author yuta seya
 * @date 2019 3.25 
*/

#include <iostream>
#include <unistd.h>

#include "MauseSystem.h"
#include "Mode.h"
#include <thread>
#include "Interrupt.h"

Mode *mode = new Mode();;
Interrupt * interrupt = Interrupt::getInstance();

void mode_run()
{  
  mode->select();
}

void interrupt_run()
{
  interrupt->processing();
}

int main()
{
 
  MauseSystem *mause = new MauseSystem();
  mause->peripheral_init();
  std::thread th_a(mode_run);
  std::thread th_b(interrupt_run);

  th_a.join();
  th_b.join();
  
  return 0;
}