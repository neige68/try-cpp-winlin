# try-cpp-winlin

Windows, Linux 両方でビルト・実行できるキャラクタベースの C++ プログラムを作ってみる

## 目的

昔作った Lisp インタプリタを、Windows, Linux 両方で動かしたいので、
その方法を確立する。
Windows では 32bit/64bit 両方, Shift-JIS/UNICODE 両方とする。
それは以前は MS-DOS, MacOS, UNIX, VOS3 で動いていたが、
現在は 32bit Windows Shift-JIS GUI アプリケーションの組み込み用になっている。


## 対象

### 使用するコンパイラとビルドツールとライブラリ

* Windows では Visual Studio, 同梱の MSBuild

* Linux では gcc, make

* 双方で CMake, Boost を使用


### 実際に使用しているバージョン

* Windows: Windows 10, Visual Sutdio 2019 (14.2), CMake 3.19.2, Boost 1.75,

* Linux: Debian GNU/Linux 10(buster), gcc 8.3, CMake 3.13.4, Boost 1.74, ncurses 6.1


## ビルド・実行方法

### ビルド方法

* Windows では vcvarsall.bat のあるディレクトリを環境変数 VC142 に設定しておき、mak.bat を実行する

* Linux では、初回は mkdir build; pushd build; cmake ..; make; popd で行う。以降は mkdir と cmake を抜かしてよい。alias も定義する。


### 実行方法

* Windows では exe.bat に 64 u hello とテスト用の任意の引数を指定する。64 と u は省略可能である。

* Linux ではシェルスクリプト exe に hello とテスト用の任意の引数を指定する

* 任意の引数の例: 🦆鴨かもｶﾓ


## 検討項目

### ソースコードのエンコーディング(完了)

UTF-8 とする。
VC ではコンパイルオプション /utf-8 オプションが必要となるので、
CMakeLists.txt にて、CMAKE_GENERATOR に "Visual Studio" が含まれるときに、
CMAKE_CXX_FLAGS にそれを追加する。


### ビルドと実行のコマンドを共通化(完了)

* ビルドのコマンドは mak, 実行のコマンドは exe とする

* Windows ではカレントディレクトリの mak.bat, exe.bat を使用する

* Linux では bash を前提とし、mak はシェルの alias で alias mak='pushd
  build; make; popd' と定義し、exe は alias exe=./exe でカレントディレ
  クトリのシェルスクリプト exe を呼び出す。

alias は ~/.bashrc から呼び出される ~/.bash_aliases で定義する

変更した ~/.bash_aliases をすぐ反映したいときは source ~/.bash_aliases とする

Emacs の M-x compile で mak を実行するには、
.emacs 等に (setq shell-command-switch "-ic") を 追加し、
bash のインタラクティブシェルを起動するよう指示する。


### コマンドライン引数の処理(完了)

Windows では _tmain で TCHAR** argv で受け取る。
Linux では main にて char** argv で、環境変数 LANG で指定されたエンコードで受け取る。


### ワイド文字、マルチバイト文字変換(完了)

C++ 標準ライブラリの std::mbstowcs, std::wcstombs で行う。
VC ではセキュリティ強化版 mbstowcs_s, wcstombs_s で行う。

プログラムの最初に std::locale::global(std::locale("")); を行い、
グローバルロケールをデフォルトロケールに設定すると、
素直に変換できる。

const char* であろうと const wchar_t* であろうと、
オーバロードした to_wstring 関数で std::wstring に変換して処理できるようにする。

Windows のワイド文字は UTF-16 であり、
Linux のワイド文字は UTF-32 であるとのことなので、
ワイド文字のままデータ交換はできない。
UTF-8 を介すのが望ましい。


### ターミナルの行の長さの取得(完了)

pretty-print に必要なので取得したい。

Linux ではライブラリ ncurses を使用。

Windows では API GetConsoleScreenBufferInfo で取得できる。

Windows の Emacs の shell から起動したプログラムではエラーとなるが、
環境変数にシェル起動時の桁数が設定されているのでそれを取得する。


### 例外メッセージ(未着手)

C++ 標準ライブラリの std::exception のメッセージは std::string になっている。
Boost Spirit X3 では wstring を UTF-8 決め打ちで string に変換していた記憶がある。
そういうことがあると Windows (Shift-JIS) では
UTF-8 と Shift-JIS が混在することにならないか危惧している。
