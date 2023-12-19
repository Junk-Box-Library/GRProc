// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された TRIANGLE_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// TRIANGLE_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。


#ifdef TRIANGLE_EXPORTS
#define TRIANGLE_API __declspec(dllexport)
#else
#define TRIANGLE_API __declspec(dllimport)
#endif


#include "tools++.h"
#include "GraphLib.h"


using namespace jbxl;


TRIANGLE_API char* get_info(int n);
TRIANGLE_API MSGraph<sWord>* triangle_proc(MSGraph<sWord>* vp);
TRIANGLE_API void  triangle_free(MSGraph<sWord>* vp);
TRIANGLE_API BOOL  triangle_active(void);

