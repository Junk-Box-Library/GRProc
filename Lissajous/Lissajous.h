// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された LISSAJOUS_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// LISSAJOUS_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。


#ifdef LISSAJOUS_EXPORTS
#define LISSAJOUS_API __declspec(dllexport)
#else
#define LISSAJOUS_API __declspec(dllimport)
#endif


#include "tools++.h"
#include "GraphLib.h"


using namespace jbxl;


LISSAJOUS_API char* get_info(int n);
LISSAJOUS_API MSGraph<sWord>* lissajous_proc(MSGraph<sWord>* vp);
LISSAJOUS_API void  lissajous_free(MSGraph<sWord>* vp);
LISSAJOUS_API BOOL  lissajous_active(void);


