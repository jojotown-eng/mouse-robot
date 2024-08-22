/**
 * Interrupt.h
 * @author yuta seya
 * @date 2019 4.2
*/
#ifndef __INTERRUPT__H
#define __INTERRUPT__H

#include "Trapezoid.h"
#include "TargetGenerator.h"
#include "Sensor.h"
#include "Map.h"

#include <chrono>
#include "Motor.h"

class Interrupt
{
private:
  static Interrupt *instance;
  Trapezoid *trape = nullptr;
  TargetGenerator *target_trans = nullptr;
  Sensor *sensor = nullptr;
  Motor *motor = nullptr;

  int left = 0;
  int right = 0;
  float velocity = 0.0f;
  
  // 時間を計測するための変数
  std::chrono::system_clock::time_point processing_start, processing_end;

public:
  // 割り込みクラスのコンストラクタ
  Interrupt();

  // 割り込みクラスのデストラクタ
  ~Interrupt();

  // クラスのインスタンスを返す
  static Interrupt* getInstance();

  // 処理を行う
  void processing();

  ExistWall getExistWall() const { return exsit; }

  // 横壁制御設定
  void setSideSensorControl(bool _flag)
  {
    side_sensor_control = _flag;
  }

  // 前壁制御設定
  void setFrontWallControl(bool _flag)
  {
    front_wall_control = _flag;
  }

private:
  Sensor_Data sen_front;
  Sensor_Data sen_left;
  Sensor_Data sen_right;
  ExistWall exsit;
  bool side_sensor_control = false;
  bool front_wall_control = false;
  int16_t side_sensor_feedback = 0;
  int16_t front_wall_feedback = 0;
};


#endif /* __INTERRUPT__H */
