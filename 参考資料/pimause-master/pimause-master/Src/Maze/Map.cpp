/**
 * map.cpp
 * @author yuta seya
 * @date 2019 3.13
*/

#include "Map.h"

#include <cstdio>

/**
 * @brief マップクラスのコンストラクタ
 * @param なし
 * @return　なし
*/
Map::Map()
{

}

/**
 * @brief マップクラスのデストラクタ
 * @param なし
 * @return　なし
*/
Map::~Map()
{

}

/**
 * @brief 壁情報の初期化
 * @param なし
 * @return　なし
 * @detail マイクロマウスのルールに合わせて初期壁の追加,
 *         壁情報の初期化を行う.
*/
void Map::init()
{
  for ( int i = 0; i < 17; i++ ){
    wall.vertical[i] = 0x0000;
    wall.horizontal[i] = 0x0000;
    wall.vertical_known[i] = 0x0000;
    wall.horizontal_knwon[i] = 0x0000;

  }

  // 外周、スタートの右壁を追加
  wall.vertical[0] = 0xffff;
  wall.vertical[1] = 0x0001;
  wall.horizontal[0] = 0xffff;
  wall.vertical[16] = 0xffff;
  wall.horizontal[16] = 0xffff;

  wall.vertical_known[0] = 0xffff;
  wall.vertical_known[1] = 0x0001;
  wall.horizontal_knwon[0] = 0xffff;
  wall.vertical_known[16] = 0xffff;
  wall.horizontal_knwon[16] = 0xffff;

  manegeNorthWall(0, 0, false);
}

/**
 * @brief 壁情報の追加
 * @param uint8_t x マウスのx座標
 * @param uint8_t y マウスのy座標
 * @param ExistWall *exist 壁があるかないかの情報が入っている構造体
 * @param uint8_t direction マウスの向き
 * @return　なし
 * @detail 引数に与えられた座標の壁情報を追加する.
*/
void Map::addWall(  uint8_t x, uint8_t y, ExistWall *exist, uint8_t direction )
{
  switch( direction ){
    case North:
      if ( exist->left ){
        manegeWestWall( x, y, true );
      } else {
        manegeWestWall( x, y, false );
      }

      if ( exist->right ){
        manegeEastWall( x, y, true );
      } else {
        manegeEastWall( x, y, false );
      }

      if ( exist->front ){
        manegeNorthWall( x, y, true );
      } else {
        manegeNorthWall( x, y, false );
      }
      break;

    case West:
      if ( exist->left ){
        manegeSouthWall( x, y, true );
      } else {
        manegeSouthWall( x, y, false );
      }

      if ( exist->right ){
        manegeNorthWall( x, y, true );
      } else {
        manegeNorthWall( x, y, false );
      }

      if ( exist->front ){
        manegeWestWall( x, y, true );
      } else {
        manegeWestWall( x, y, false );
      }
      break;

    case South:
      if ( exist->left ){
        manegeEastWall( x, y, true );
      } else {
        manegeEastWall( x, y, false );
      }

      if ( exist->right ){
        manegeWestWall( x, y, true );
      } else {
        manegeWestWall( x, y, false );
      }

      if ( exist->front ){
        manegeSouthWall( x, y, true );
      } else {
        manegeSouthWall( x, y, false );
      }
      break;

    case East:
      if ( exist->left ){
        manegeNorthWall( x, y, true );
      } else {
        manegeNorthWall( x, y, false );
      }

      if ( exist->right ){
        manegeSouthWall( x, y, true );
      } else {
        manegeSouthWall( x, y, false );
      }

      if ( exist->front ){
        manegeEastWall( x, y, true );
      } else {
        manegeEastWall( x, y, false );
      }
      break;

  }
}

