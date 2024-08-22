/**
 * TargetGenerator.h
 * @author yuta seya
 * @date 2019 4.2
*/

#include "TargetGenerator.h"

/**
 * @brief 目標値の生成クラスのコンストラクタ
 * @param なし
 * @return　なし
*/
TargetGenerator::TargetGenerator()
{
  trape = Trapezoid::getInstance();
}

/**
 * @brief 目標値の生成クラスのコンストラクタ
 * @param なし
 * @return　なし
*/
TargetGenerator::~TargetGenerator()
{

}

/**
 * @brief ステップ周波数を返す
 * @param なし
 * @return　なし
*/
void TargetGenerator::getStepFrequency( int *left, int *right, bool back_right )
{
  // step_sensorの足し引きは暫定
  if ( back_right ){
    *left += -1 * (step_vel - step_sensor);
    *right += -1 * (step_vel + step_sensor);
  } else {
    *left += step_vel + step_sensor - step_front_sensor;
    *right += step_vel - step_sensor - step_front_sensor;
  }
}

/**
 * @brief 速度からステップ周波数を計算する
 * @param なし
 * @return　なし
*/
void TargetGenerator::calcStepFrequency( float velocity )
{
  float frequency = 0.0f;

  store_velocity = velocity;
  // v_step[step/sec] = v[mm/s] / d[mm/step]
  // v_step パルス周波数
  frequency = velocity / STEP_DISTANCE_CONST;

  step_vel = int(frequency);
}

/**
 * @brief センサの情報からフィードバック用ステップ周波数を計算する
 * @param なし
 * @return　なし
*/
int16_t TargetGenerator::clacSideSensorP(Sensor_Data& sen_left, Sensor_Data& sen_right, bool act, bool rotation)
{
  float step_value = 0.0f;
  float step_d = 0.0f;
  if( act && !rotation && (store_velocity > 200.0f) ){
    if(sen_left.now > sen_left.threshold && sen_right.now > sen_right.threshold && sen_left.diff_1ms < 10 && sen_right.diff_1ms < 10){
      // 両壁があるとき
      step_value = (float)sensor_kp * ( (sen_left.now-sen_left.reference) - (sen_right.now-sen_right.reference));
      step_d = (step_value - step_diff) * sensor_kd;
      step_diff = step_value;
      step_value += step_d;
      if(step_value > 100) step_value = 100.0f;
      else if(step_value < -100) step_value = -100.0f;
    } else if(sen_left.now > sen_left.threshold && sen_left.diff_1ms < 7 && sen_right.diff_1ms < 7 ){
      // 左壁があるとき
      step_value = (float)sensor_kp * (sen_left.now-sen_left.reference);
      step_diff = step_value;
      if(step_value > 100) step_value = 100.0f;
      else if(step_value < -100) step_value = -100.0f;
    } else if(sen_right.now > sen_right.threshold && sen_right.diff_1ms < 7 && sen_left.diff_1ms < 7 ){
      // 右壁があるとき
      step_value = (float)-sensor_kp *(sen_right.now-sen_right.reference);
      step_diff = step_value;
      if(step_value > 100) step_value = 100.0f;
      else if(step_value < -100) step_value = -100.0f;
    } else {
      step_value = 0.0f;
      step_diff = 0.0f;
    } 
  }

  step_sensor = (int16_t)step_value;
  return step_sensor;
}

int16_t TargetGenerator::calcFrontSensorP(Sensor_Data &sen_front, bool act)
{
  float front_control_val = 0.0f;
  if(!act && (store_velocity > 100 && store_velocity < 300.0f) && sen_front.now > 700){
    front_control_val = (float)front_kp * (sen_front.now - sen_front.reference);
  } 

  step_front_sensor = (int16_t)front_control_val;
  return step_front_sensor;
}