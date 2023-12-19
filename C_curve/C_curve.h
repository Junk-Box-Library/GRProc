// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された C_CURVE_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// C_CURVE_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。


#ifdef C_CURVE_EXPORTS
#define C_CURVE_API __declspec(dllexport)
#else
#define C_CURVE_API __declspec(dllimport)
#endif


#include "tools++.h"
#include "GraphLib.h"


using namespace jbxl;


C_CURVE_API char* get_info(int n);
C_CURVE_API MSGraph<sWord>* c_curve_proc(MSGraph<sWord>* vp);
C_CURVE_API void  c_curve_free(MSGraph<sWord>* vp);
C_CURVE_API BOOL  c_curve_active(void);

