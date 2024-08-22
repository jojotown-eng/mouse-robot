/**
 * Interrupt.cpp
 * @author yuta seya
 * @date 2019 4.2
*/
#include "Interrupt.h"

#include <iostream>
#include <unistd.h>
#include <cstdio>

#include <mutex>

std::mutex mtx;

Interrupt* Interrupt::instance = nullptr;

/**
 * @brief 割り込みクラスのコンストラクタ
 * @param なし
 * @return　なし
*/
Interrupt::Interrupt()
{
  if ( trape == nullptr ){
    trape = Trapezoid::getInstance();
  }

  if ( target_trans == nullptr ){
    target_trans = new TargetGenerator();
  }

  if ( motor == nullptr ){
    motor = Motor::getInstance();
  }
  
  if ( sensor == nullptr){
    sensor = Sensor::getInstance();
  }
  
}

/**
 * @brief 割り込みクラスのデストラクタ
 * @param なし
 * @return　なし
*/
Interrupt::~Interrupt()
{

}

/**
 * @brief interruptクラスのインスタンスを得る
 * @param なし
 * @return　interruptクラスのインスタンス
*/
Interrupt* Interrupt::getInstance()
{
  if ( instance == nullptr ){
    instance = new Interrupt();
  }
  return instance;
}

/**
 * @brief 割り込みの処理を行う
 * @param なし
 * @return　なし
*/
void Interrupt::processing()
{
  while( 1 ){
    mtx.lock();
    processing_start = std::chrono::system_clock::now();
    sensor->get(&sen_front, &sen_left, &sen_right, &exsit);
    
    if(trape->status() == false){
      velocity = trape->getNextVelocity();
      target_trans->calcStepFrequency( velocity );
      target_trans->clacSideSensorP(sen_left, sen_right, side_sensor_control, trape->checkTurn()); 
      target_trans->calcFrontSensorP(sen_front, trape->checkTurn());
      target_trans->getStepFrequency( &left, &right, trape->travelDirection() );    
    } else {
      //std::printf("act\r");
      left = 0;
      right = 0;
    }

    mtx.unlock();

    if ( trape->checkTurn() ){
      left = -1 * left;
    }

    mtx.lock();
    motor->control( left, right );
    processing_end = std::chrono::system_clock::now();
    mtx.unlock();

    //std::cout << left << right << velocity << std::endl;
    
    left = 0;
    right = 0;
    velocity = 0.0f;

    double processing_time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(processing_end - processing_start).count() );
    
    uint32_t wait_time = (uint32_t)( 5000 - processing_time );

    usleep( wait_time );
    
  }
}
