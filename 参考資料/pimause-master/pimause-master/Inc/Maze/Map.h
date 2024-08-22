/**
 * map.h
 * @author yuta seya
 * @date 2019 3.13
*/

#ifndef MAP_H
#define MAP_H


#include <stdint.h>
#include "mazeConf.h"

struct ExistWall
{
  bool front;
  bool left;
  bool right;
};

class Map
{

private:
  // 壁情報をもつ構造体
  struct WallData
  {
    uint16_t vertical[17];
    uint16_t horizontal[17];
    uint16_t vertical_known[17];
    uint16_t horizontal_knwon[17];
  };

  WallData wall;

public:
  // コンストラクタ
  Map();

  // デストラクタ
  ~Map();

  // 壁情報の初期化
  void init();

  // 壁情報の追加
  void addWall( uint8_t x, uint8_t y, ExistWall *exist, uint8_t direction );

  // 壁情報の追加
  void addWall(uint8_t x, uint8_t y, bool n, bool w, bool s, bool e );

  // 壁情報を読み出す
  bool getData( uint8_t x, uint8_t y, uint8_t direction );

  // 壁情報を読み込む
  void getWallData( ExistWall *exist );

  // 探索したかどうかを確認
  bool checkWall( uint8_t x, uint8_t y );

  // 壁を保存する
  void storeWall();

  // 壁を読み込む
  void loadWall();

private:
  // 東西南北の壁の追加、削除
  void manegeNorthWall( uint8_t x, uint8_t y, bool exist );

  void manegeSouthWall( uint8_t x, uint8_t y, bool exist );

  void manegeWestWall( uint8_t x, uint8_t y, bool exist );

  void manegeEastWall( uint8_t x, uint8_t y, bool exist );

};
#endif // MAP_H