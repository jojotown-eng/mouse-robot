/**
 * Switch.h
 * @author yuta seya
 * @date 2019 3.25 
*/

#ifndef __SWITCH__H
#define __SWITCH__H

class Switch
{
private:
  static Switch* instance;

public:
  // コンストラクタ
  Switch();
  // デストラクタ
  ~Switch();

  // インスタンスを得る
  static Switch* getInstance();

  // sw0
  bool get0();

  // sw1
  bool get1();

  // sw2
  bool get2();

};

#endif /* __SWITCH__H */