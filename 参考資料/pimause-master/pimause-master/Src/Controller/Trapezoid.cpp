/**
 * Trapezoid.cpp
 * @author yuta seya
 * @date 2019 4.2 
*/
#include "Trapezoid.h"
#include <cmath>

Trapezoid* Trapezoid::instance = nullptr;

/**
 * @brief 台形クラスのコンストラクタ
 * @param なし
 * @return　なし
*/
Trapezoid::Trapezoid()
{

}

/**
 * @brief 台形クラスのコンストラクタ
 * @param なし
 * @return　なし
*/
Trapezoid::~Trapezoid()
{

}

/**
 * @brief 台形クラスのインスタンスを得る
 * @param なし
 * @return　台形クラスのインスタンス
*/
Trapezoid* Trapezoid::getInstance()
{
  if ( instance == nullptr ){
    instance = new Trapezoid();
  }
  return instance;
}

/**
 * @brief 台形加速の形をつくる
 * @param なし
 * @return　なし
 * @detail 加速区間の距離と減速距離を計算し求める
*/
void Trapezoid::makeTrapezoid( float dis, float acc, float max_vel, float start_vel, float end_vel, bool turn_flag )
{
  // 各種パラメータをリセット
  is_end = false;
  distance = 0.0f;

  if ( dis < 0.0f ){
    travel_dir = true;
  } else {
    travel_dir = false;
  }
  
  accel = std::abs(acc);
  max_velocity = std::abs(max_vel);
  end_velocity = std::abs(end_vel);
  target_velocity = std::abs(dis);
  velocity = start_vel;

  turn = turn_flag;

  if ( acc == 0.0f ){
    // 加速度が0のときは加減速の距離は0
    accel_dis = 0.0f;
    deccel_dis = 0.0f;
  } else {
    accel_dis = ( max_vel * max_vel- start_vel * start_vel ) / ( 2.0f * acc );
    deccel_dis = ( max_vel * max_vel- end_vel * end_vel ) / ( 2.0f * acc );
  }
}

/**
 * @brief 次の速度を返す
 * @param なし
 * @return　なし
 * @detail 距離、速度を計算して、速度を返す。
*/
float Trapezoid::getNextVelocity()
{
  if ( distance < accel_dis ){
    // 加速距離よりも少ないとき
    velocity += accel * dt;
    distance += velocity * dt + accel * dt * dt;
  } else if ( distance < target_velocity - deccel_dis ){
    if ( velocity < max_velocity ){
      // 指定距離よりも短いとき
      velocity += accel * dt;
      distance += velocity * dt + accel * dt * dt;
    } else {
      // 速度一定
      velocity = max_velocity;
      distance += velocity * dt;
    }
  } else if ( velocity > end_velocity ){
    // 速度が終了速度よりも早いとき
    velocity -= accel * dt;
    distance += velocity * dt - accel * dt * dt;
  } else {
    // 終了処理
    // 速度を終了速度にする、モーションの終了速度をtrueにする
    velocity = end_velocity;
    is_end = true;
  }

  return velocity;

}

/**
 * @brief 台形加速のステータスを返す
 * @param なし
 * @return　なし
 * @detail 台形加速の終了していた場合はtrueを返す
*/
bool Trapezoid::status()
{
  return is_end;
}

/**
 * @brief 台形加速の進む向きを返す
 * @param なし
 * @return　なし
 * @detail 前 false 後ろ true
*/
bool Trapezoid::travelDirection()
{
  return travel_dir;
}

/**
 * @brief ターンかどうか返す
 * @param なし
 * @return　なし
*/
bool Trapezoid::checkTurn()
{
  return turn;
}