/**
 * @brief 壁情報の読み出し
 * @param uint8_t x マウスのx座標
 * @param uint8_t y マウスのy座標
 * @param uint8_t direction 取得したい壁の方位
 * @return bool 壁情報　有 : true, 無 : false
 * @detail 引数に与えられた座標、方向の壁情報を返す
*/
bool Map::getData( uint8_t x, uint8_t y, uint8_t direction )
{
  uint16_t check_wall = 1;
  bool exist = false;

  if ( direction > East ){
    direction -= 4;
  }

  if ( direction == North ){
        check_wall <<= x;
        check_wall &= wall.horizontal[y + 1];
        if (check_wall != 0) {
            exist = true;
        } else {
      exist = false;
    }

  } else if ( direction == East ){
        check_wall <<= y;
        check_wall &= wall.vertical[x + 1];
        if (check_wall != 0) {
            exist = true;
        } else {
      exist = false;
    }

  } else if ( direction == South ){
        check_wall <<= x;
        check_wall &= wall.horizontal[y];
        if (check_wall != 0) {
            exist = true;
        } else {
      exist = false;
    }
  } else if ( direction == West ){
        check_wall <<= y;
        check_wall &= wall.vertical[x];
        if (check_wall != 0) {
            exist = true;
        } else {
      exist = false;
    }
  }

  return exist;
}

/**
 * @brief 北壁情報の追加/削除
 * @param uint8_t x マウスのx座標
 * @param uint8_t y マウスのy座標
 * @param bool exist 壁が存在するか否か
 * @return　なし
 * @detail 引数に与えられた座標の北壁情報を追加する.
*/
void Map::manegeNorthWall( uint8_t x, uint8_t y, bool exist )
{
  uint16_t data = 1;
  data <<= x;
  wall.horizontal_knwon[y+1] |= data;
  if ( exist ){
    wall.horizontal[y+1] |= data;
  } else {
    wall.horizontal[y+1] &= ~data;
  }
}

/**
 * @brief 南壁情報の追加/削除
 * @param uint8_t x マウスのx座標
 * @param uint8_t y マウスのy座標
 * @param bool exist 壁が存在するか否か
 * @return　なし
 * @detail 引数に与えられた座標の南壁情報を追加する.
*/
void Map::manegeSouthWall( uint8_t x, uint8_t y, bool exist )
{
  uint16_t data = 1;
  data <<= x;
  wall.horizontal_knwon[y] |= data;
  if ( exist ){
    wall.horizontal[y] |= data;
  } else {
    wall.horizontal[y] &= ~data;
  }
}

/**
 * @brief 西壁情報の追加/削除
 * @param uint8_t x マウスのx座標
 * @param uint8_t y マウスのy座標
 * @param bool exist 壁が存在するか否か
 * @return　なし
 * @detail 引数に与えられた座標の西壁情報を追加する.
*/
void Map::manegeWestWall( uint8_t x, uint8_t y, bool exist )
{
  uint16_t data = 1;
  data <<= y;
  wall.vertical_known[x] |= data;
  if ( exist ){
    wall.vertical[x] |= data;
  } else {
    wall.vertical[x] &= ~data;
  }
}

/**
 * @brief 東壁情報の追加/削除
 * @param uint8_t x マウスのx座標
 * @param uint8_t y マウスのy座標
 * @param bool exist 壁が存在するか否か
 * @return　なし
 * @detail 引数に与えられた座標の東壁情報を追加する.
*/
void Map::manegeEastWall( uint8_t x, uint8_t y, bool exist )
{
  uint16_t data = 1;
  data <<= y;
  wall.vertical_known[x+1] |= data;
  if ( exist ){
    wall.vertical[x+1] |= data;
  } else {
    wall.vertical[x+1] &= ~data;
  }
}

/**
 * @brief 壁情報の追加
 * @param uint8_t x マウスのx座標
 * @param uint8_t y マウスのy座標
 * @param bool n,w,s,e それぞれの方向の壁情報を入力
 * @return　なし
 * @detail 引数に与えられた座標の壁情報を追加する.
*/
void Map::addWall(uint8_t x, uint8_t y, bool n, bool w, bool s, bool e )
{
    if ( n ) manegeNorthWall(x,y,true);
    else manegeNorthWall(x,y,false);

    if ( w ) manegeWestWall(x,y,true);
    else manegeWestWall(x,y,false);

    if ( s ) manegeSouthWall(x,y,true);
    else manegeSouthWall(x,y,false);

    if ( e ) manegeEastWall(x,y,true);
    else manegeEastWall(x,y,false);
}

