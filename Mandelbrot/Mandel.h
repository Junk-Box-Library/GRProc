// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された MANDEL_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// MANDEL_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。


#ifdef MANDEL_EXPORTS
#define MANDEL_API __declspec(dllexport)
#else
#define MANDEL_API __declspec(dllimport)
#endif


#include "tools++.h"
#include "GraphLib.h"


using namespace jbxl;


MANDEL_API char* get_info(int n);
MANDEL_API MSGraph<sWord>* mandel_proc(MSGraph<sWord>* vp);
MANDEL_API void	 mandel_free(MSGraph<sWord>* vp);
MANDEL_API BOOL  mandel_active(void);


