/**
 * Motor.cpp
 * @author yuta seya
 * @date 2019 3.25 
*/

#include <cstdio>

#include "Motor.h"

#include <cstdio>

Motor* Motor::instance = nullptr;

/**
 * @brief モータークラスのコンストラクタ
 * @param なし
 * @return　なし
*/
Motor::Motor()
{
  on();
}

/**
 * @brief モータークラスのデストラクタ
 * @param なし
 * @return　なし
*/
Motor::~Motor()
{
  //off();
  delete instance;
}

/**
 * @brief モータークラスのインスタンスを得る
 * @param なし
 * @return　モータークラスのインスタンス
*/
Motor* Motor::getInstance()
{
  if ( instance == nullptr ){
    instance = new Motor();
  }
  return instance;
}


/**
 * @brief ソフトウェアスイッチのオンオフ
 * @param なし
 * @return なし
 * @detail 現在のソフトウェアスイッチのステータスを更新し、
 *        　ソフトウェアスイッチをステータスに合わせてオンオフを行う 
*/
void Motor::setSoftwareSwitch( bool sw )
{
  status = sw;
  if ( status ){
    on();
  } else {
    off();
  }
}

/**
 * @brief モーターのコントロールを行う
 * @param int left 左側の周波数
 * @param int right 右側の周波数
 * @return なし
*/
void Motor::control( int left, int right )
{
  if ( !status ) on();
  
  leftControl( left );
  rightControl( right );
}

/**
 * @brief モーターのステップ数のカウンタを読む
 * @param int *left 左側のカウント
 * @param int *right 右側のカウント
 * @return なし
*/
void Motor::readStepCount( int *left, int *right )
{
  *left = readLeft();
  *right = readRight();
}

/**
 * @brief 左モーターのステップ数のカウンタを読む
 * @param なし
 * @return int left 左のカウント
*/
int Motor::readLeft()
{
  int left = 0;
  std::FILE *data;

  data = std::fopen( "/dev/rtcounter_l0", "r" );
  std::fscanf( data, "%d", &left );
  std::fclose( data );
  return left;
}

/**
 * @brief 右モーターのステップ数のカウンタを読む
 * @param なし
 * @return int right 右のカウント
 * */
int Motor::readRight()
{
  int right = 0;
  std::FILE *data;

  data = std::fopen( "/dev/rtcounter_r0", "r" );
  std::fscanf( data, "%d", &right );
  std::fclose( data );
  return right;
}

/**
 * @brief モーターのステップ数をリセットする
 * @param なし
 * @return なし
 * */
void Motor::resetStepCount()
{
  resetLeftStep();
  resetRightStep();
}

/**
 * @brief 左モーターのステップ数をリセットする
 * @param なし
 * @return なし
 * */
void Motor::resetLeftStep()
{
  std::FILE *count;
  count = std::fopen( "/dev/rtcounter_l0", "w" );
  std::fprintf( count, "0" );
  std::fclose( count );
}

/**
 * @brief 右モーターのステップ数のカウンタを読む
 * @param なし
 * @return なし
 * */
void Motor::resetRightStep()
{
  std::FILE *count;
  count = std::fopen( "/dev/rtcounter_r0", "w" );
  std::fprintf( count, "0" );
  std::fclose( count );
}

/**
 * @brief ソフトウェアスイッチのオフ
 * @param なし
 * @return なし
*/
void Motor::off()
{
  std::FILE *sw;
  sw = std::fopen( "/dev/rtmotoren0","w" );
  std::fprintf( sw, "0" ); 
  std::fclose( sw );
}

/**
 * @brief ソフトウェアスイッチのオン
 * @param なし
 * @return なし
*/
void Motor::on()
{
  std::FILE *sw;
  sw = std::fopen( "/dev/rtmotoren0","w" );
  std::fprintf( sw, "1" ); 
  std::fclose( sw );
}

/**
 * @brief 左モーターのコントロールを行う
 * @param int hz 周波数
 * @return なし
*/
void Motor::leftControl( int hz )
{
  std::FILE *motor;
  motor = std::fopen( "/dev/rtmotor_raw_l0","w" );
  std::fprintf( motor, "%d", hz ); 
  std::fclose( motor );
}

/**
 * @brief 右モーターのコントロールを行う
 * @param int hz 周波数
 * @return なし
*/
void Motor::rightControl( int hz )
{
  std::FILE *motor;
  motor = std::fopen( "/dev/rtmotor_raw_r0","w" );
  std::fprintf( motor, "%d", hz ); 
  std::fclose( motor );
}