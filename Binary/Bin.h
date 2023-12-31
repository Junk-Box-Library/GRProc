// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された BIN_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// BIN_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。

#ifdef BIN_EXPORTS
#define BIN_API __declspec(dllexport)
#else
#define BIN_API __declspec(dllimport)
#endif

#include "tools++.h"
#include "GraphLib.h"

using namespace jbxl;

BIN_API char* get_info(int n);
BIN_API MSGraph<sWord>* bin_proc(MSGraph<sWord>* vp);
BIN_API void bin_free(MSGraph<sWord>* vp);
BIN_API BOOL bin_active(void);
