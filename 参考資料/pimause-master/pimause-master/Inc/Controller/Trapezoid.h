/**
 * Trapezoid.h
 * @author yuta seya
 * @date 2019 4.2
*/
#ifndef __TRAPEZOID__H
#define __TRAPEZOID__H

class Trapezoid
{
private:
  static Trapezoid *instance;

  // 終了しているかどうかを返す
  bool is_end = true;

  // 引数から与えられた定数
  float accel = 0.0f; // 加速度
  float max_velocity = 0.0f; // 最高速度
  float end_velocity = 0.0f; // 終了時の速度(最高速を上回ってはいけない)
  float target_velocity = 0.0f; // 目標距離

  // 計算から求めた定数
  float accel_dis = 0.0f; // 加速の距離
  float deccel_dis = 0.0f; // 減速の距離
  
  // 現在の数値を覚える
  float velocity = 0.0f;  // 速度
  float distance = 0.0f; // 距離

  bool travel_dir = false;
  bool turn = true;

  #define dt 0.005f     // 制御時間

public:
  #define ONE_BLOCK 180.0f
  #define HALF_BLOCK 90.0f
  #define TURN_90 72.2f
  #define TURN_180 143.5f

  // コンストラクタ
  Trapezoid();
  
  // デストラクタ
  ~Trapezoid();

  // インスタンスを返す
  static Trapezoid* getInstance();

  // 台形加速の加速、定速、減速区間を作成する
  void makeTrapezoid( float dis, float acc, float max_vel, float start_vel, float end_vel, bool turn_flag );

  // 次の速度を返す
  float getNextVelocity();

  // モーションのステータスを返す
  bool status();

  // 前、後ろを返す
  bool travelDirection();

  // ターンか直進か返す
  bool checkTurn();
};

#endif /* __TRAPEZOID__H */