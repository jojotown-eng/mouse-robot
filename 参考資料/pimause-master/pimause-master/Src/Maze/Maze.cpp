/**
 * maze.cpp
 * @author yuta seya
 * @date 2019 3.13
*/

#include "Maze.h"
#include <cstdio>
#include <queue>
#include <utility>
#include "mazeConf.h"

#include <mutex> 
extern std::mutex mtx;

Maze* Maze::instance = nullptr;

/**
 * @override Maze
 * @brief 迷路クラスのコンストラクタ
 * @param なし
 * @return なし
 * @detail mapクラスのインスタンスを得る,壁情報を初期化
*/
Maze::Maze()
{
  map = new Map();
  map->init();
}

/**
 * @override Maze
 * @brief 迷路クラスのコンストラクタ
 * @param uint8_t _gx マウスのゴール座標
 * @param uint8_t _gy マウスのゴール座標
 * @return なし
 * @detail mapクラスのインスタンスを得る,壁情報を初期化,ゴール座標の設定
*/
Maze::Maze( uint8_t _gx, uint8_t _gy )
{
  gx = _gx;
  gy = _gy;
  map = new Map();
  map->init();
}

/**
 * @brief 迷路クラスのデストラクタ
 * @param なし
 * @return　なし
*/
Maze::~Maze()
{
  delete map;
}

/**
 * @brief 迷路のインスタンスを得る
 * @param なし
 * @return　迷路クラスのインスタンス
*/
Maze* Maze::getInstance()
{
  if ( instance == nullptr ){
    instance = new Maze( 7, 7);
  }
  return instance;
}

/**
 * @brief マップを初期化する
 * @param なし
 * @return なし
*/
void Maze::resetMap()
{
  check_all_search = false;
  map->init();
}

/**
 * @brief ゴール座標を設定
 * @param uint8_t _gx マウスのゴール座標
 * @param uint8_t _gy マウスのゴール座標
 * @return　なし
*/
void Maze::setGoal( uint8_t _gx, uint8_t _gy )
{
  gx = _gx;
  gy = _gy;
}

/**
 * @brief 迷路関連のアップデートをしたのち、次の動作を返す
 * @param Position pos マウスの座標、向きの情報をもった構造体
 * @param ExsitWall exist 壁の有無の情報を持った構造体
 * @return 次の動作
 * @detail 壁情報の追加,歩数マップの更新,次の動作を決定,マウスの座標の更新を行ったのち
 *         次の動作を返す
*/
uint8_t Maze::getNextAction( Position *pos, ExistWall *exist )
{
  uint8_t next = Front;

  map->addWall( pos->x, pos-> y, exist, pos->direction );
  updateStepMap();
  next = updateNextAction( pos );
  //mtx.lock();
  //std::printf("x = %d, y = %d\r\n", pos->x, pos->y);
  //mtx.unlock();

  return next;
}

/**
 * @brief 歩数マップの更新を行う
 * @param なし
 * @return なし
 * @detail キューを使用した歩数マップの更新
*/
void Maze::updateStepMap()
{
  uint16_t count = 0;

  std::queue<std::pair<uint8_t, uint8_t>> q;
  std::pair<uint8_t, uint8_t> p;


  if ( gx == 0 && gy == 0 ){
      if ( !check_all_search ){
          for ( uint8_t x = 0; x < 16; x++ ){
              for ( uint8_t y = 0; y < 16; y++ ){
                  if ( map->checkWall(x,y) && ((virtual_goal[y] >> x) & 0x01) == 1)
                      manegeVirtualGoal(x, y, false);

                  if ( ((virtual_goal[y] >> x) & 0x01) == 1 ){
                      step[x][y] = 0;
                      q.push(std::pair<uint8_t, uint8_t>(x,y) );
                      count++;
                  } else {
                      step[x][y] = MAX_STEP;
                  }
              }
          }

          if ( count < 6 ){
              check_all_search = true;
              step[gx][gy] = 0;
              q.push(std::pair<uint8_t, uint8_t>(gx,gy) );
          }
      } else {
          for ( uint8_t x = 0; x < 16; x++ ){
              for ( uint8_t y = 0; y < 16; y++ ){
                  step[x][y] = MAX_STEP;
              }
          }
          step[gx][gy] = 0;
          q.push(std::pair<uint8_t, uint8_t>(gx,gy) );
      }
  } else {
      for ( uint8_t x = 0; x < 16; x++ ){
          for ( uint8_t y = 0; y < 16; y++ ){
              step[x][y] = MAX_STEP;
          }
      }
      step[gx][gy] = 0;
      q.push(std::pair<uint8_t, uint8_t>(gx,gy) );
  }


  while( !q.empty() ){
    p = q.front();
    uint8_t x = p.first;
    uint8_t y = p.second;
    q.pop();

    if( y < 15 && !map->getData(x,y,North) && step[x][y+1] == MAX_STEP ){
      step[x][y+1] = step[x][y] + 1;
      q.push(std::pair<uint8_t, uint8_t>(x,y+1));
    }

    if ( x < 15 && !map->getData(x,y,East) && step[x+1][y] == MAX_STEP ){
      step[x+1][y] = step[x][y] + 1;
      q.push(std::pair<uint8_t, uint8_t>(x+1,y));
    }

    if ( y > 0 && !map->getData(x,y,South) && step[x][y-1] == MAX_STEP ){
      step[x][y-1] = step[x][y] + 1;
      q.push(std::pair<uint8_t, uint8_t>(x,y-1));
    }

    if ( x > 0  && !map->getData(x,y,West) && step[x-1][y] == MAX_STEP ){
      step[x-1][y] = step[x][y] + 1;
      q.push(std::pair<uint8_t, uint8_t>(x-1,y));
    }
  }

}

