// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された TREE_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// TREE_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。


#ifdef TREE_EXPORTS
#define TREE_API __declspec(dllexport)
#else
#define TREE_API __declspec(dllimport)
#endif


#include "tools++.h"
#include "GraphLib.h"


using namespace jbxl;


TREE_API char* get_info(int n);
TREE_API MSGraph<sWord>* tree_proc(MSGraph<sWord>* vp);
TREE_API void  tree_free(MSGraph<sWord>* vp);
TREE_API BOOL  tree_active(void);

