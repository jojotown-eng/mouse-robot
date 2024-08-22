/**
 * Mode.cpp
 * @author yuta seya
 * @date 2019 3.28 
*/

#include "Mode.h"

#include <iostream>

#include <unistd.h>

#include <cstdio>

#include "TargetGenerator.h"

#include <mutex> 
extern std::mutex mtx;

/**
 * @brief モードクラスのコンストラクタ
 * @param なし
 * @return　なし
*/
Mode::Mode()
{

}

/**
 * @brief モードクラスのデストラクタ
 * @param なし
 * @return　なし
*/
Mode::~Mode()
{

}

/**
 * @brief モードクラスの初期化
 * @param なし
 * @return　なし
*/
void Mode::init()
{
  if ( led == nullptr ){
    led = Led::getInstance();
  }

  if ( sw == nullptr ){
    sw = Switch::getInstance();
  }

  if ( sensor == nullptr ){
    sensor = Sensor::getInstance();
  }

  if ( motor == nullptr ){
    motor = Motor::getInstance();
  }

  if ( maze == nullptr ){
    maze = Maze::getInstance();
  } 

  if ( trape == nullptr ){
    trape = Trapezoid::getInstance();
  } 

  if ( interrupt == nullptr ){
    interrupt = Interrupt::getInstance();
  } 
  
}

