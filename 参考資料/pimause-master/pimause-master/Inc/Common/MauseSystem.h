/**
 * MauseSystem.h
 * @author yuta seya
 * @date 2019 3.28 
*/

#ifndef __MAUSE_SYSTEM__H
#define __MAUSE_SYSTEM__H

#include "Switch.h"
#include "Led.h"
#include "Motor.h"
#include "Sensor.h"
#include "Interrupt.h"

class MauseSystem
{
private:
  Led *led;
  Switch *sw;
  Sensor *sensor;
  Motor *motor;

public:
  // コンストラクタ
  MauseSystem();
  
  // デストラクタ
  ~MauseSystem();

  // 周辺機能の初期化
  void peripheral_init();
  
};

#endif /* __MAUSE_SYSTEM__H */