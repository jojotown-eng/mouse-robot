/**
 * MauseSystem.cpp
 * @author yuta seya
 * @date 2019 3.28 
*/

#include "MauseSystem.h"

#include <unistd.h>

/**
 * @brief マウスシステムクラスのコンストラクタ
 * @param なし
 * @return　なし
*/
MauseSystem::MauseSystem()
{
  
}

/**
 * @brief マウスシステムクラスのデストラクタ
 * @param なし
 * @return　なし
*/
MauseSystem::~MauseSystem()
{

}

/**
 * @brief 周辺機能の初期化(インスタンスを得る)
 * @param なし
 * @return　なし
*/
void MauseSystem::peripheral_init()
{
  sleep(1);
  led = Led::getInstance();
  sw = Switch::getInstance();
  sensor = Sensor::getInstance();
  motor = Motor::getInstance();

  led->illuminate( 0x0f );
  sleep(1);
  led->illuminate( 0x00 );
}

