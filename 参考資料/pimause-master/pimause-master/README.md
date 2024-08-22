# ラズベリーパイマウスのリポジトリ

## ファイル構造
- pimause
  - Inc
    - Maze
      - *.h
    - peripheral
      - *.h
    - Common
      - *.h
  - Src
    - Maze
      - .*cpp
    - peripheral
      - .*cpp
    - Common
      - .*cpp
  - .gitignore
  - main.cpp
  - makefile
  - README.md
  
 ## 使用方法
 makefileのあるカレントディレクトリに移動後、makefileをたたくことでコンパイル、プログラムの実行を行うことができる。
 
 コンパイルしたいときは
 ```
 $ make
 ```
 または、
 ``` 
 $ make all
 ```
 をコマンドラインで実行することでできる。
 make all 実行した場合、./buildのコンパイル済みデータを一度削除したのち、すべてのファイルがコンパイルさせる。
 makeの場合は、変更したファイルのみのコンパイルが行われる。
 
 ./buildを削除したい場合は、
 ``` 
 $ make clean
 ```
 を実行すればよい。
 
 実行をしたい場合は、
 ``` 
 $ make run
 ```
 を実行すればよい。
 
 ## 内容物
 #### ver1.0
 - 迷路
    - クラシックマイクロマウス競技の16*16マスの迷路を足立法で解くプログラムを作成
 - ペリファイラル設定
    - [RT Corp.RaspberryPiMouseリポジトリ](https://github.com/rt-net/RaspberryPiMouse)
    のドライバをたたき、LED,ブザー、モーター、スイッチを使用できるようにするクラスを作成
#### ver1.1
   - ペリファイラル設定
      - センサを読めるようにするクラスを作成
    
#### ver1.2
- 各クラスにインスタンスを用意し、インスタンスの受け渡しを可能にした。
- ファイルの名前を変更
 
 
 ## 参考文献

[ラズベリーパイマウスの取り扱い説明書v2.0](http://resources.rt-net.jp/products/RPiM/raspberryPiMouseManual_2016_06_15.pdf)

[ラズベリーパイマウスの商品ページ](https://www.rt-net.jp/products/raspimouse2)

このりポジトリの中に以下のソースコードを含みます。


[シンプルで応用の利くmakefile URIN HACK](http://urin.github.io/posts/2013/simple-makefile-for-clang)

### 更新日
2019 3 / 26 ver 1.0

2019 3 / 27 ver 1.1

2019 3/ 28 ver 1.2
