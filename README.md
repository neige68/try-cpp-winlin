# try-cpp-winlin

Windows, Linux 両方でビルト・実行できる C++ プログラムを作ってみる

とりあえずの目標は、昔作った、以前は MS-DOS, MacOS, UNIX, VOS3 で動作していたが、
現在は 32bit Windows (Shift-JIS) のみで
アプリケーション組み込み用になっている Lisp インタプリタを、
32bit Windows (Shift-JIS) でも動作させつつ Windows, Linux 両方で
UNICODE 対応で 64bit でも動かしたいので、その基盤を整える。


## 使用するコンパイラとビルドツールとライブラリ

* Windows では Visual Studio, 同梱の MSBuild

* Linux では gcc, make

* 双方で CMake, Boost を使用


## ソースコードのエンコーディング

UTF-8 で大丈夫だと思う


## ビルドと実行のコマンドを共通化したい

* ビルドのコマンドは mak, 実行のコマンドは exe とする

* Windows ではカレントディレクトリの mak.bat, exe.bat を使用する

* Linux では bash を前提とし、mak はシェルの alias で alias mak='pushd
  build; make; popd' と定義し、exe は alias exe=./exe でカレントディレ
  クトリのシェルスクリプト exe を呼び出す。

alias は ~/.bashrc から呼び出される ~/.bash_aliases で定義する

変更した ~/.bash_aliases をすぐ反映したいときは source ~/.bash_aliases とする


## ワイド文字、マルチバイト文字変換

C++ 標準ライブラリの std::mbstowcs, std::wcstombs でできると思われる。


## コマンドライン引数

Windows では _tmain で TCHAR** argv で受け取る。
Linux では main にて char** argv で、環境変数 LANG で指定されたエンコードで受け取る。


## 例外メッセージ

C++ 標準ライブラリの std::exception のメッセージは std::string になっている。
Boost Spirit X3 では wstring を UTF-8 決め打ちで string に変換していた記憶がある。
そういうことがあると Windows (Shift-JIS) では
UTF-8 と Shift-JIS が混在することにならないか危惧している。


## ターミナルの行の長さ

pretty-print に必要
