// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された GENERAL_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// GENERAL_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。


#ifdef GENERAL_EXPORTS
#define GENERAL_API __declspec(dllexport)
#else
#define GENERAL_API __declspec(dllimport)
#endif


#include "tools++.h"
#include "GraphLib.h"

using namespace jbxl;

GENERAL_API char* get_info(int n);
GENERAL_API MSGraph<sWord>* general_proc(MSGraph<sWord>* vp);
GENERAL_API void general_free(MSGraph<sWord>* vp);
GENERAL_API BOOL general_active(void);