/**
 * @brief 探索をしたかどうかを返す
 * @param uint8_t x マウスのx座標
 * @param uint8_t y マウスのy座標
 * @return bool t or f
 * @detail 引数に与えられた座標が探索済みかどうかを返す
*/
bool Map::checkWall(uint8_t x, uint8_t y)
{
    bool n,s,w,e;
    uint16_t check_wall = 1;
    bool check = false;


    // north
    check_wall <<= x;
    check_wall &= wall.horizontal_knwon[y + 1];
    if (check_wall != 0) n = true;
    else n = false;
    check_wall = 1;


    // east
    check_wall <<= y;
    check_wall &= wall.vertical_known[x + 1];
    if (check_wall != 0) e = true;
    else e = false;
    check_wall = 1;

    // south
    check_wall <<= x;
    check_wall &= wall.horizontal_knwon[y];
    if (check_wall != 0) s = true;
    else s = false;
    check_wall = 1;

    // west
    check_wall <<= y;
    check_wall &= wall.vertical_known[x];
    if (check_wall != 0) w = true;
    else w = false;

    if ( n == true && e == true && s == true && w == true ) check = true;
    else check = false;

    return check;

}

void Map::storeWall()
{

  // 保存用のデータ
  // 再探索するときに使用する
  uint16_t horizontal_buff[17];
  uint16_t vertical_buff[17];

  for(int i = 0; i < 17; i++){
    horizontal_buff[i] = wall.horizontal[i];
    vertical_buff[i] = wall.vertical[i];
  }

  // 未探索の場所に壁をいれる
  for(int x = 0; x < 16; x++){
    for(int y = 0; y < 16; y++){
      bool n,s,w,e;
      uint16_t check_wall = 1;

      // north
      check_wall <<= x;
      check_wall &= wall.horizontal_knwon[y + 1];
      if (check_wall != 0) n = true;
      else n = false;
      check_wall = 1;

      // east
      check_wall <<= y;
      check_wall &= wall.vertical_known[x + 1];
      if (check_wall != 0) e = true;
      else e = false;
      check_wall = 1;

      // south
      check_wall <<= x;
      check_wall &= wall.horizontal_knwon[y];
      if (check_wall != 0) s = true;
      else s = false;
      check_wall = 1;

      // west
      check_wall <<= y;
      check_wall &= wall.vertical_known[x];
      if (check_wall != 0) w = true;
      else w = false;

      if(!n) {
        // add north
        uint16_t data = 1;
        data <<= x;
        horizontal_buff[y+1] |= data;
      }

      if(!s) {
        // add north
        uint16_t data = 1;
        data <<= x;
        horizontal_buff[y] |= data;
      }

      if(!w) {
        // add west
        uint16_t data = 1;
        data <<= y;
        vertical_buff[x] |= data;
      }

      if(!e) {
        // add east
        uint16_t data = 1;
        data <<= y;
        vertical_buff[x+1] |= data;
      }
    }
  }

  std::FILE *fp;
  fp = std::fopen("maze.txt", "w");
  for (int i = 0; i < 17; i++)
  {
    std::fprintf(fp, "%d ", horizontal_buff[i]);
  }

  std::fprintf(fp, "\n");

  for (int i = 0; i < 17; i++)
  {
    std::fprintf(fp, "%d ", vertical_buff[i]);
  };

  std::fprintf(fp, "\n");

  std::fclose(fp);

}

void Map::loadWall()
{
  std::FILE *fp;
  fp = std::fopen("maze.txt", "r");

  if(fp == NULL){
    printf("maze.txt not found\n");
    return;
  }

  int horizontal[17];
  int vertical[17];

  std::fscanf(fp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
  &horizontal[0],&horizontal[1],&horizontal[2],&horizontal[3],
  &horizontal[4],&horizontal[5],&horizontal[6],&horizontal[7],
  &horizontal[8],&horizontal[9],&horizontal[10],&horizontal[11],
  &horizontal[12],&horizontal[13],&horizontal[14],&horizontal[15],&horizontal[16]);

  std::fscanf(fp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
  &vertical[0],&vertical[1],&vertical[2],&vertical[3],
  &vertical[4],&vertical[5],&vertical[6],&vertical[7],
  &vertical[8],&vertical[9],&vertical[10],&vertical[11],
  &vertical[12],&vertical[13],&vertical[14],&vertical[15],&vertical[16]);
  
  for(int i = 0; i < 17; i++){
    wall.horizontal[i] = horizontal[i];
    wall.vertical[i] = vertical[i];
  }

  fclose(fp);
  
}