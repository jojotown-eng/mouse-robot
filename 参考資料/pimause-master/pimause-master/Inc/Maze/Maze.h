/**
 * maze.h
 * @author yuta seya
 * @date 2019 3.13
*/

#ifndef MAZE_H
#define MAZE_H

#include <stdint.h>
#include "mazeConf.h"
#include "Map.h"

struct Position
{
public:
  int8_t x;
  int8_t y;
  uint8_t direction;

  void init()
  {
    x = 0;
    y = 0;
    direction = 0;
  }
};

class Maze {
private:
  static Maze* instance;
  #define MAX_STEP 0xffff
  Map *map;
  uint8_t gx = 0;
  uint8_t gy = 0;
  uint16_t step[16][16];
  bool start = true;
  uint8_t size = 16;
  uint16_t virtual_goal[16];
  bool check_all_search = false;

public:
  // コンストラクタ
  Maze();

  Maze( uint8_t _gx, uint8_t _gy );

  // デストラクタ
  ~Maze();

  // インスタンスを得る
  static Maze* getInstance();

  // ゴール座標をセットする
  void setGoal( uint8_t _gx, uint8_t _gy );

  // 迷路情報のアップデートを行い、次の動作を返す
  uint8_t getNextAction( Position *pos, ExistWall *exist );

  // マシンの座標を更新する
  void updatePosition( Position *pos, uint8_t action );
  
  // スタート動作かどうかのフラグをセットする
  void setStartFlag( bool _flag )
  {
    start = _flag;
  }

  // マップをリセットする
  void resetMap();

  uint8_t getMazeSize(){ return size; }

  // 壁情報を得る
  bool getWallData( uint8_t _x, uint8_t _y, uint8_t _direction)
  {
      return map->getData( _x, _y, _direction);
  }

  // ゴール座標を返す
  void loadGoalPosition( uint8_t *_gx, uint8_t *_gy )
  {
      *_gx = gx;
      *_gy = gy;
  }

  // 壁を追加
  void addWall(uint8_t x, uint8_t y, bool n, bool w, bool s, bool e)
  {
      map->addWall( x, y, n, w, s, e );
  }

  // 仮想ゴールを追加する
  void setVirtualGoal();

  // 歩数マップと壁情報を表示する
  void show( Position pos);

  // 迷路をtxtに保存
  void storeWall();

  // 迷路をtxtから読み出し
  void loadWall();
  
  // 歩数マップを更新
  void updateStepMap();

  // 次の動作を決める
  uint8_t updateNextAction( Position *pos );

private:

  // 仮想ゴールの管理を行う
  void manegeVirtualGoal( uint8_t x, uint8_t y, bool manege );

};

#endif // MAZE_H