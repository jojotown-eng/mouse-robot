/**
 * Sensor.cpp
 * @author yuta seya
 * @date 2019 3.27
*/

#include "Sensor.h"

#include <cstdio>

Sensor* Sensor::instance = nullptr;

/**
 * @brief センサークラスのコンストラクタ
 * @param なし
 * @return　なし
*/
Sensor::Sensor()
{

}

/**
 * @brief センサークラスのデストラクタ
 * @param なし
 * @return　なし
*/
Sensor::~Sensor()
{
  delete instance;
}

/**
 * @brief センサクラスのインスタンスを得る
 * @param なし
 * @return　センサクラスのインスタンス
*/
Sensor* Sensor::getInstance()
{
  if ( instance == nullptr ){
    instance = new Sensor();
  }
  return instance;
}

/**
 * @brief センサーの情報を返す
 * @param Sensor_Data *front 前壁
 * @param Sensor_Data *left  左壁
 * @param Sensor_Data *right 右壁
 * @param ExistWall *real 壁情報
 * @return なし
 * @detail センサ関連の処理をしたのち、センサのデータを返す。
*/
void Sensor::get( Sensor_Data *front, Sensor_Data *left, Sensor_Data *right, ExistWall *real)
{
  update();
  *front = sen_front;
  *left = sen_left;
  *right = sen_right; 
  *real = exist;
}

/**
 * @brief センサーのリファレンス値をセットする。
 * @param Sensor_Data *data
 * @param int reference 中心に置いたときの値
 * @param int threshold 壁の閾値
 * @param int dir 向きを決める 
 * @return なし
*/
void Sensor::setConstant( int reference, int threshold, int dir )
{
  if ( dir == Front ){
    sen_front.reference = reference;
    sen_front.threshold = threshold;
  } else if ( dir == Left ){
    sen_left.reference = reference;
    sen_left.threshold = threshold;
  } else if ( dir == Right ){
    sen_right.reference = reference;
    sen_right.threshold = threshold;
  }
}

void Sensor::show()
{
  //update();
  std::printf( "%d, %d, %d, %d, %d\r\n",left_fornt, right_front, sen_front.now, sen_left.now, sen_right.now);
}

/**
 * @brief センサーの情報を更新する
 * @param なし
 * @return なし
*/
void Sensor::update()
{
  read();
  updateDiff();
  checkWall();
}

/**
 * @brief センサーの情報から壁情報を更新
 * @param なし
 * @return なし
*/
void Sensor::checkWall()
{
  if ( sen_front.now > sen_front.threshold ){
    exist.front = true;
  } else {
    exist.front = false;
  }

  if ( sen_left.now > sen_left.threshold ){
    exist.left = true; 
  } else {
    exist.left = false;
  }

  if ( sen_right.now > sen_right.threshold ){
    exist.right = true; 
  } else {
    exist.right = false;
  }
}

/**
 * @brief センサーの情報を読み込む
 * @param なし
 * @return なし
*/
void Sensor::read()
{
  std::FILE *data;

  int fr = 0;
  int r = 0;
  int l = 0;
  int fl = 0;

  data = std::fopen("/dev/rtlightsensor0", "r" );
  std::fscanf( data, "%d %d %d %d", &fr, &r, &l, &fl );
  std::fclose( data );
  left_fornt = fl;
  right_front = fr;
  sen_front.now = ( fr + fl ) / 2;
  sen_left.now = l;
  sen_right.now = r; 
}

/**
 * @brief センサーの情報の差分を計算する
 * @param なし
 * @return なし
*/
void Sensor::updateDiff()
{
  sen_front.diff_1ms = sen_front.now - sen_front.before_1ms;
  sen_front.diff_3ms = sen_front.now - sen_front.before_3ms;
  if( sen_front.diff_1ms < 0 ) sen_front.diff_1ms = -1 * sen_front.diff_1ms;
  if( sen_front.diff_3ms < 0 ) sen_front.diff_3ms = -1 * sen_front.diff_3ms;

  sen_front.before_3ms = sen_front.before_2ms;
  sen_front.before_2ms = sen_front.before_1ms;
  sen_front.before_1ms = sen_front.now;

  sen_left.diff_1ms = sen_left.now - sen_left.before_1ms;
  sen_left.diff_3ms = sen_left.now - sen_left.before_3ms;
  if( sen_left.diff_1ms < 0 ) sen_left.diff_1ms = -1 * sen_left.diff_1ms;
  if( sen_left.diff_3ms < 0 ) sen_left.diff_3ms = -1 * sen_left.diff_3ms;

  sen_left.before_3ms = sen_left.before_2ms;
  sen_left.before_2ms = sen_left.before_1ms;
  sen_left.before_1ms = sen_left.now;

  sen_right.diff_1ms = sen_right.now - sen_right.before_1ms;
  sen_right.diff_3ms = sen_right.now - sen_right.before_3ms;
  if( sen_right.diff_1ms < 0 ) sen_right.diff_1ms = -1 * sen_right.diff_1ms;
  if( sen_right.diff_3ms < 0 ) sen_right.diff_3ms = -1 * sen_right.diff_3ms;

  sen_right.before_3ms = sen_right.before_2ms;
  sen_right.before_2ms = sen_right.before_1ms;
  sen_right.before_1ms = sen_right.now;

}

void Sensor::getWalldata(ExistWall *real)
{
  *real = exist;
}

void Sensor::getSensorFront(int &left, int &right)
{ 
  left = left_fornt;
  right = right_front;
}