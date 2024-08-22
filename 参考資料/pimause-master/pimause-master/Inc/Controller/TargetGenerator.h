/**
 * TargetGenerator.h
 * @author yuta seya
 * @date 2019 4.2
*/
#ifndef __TARGET_GENERATOR__H
#define __TARGET_GENERATOR__H

#include "Trapezoid.h"

#include "Sensor.h"

class TargetGenerator
{
private:
  Trapezoid *trape;

  int step_vel = 0;
  int16_t step_sensor = 0;
  int16_t step_front_sensor = 0;
  float store_velocity = 0.0f;
  float step_diff = 0.0f;

  // TIRE_RADIUS 48.0f
  // d[mm/step] = 48.0 * ( 0.9 * pi / 360)
  #define STEP_DISTANCE_CONST 0.37699111843f 

  #define sensor_kp 0.30f
  #define sensor_kd 1.2f
  #define front_kp 0.30f

public:
  // コンストラクタ
  TargetGenerator();

  // デストラクタ
  ~TargetGenerator();

  // ステップ周波数を返す
  void getStepFrequency( int *left, int *right, bool back_right );

  // 速度からステップ周波数の目標値を計算する
  void calcStepFrequency( float velocity );

  // センサの値からフィードバックする
  int16_t clacSideSensorP(Sensor_Data& sen_left, Sensor_Data& sen_right, bool act, bool rotation);

  // 前壁制御をする
  int16_t calcFrontSensorP(Sensor_Data &sen_front, bool act);

};




#endif /* __TARGET_GENERATOR__H */