/**
 * @brief モードセレクト
 * @param なし
 * @return　なし
*/
void Mode::select()
{
  init();
  gx = 3;
  gy = 3;

  sensor->setConstant(1300, 120, Front);
  sensor->setConstant(495, 140, Left);
  sensor->setConstant(320, 120, Right);

  bool sw0,sw1,sw2;
  int mode_count = 0;

  while( 1 ){
    while( 1 ){
      mtx.lock();
      sw0 = sw->get0();
      sw1 = sw->get1();
      sw2 = sw->get2();
      std::printf("sw0 : %d, sw1 : %d, sw2 : %d\r",sw0, sw1, sw2 );
      mtx.unlock();

      if ( sw0 ){
        mode_count++;
        if ( mode_count > 8 ) mode_count = 0;
        mtx.lock();
        led->illuminate( mode_count );
        mtx.unlock();
      }

      if ( sw1 ){
        mode_count--;
        if ( mode_count < 0 ) mode_count = 8;
        mtx.lock();
        led->illuminate( mode_count );
        mtx.unlock();
      }

      if ( sw2 ) {
        mtx.lock();
        led->illuminate( 0x00 );
        mtx.unlock();
        break;
      }
      usleep(100);
    }

    if( mode_count == 0){
      Position pos;
      pos.init();
      maze->setGoal(gx, gy);
      maze->show( pos );
    } else if( mode_count == 1){
      while( 1 ){
        mtx.lock();
        sensor->show();
        sw1 = sw->get1();
        mtx.unlock();
        if ( sw1 ) break;
        usleep(10000);
      }
    } else if( mode_count == 2 ){
      // ゴール座標を変更する
      gx = 7;
      gy = 7;
    } else if( mode_count == 3 ){
      float velocity = 0.0f;
      int left = 0;
      int right = 0;

      TargetGenerator *trans_target = new TargetGenerator();

      trape->makeTrapezoid( 180.0f, 2000.0f, 500.0f, 0.0f, 0.0f, false );
      mtx.lock();
      std::printf("velocity ,left, right \r\n");
      mtx.unlock();

      while( trape->status() == false ){
        velocity = trape->getNextVelocity();
        trans_target->calcStepFrequency( velocity );
        trans_target->getStepFrequency( &left, &right, false );
        mtx.lock();
        std::printf("%5.5f, %d, %d\r\n", velocity, left, right );
        mtx.unlock();
        left = 0;
        right = 0;
      }
      delete trans_target;
    } else if( mode_count == 4 ){
      trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
      while( trape->status() == false );

      usleep( 300 );
        
      trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
      while( trape->status() == false );
    } else if( mode_count == 5 ){
      Position pos;
      ExistWall exist;
      uint8_t goal_x = gx;
      uint8_t goal_y = gy;
      maze->setGoal(goal_x, goal_y);
      pos.init();
	    maze->resetMap();
      mtx.lock();
      led->illuminate(0x0f);
      mtx.unlock();
      sleep(1);
      mtx.lock();
      led->illuminate(0x01);
      mtx.unlock();
      sleep(1);
      uint8_t next_dir = Front;

      maze->updatePosition(&pos, next_dir);
      trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
      while( trape->status() == false );
        
      while(pos.x != goal_x || pos.y != goal_y){	
        usleep(5500);
        mtx.lock();
        sw0 = sw->get0();
        mtx.unlock();

        for(int i = 0; i < 100; i++ ){
          mtx.lock();
          sensor->update();
          sensor->getWalldata(&exist);
          mtx.unlock();
          usleep(1);
        }

        if( sw0 ) break;
        next_dir = maze->getNextAction(&pos, &exist);
          
        if( next_dir == Front){
          maze->updatePosition(&pos, next_dir);
          trape->makeTrapezoid( 180.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
        } else if( next_dir == Left){
          maze->updatePosition(&pos, next_dir);
          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );

          // 左前、右前のセンサの値をみて処理を考える
          mtx.lock();
          int front_left = 0;
          int front_right = 0;
          for(int i = 0; i < 5; i++){
            sensor->getSensorFront(front_left, front_right);
          }
          mtx.unlock();
          if(front_left > 300){
            trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
            trape->makeTrapezoid( 30.0f, 2000.0f, 100.0f, 0.0f, 0.0f, false );
            while( trape->status() == false );
            trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
          }

          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
        } else if( next_dir == Right) {
          maze->updatePosition(&pos, next_dir);
          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );

          // 左前、右前のセンサの値をみて処理を考える
          mtx.lock();
          int front_left = 0;
          int front_right = 0;
          for(int i = 0; i < 5; i++){
            sensor->getSensorFront(front_left, front_right);
          }
          mtx.unlock();
          if(front_left > 300){
            trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
            trape->makeTrapezoid( 30.0f, 2000.0f, 100.0f, 0.0f, 0.0f, false );
            while( trape->status() == false );
            trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
          }

          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
          // 左前、右前のセンサの値をみて処理を考える
        } else if( next_dir == Rear){
          maze->updatePosition(&pos, next_dir);
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( TURN_180, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );
        }
      }
      trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
      while( trape->status() == false );
      if(pos.x == goal_x && pos.y == goal_y){
        maze->storeWall();
      }
    } else if(mode_count == 6){
      Position pos;
      ExistWall exist;
      uint8_t goal_x = gx;
      uint8_t goal_y = gy;
      maze->setGoal(goal_x, goal_y);
      pos.init();
	    maze->resetMap();
      mtx.lock();
      led->illuminate(0x0f);
      mtx.unlock();
      sleep(1);
      mtx.lock();
      led->illuminate(0x01);
      mtx.unlock();
      sleep(1);
      uint8_t next_dir = Front;

      maze->updatePosition(&pos, next_dir);
      trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
      while( trape->status() == false );
        
      while(pos.x != goal_x || pos.y != goal_y){	
        usleep(5500);
        mtx.lock();
        sw0 = sw->get0();
        mtx.unlock();

        for(int i = 0; i < 100; i++ ){
          mtx.lock();
          sensor->update();
          sensor->getWalldata(&exist);
          mtx.unlock();
          usleep(1);
        }

        if( sw0 ) break;
        next_dir = maze->getNextAction(&pos, &exist);
          
        if( next_dir == Front){
          maze->updatePosition(&pos, next_dir);
          trape->makeTrapezoid( 180.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
        } else if( next_dir == Left){
          maze->updatePosition(&pos, next_dir);
          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );

          // 左前、右前のセンサの値をみて処理を考える
          mtx.lock();
          int front_left = 0;
          int front_right = 0;
          for(int i = 0; i < 5; i++){
            sensor->getSensorFront(front_left, front_right);
          }
          mtx.unlock();
          if(front_left > 300){
            trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
            trape->makeTrapezoid( 30.0f, 2000.0f, 100.0f, 0.0f, 0.0f, false );
            while( trape->status() == false );
            trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
          }

          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
        } else if( next_dir == Right) {
          maze->updatePosition(&pos, next_dir);
          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );

          // 左前、右前のセンサの値をみて処理を考える
          mtx.lock();
          int front_left = 0;
          int front_right = 0;
          for(int i = 0; i < 5; i++){
            sensor->getSensorFront(front_left, front_right);
          }
          mtx.unlock();
          if(front_left > 300){
            trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
            trape->makeTrapezoid( 30.0f, 2000.0f, 100.0f, 0.0f, 0.0f, false );
            while( trape->status() == false );
            trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
          }

          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
          // 左前、右前のセンサの値をみて処理を考える
        } else if( next_dir == Rear){
          maze->updatePosition(&pos, next_dir);
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( TURN_180, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );
        }
      }
      trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
      while( trape->status() == false );
      if(pos.x == goal_x && pos.y == goal_y){
        maze->storeWall();
      }

      pos.direction = (pos.direction + 2) % 4;
      goal_x = 0;
      goal_y = 0;
      maze->setGoal(goal_x, goal_y);

      trape->makeTrapezoid( TURN_180, 1000.0f, 200.0f, 0.0f, 0.0f, true );
      while( trape->status() == false );

      maze->updatePosition(&pos, next_dir);
      trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
      while( trape->status() == false );
        
      while(pos.x != goal_x || pos.y != goal_y){	
        usleep(5500);
        mtx.lock();
        sw0 = sw->get0();
        mtx.unlock();

        for(int i = 0; i < 100; i++ ){
          mtx.lock();
          sensor->update();
          sensor->getWalldata(&exist);
          mtx.unlock();
          usleep(1);
        }

        if( sw0 ) break;
        next_dir = maze->getNextAction(&pos, &exist);
          
        if( next_dir == Front){
          maze->updatePosition(&pos, next_dir);
          trape->makeTrapezoid( 180.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
        } else if( next_dir == Left){
          maze->updatePosition(&pos, next_dir);
          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );

          // 左前、右前のセンサの値をみて処理を考える
          mtx.lock();
          int front_left = 0;
          int front_right = 0;
          for(int i = 0; i < 5; i++){
            sensor->getSensorFront(front_left, front_right);
          }
          mtx.unlock();
          if(front_left > 300){
            trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
            trape->makeTrapezoid( 30.0f, 2000.0f, 100.0f, 0.0f, 0.0f, false );
            while( trape->status() == false );
            trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
          }

          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
        } else if( next_dir == Right) {
          maze->updatePosition(&pos, next_dir);
          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );

          // 左前、右前のセンサの値をみて処理を考える
          mtx.lock();
          int front_left = 0;
          int front_right = 0;
          for(int i = 0; i < 5; i++){
            sensor->getSensorFront(front_left, front_right);
          }
          mtx.unlock();
          if(front_left > 300){
            trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
            trape->makeTrapezoid( 30.0f, 2000.0f, 100.0f, 0.0f, 0.0f, false );
            while( trape->status() == false );
            trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
            while( trape->status() == false );
          }

          trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
          interrupt->setSideSensorControl(true);
          while( trape->status() == false );
          interrupt->setSideSensorControl(false);
        } else if( next_dir == Rear){
          maze->updatePosition(&pos, next_dir);
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( TURN_180, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );
        }
      }
      trape->makeTrapezoid( 90.0f, 2000.0f, 300.0f, 0.0f, 0.0f, false );
      while( trape->status() == false );
      if(pos.x == goal_x && pos.y == goal_y){
        maze->storeWall();
        mode_count = 8;
      }

    } else if(mode_count == 7){
      sleep(1);
      trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
      while( trape->status() == false );
    } else if(mode_count == 8){
      /* 最短走行追加 */
      // ゴール座標をセットする
      maze->setGoal(gx, gy);
      // 壁情報を読み込み
      maze->loadWall();
      // 最短走行用のステップマップを作成
      maze->updateStepMap();
      // 迷路の現在座標をリセットする
      Position pos;
      pos.init();
      // 次の動作を定義
      uint8_t next_dir = Front;
      // パスのカウンタ
      uint16_t count = 0;
      // motionを入れる
      uint8_t path_motion[256];
      // 直線の数を入れる
      uint8_t path_count[256];
      // 直進のカウント用変数
      int straight_count = 0;
      // 迷路を表示
      maze->show(pos);
      while(pos.x != gx || pos.y != gy)
      {
        next_dir = maze->updateNextAction(&pos);
        // 最短走行なので、あり得るのは前or左or右だけ。それ以外はあり得ない。
        if(next_dir == Front){
          straight_count++;
          // 座標を更新
          maze->updatePosition(&pos, next_dir);
          // 直線が続く限り、直線を追加。
          while(maze->updateNextAction(&pos) == Front){
            // 直進のカウントを追加
            straight_count++;
            // 座標を更新
            maze->updatePosition(&pos, Front);
          }
          path_motion[count] = Front;
          path_count[count] = straight_count;
          count++;
          straight_count = 0;
        } else if(next_dir == Left){
          if(straight_count > 0){
            path_motion[count] = Front;
            path_count[count] = straight_count;
            count++;
          }
          maze->updatePosition(&pos, Left);
          path_motion[count] = Left;
          path_count[count] = 1;
          count++;
          straight_count = 1;
        } else if(next_dir == Right){
          if(straight_count > 0){
            path_motion[count] = Front;
            path_count[count] = straight_count;
            count++;
          }
          maze->updatePosition(&pos, Right);
          path_motion[count] = Right;
          path_count[count] = 1;
          count++;
          straight_count = 1;
        }
      }
      
      if(straight_count > 0){
        path_motion[count] = Front;
        path_count[count] = straight_count;
        count++;
      }

      for(int i = 0; i < count; i++){
        if(path_motion[i] == Front){
          printf("\nstraight %2d blocks\n", path_count[i]);
        } else if(path_motion[i] == Left){
          printf("turn left\n");
        } else if(path_motion[i] == Right){
          printf("turn right\n");
        }
      }

      // 三秒間まつ
      sleep(3);
      for(int i = 0; i < count; i++){
        mtx.lock();
        bool sw0 = sw->get0();
        mtx.unlock();
        usleep(10000);

        if( sw0 ) break;
        if(path_motion[i] == Front){
          if(path_count[i] > 9){
            trape->makeTrapezoid( 180.0f * path_count[i], 2000.0f, 1000.0f, 0.0f, 0.0f, false );
            interrupt->setSideSensorControl(true);
            while( trape->status() == false );
            interrupt->setSideSensorControl(false);
          } else if(path_count[i] > 8){
            trape->makeTrapezoid( 180.0f * path_count[i], 2000.0f, 900.0f, 0.0f, 0.0f, false );
            interrupt->setSideSensorControl(true);
            while( trape->status() == false );
            interrupt->setSideSensorControl(false);
          } else if(path_count[i] > 6){
            trape->makeTrapezoid( 180.0f * path_count[i], 2000.0f, 800.0f, 0.0f, 0.0f, false );
            interrupt->setSideSensorControl(true);
            while( trape->status() == false );
            interrupt->setSideSensorControl(false);
          } else if(path_count[i] > 4){
            trape->makeTrapezoid( 180.0f * path_count[i], 2000.0f, 700.0f, 0.0f, 0.0f, false );
            interrupt->setSideSensorControl(true);
            while( trape->status() == false );
            interrupt->setSideSensorControl(false);
          } else if(path_count[i] > 2){
            trape->makeTrapezoid( 180.0f * path_count[i], 2000.0f, 600.0f, 0.0f, 0.0f, false );
            interrupt->setSideSensorControl(true);
            while( trape->status() == false );
            interrupt->setSideSensorControl(false);
          } else if(path_count[i] > 1){
            trape->makeTrapezoid( 180.0f * path_count[i], 2000.0f, 400.0f, 0.0f, 0.0f, false );
            interrupt->setSideSensorControl(true);
            while( trape->status() == false );
            interrupt->setSideSensorControl(false);
          } else {
            trape->makeTrapezoid( 180.0f * path_count[i], 2000.0f, 300.0f, 0.0f, 0.0f, false );
            interrupt->setSideSensorControl(true);
            while( trape->status() == false );
            interrupt->setSideSensorControl(false);
          }
        } else if(path_motion[i] == Left){
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );
        } else if(path_motion[i] == Right){
          interrupt->setSideSensorControl(false);
          trape->makeTrapezoid( -TURN_90, 1000.0f, 200.0f, 0.0f, 0.0f, true );
          while( trape->status() == false );
        }
      }

    }
    mtx.lock();
    led->illuminate(0x00);
    mtx.unlock();
    mode_count = 0;
  } 

}

