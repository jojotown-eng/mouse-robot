/**
 * Motor.h
 * @author yuta seya
 * @date 2019 3.25 
*/

#ifndef __MOTOR__H
#define __MOTOR__H

class Motor {
private:
  static Motor* instance;
  
  bool status = false; // 現在のステータス
  
public:
  // コンストラクタ
  Motor();

  //デストラクタ
  ~Motor();

  // インスタンスを得る
  static Motor* getInstance();

  // ソフトウェアスイッチをオンオフする
  void setSoftwareSwitch( bool sw );

  // モーターのコントロールをする
  void control( int left, int right );

  // モーターのステップ数のカウンタを読む
  void readStepCount( int *left, int *right );

  // モーターのステップ数をカウントをリセットする
  void resetStepCount();

private:
  // 左モーターのコントロール
  void leftControl( int hz );

  // 右モーターのコントロール
  void rightControl( int hz );

  // ソフトウェアスイッチのオン
  void on();

  // ソフトウェアスイッチのオフ
  void off();

  // 左のカウント
  int readLeft();

  // 右のカウント
  int readRight();

  // 左のカウントをリセット
  void resetLeftStep();

  // 右のカウントをリセット
  void resetRightStep();


};

#endif /* __MOTOR__H */