/**
 * @brief 次の動作を決める
 * @param Position pos マウスの座標、向き
 * @return なし
 * @detail 現在の向き、方向から一番歩数の少ないほうへ進む
*/
uint8_t Maze::updateNextAction( Position *pos )
{
    uint16_t temp_step = 0;
    uint8_t nextdir = 0;
    uint8_t direction = pos->direction;
    int8_t x = pos->x;
    int8_t y = pos->y;
    int8_t a = 0, b = 0;

    if (direction == North) {
        a = 1;
        b = 0;
    } else if (direction == West) {
        a = 0;
        b = 1;
    } else if (direction == South) {
        a = -1;
        b = 0;
    } else {
        a = 0;
        b = -1;
    }

    if ((y - a >= 0) && (x + b < 16)) {
        if ((map->getData(x, y, (North + direction) % 4))
            && (map->getData(x, y, (East + direction) % 4))
            && (map->getData(x, y, (West + direction) % 4))) {
            nextdir = 2;
        } else {
          nextdir = 2;
        }
        temp_step = step[x + b][y - a];
    }
    if ((x - a >= 0) && (y - b >= 0)
        && (!map->getData(x, y, (West + direction) % 4))) {
        if (step[x - a][y - b] <= temp_step) {
            nextdir = 1;
            temp_step = step[x - a][y - b];
        }
    }
    if ((x + a < 16) && (y + b < 16)
        && (map->getData(x, y, (East + direction) % 4) == 0)) {
        if (step[x + a][y + b] <= temp_step) {
            nextdir = 3;
            temp_step = step[x + a][y + b];
        }
    }
    if ((y + a < 16) && (x - b >= 0)
        && (map->getData(x, y, (North + direction) % 4) == 0)) {
        if (step[x - b][y + a] <= temp_step) {
            nextdir = 0;
            temp_step = step[x - b][y + a];
        }
    }

    return nextdir;
}

/**
 * @brief マシンの座標を更新する
 * @param Position pos マウスの座標、向き
 * @return なし
 * @detail 次の動作からマシンの方向、座標を更新する
*/
void Maze::updatePosition( Position *pos, uint8_t action )
{
  pos->direction = (pos->direction + action) %4;

  if ( pos->direction == North ){
    pos->y++;
  } else if ( pos->direction == West ){
    pos->x--;
  } else if ( pos->direction == South ){
    pos->y--;
  } else {
    pos->x++;
  }
}

/**
 * @brief 仮想ゴールの追加を行う
 * @param なし
 * @return なし
 * @detail 探索済みかどうかを確認して、探索済みでなければ仮想ゴールに追加
*/
void Maze::setVirtualGoal()
{
    check_all_search = false;

    for ( int y = 0; y < 16; y++ ){
        virtual_goal[y] = 0;
    }

    for ( uint8_t x = 0; x < size; x++ ){
        for ( uint8_t y = 0; y < size; y++ ){
            if ( !map->checkWall(x, y) ) manegeVirtualGoal(x, y, true);
            else manegeVirtualGoal(x, y, false);
        }
    }
}

/**
 * @brief 仮想ゴールの管理を行う
 * @param uint8_t x
 * @param uint8_t y
 * @return なし
 * @detail 与えられた座標の仮想ゴールの追加、削除を行う
*/
void Maze::manegeVirtualGoal(uint8_t x, uint8_t y, bool manege)
{
    if ( manege ) virtual_goal[y] |= ( 1 << x );
    else virtual_goal[y] = ( virtual_goal[y] & (~(1 << x)) );
}

/**
 * @brief 壁情報、歩数マップを表示する
 * @param Position pos マウスの座標、向きの情報をもった構造体
 * @param ExsitWall exist 壁の有無の情報を持った構造体
 * @return 次の動作
*/
void Maze::show( Position pos )
{
  int x,y;

  loadWall();

  updateStepMap();

  mtx.lock();
  std::printf("\r\n");

  printf("  ");

  for ( x = 0; x < 17; x++ ){
    if( x < 10 ) std::printf("%d     ",x);
    else std::printf("%d    ",x);
  }

  std::printf("\n");

  for ( y = 15; y >= 0; y-- ){
    if ( y < 9 ) std::printf(" %d+",y+1);
    else std::printf("%d+",y+1);

    for ( x = 0; x < 16; x++ ){
      if ( map->getData( x, y, North ) ){
        std::printf("-----");
      } else {
        std::printf("     ");
      }
      std::printf("+");
    }

    std::printf("\r\n");
    for ( x = 0; x < 16; x++ ){
      if ( map->getData( x, y, West) ){
        if ( x == 0 ) std::printf("  |");
        else std::printf("|");
      } else {
        if ( x == 0 ) std::printf("   ");
        std::printf(" ");
      }

      // step を表示
      if ( pos.x == x && pos.y == y ){
        std::printf( "  M  ");
      } else if ( step[x][y] == 0 ) {
        std::printf( "  G  ");
      } else {
        std::printf("%5d",step[x][y] );
      }
      
    }

    if ( map->getData( 15, y, East ) ){
      std::printf("|");
    } else {
      std::printf(" ");
    }

    std::printf("\r\n");
  }

  std::printf(" 0+");
  for( x = 0; x < 16; x++ ){
    if ( map->getData( x, 0, South ) ){
      std::printf("-----");
    } else {
      std::printf("     ");
    }

    std::printf("+");
  }

  std::printf("\r\n");

  mtx.unlock();
}

void Maze::storeWall()
{
  mtx.lock();
  map->storeWall();
  mtx.unlock();
}

void Maze::loadWall()
{
  mtx.lock();
  map->loadWall();
  mtx.unlock();
}