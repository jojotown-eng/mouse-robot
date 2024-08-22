/**
 * Mode.h
 * @author yuta seya
 * @date 2019 3.28 
*/

#ifndef __MODE__H
#define __MODE__H

#include "Led.h"
#include "Sensor.h"
#include "Buzzer.h"
#include "Motor.h"
#include "Switch.h"
#include "Maze.h"
#include "Trapezoid.h"
#include "Maze.h"
#include "Interrupt.h"

class Mode {
private:
  Led *led = nullptr;
  Sensor *sensor = nullptr;
  Motor *motor = nullptr;
  Switch *sw = nullptr;
  Maze *maze = nullptr;
  Trapezoid *trape = nullptr;
  Interrupt *interrupt = nullptr;

public:
  // コンストラクタ
  Mode();

  // デストラクタ
  ~Mode();

  // モードセレクト
  void select();


private:
  // 初期化
  void init();

  uint8_t gx = 7;
  uint8_t gy = 7;
};

#endif /* __MODE__H */