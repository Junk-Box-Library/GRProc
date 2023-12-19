// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された KOCH_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// KOCH_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。


#ifdef KOCH_EXPORTS
#define KOCH_API __declspec(dllexport)
#else
#define KOCH_API __declspec(dllimport)
#endif


#include "tools++.h"
#include "GraphLib.h"


using namespace jbxl;


KOCH_API char* get_info(int n);
KOCH_API MSGraph<sWord>* koch_proc(MSGraph<sWord>* vp);
KOCH_API void  koch_free(MSGraph<sWord>* vp);
KOCH_API BOOL  koch_active(void);

