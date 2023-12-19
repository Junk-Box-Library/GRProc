// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された FUNC_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// FUNC_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。


#ifdef FUNC_EXPORTS
#define FUNC_API __declspec(dllexport)
#else
#define FUNC_API __declspec(dllimport)
#endif


#include "tools++.h"
#include "GraphLib.h"


using namespace jbxl;


FUNC_API char* get_info(int n);
FUNC_API MSGraph<sWord>* func_proc(MSGraph<sWord>* vp);
FUNC_API void  func_free(MSGraph<sWord>* vp);
FUNC_API BOOL  func_active(void);


