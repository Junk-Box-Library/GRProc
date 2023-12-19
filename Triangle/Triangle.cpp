// Triangle.cpp : DLL アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Triangle.h"
#include "Window.h"

#include "InputNumDLG.h"
//#include "ProgressBarDLG.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace jbxwl;

 

//////////////////////////////////////////////////////////////////////
// 唯一のアプリケーション オブジェクトです。

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// MFC を初期化して、エラーの場合は結果を印刷します。
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0)) {
		// TODO: 必要に応じてエラー コードを変更してください。
		_tprintf(_T("致命的なエラー: MFC の初期化ができませんでした\n"));
		nRetCode = 1;
	}
	else{
		// TODO: アプリケーションの動作を記述するコードをここに挿入してください。
	}

	return nRetCode;
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//

TRIANGLE_API char* get_info(int n)
{
	switch (n) {
	case 0:
		return "シェルピンスキーの三角形";
	case 1:
		return "triangle_proc";
	case 2:
		return "triangle_free";
	case 3:
		return "triangle_active";
	default:
		return NULL;
	}
}



//////////////////////////////////////////////////////////////////////////////
//
// シェルピンスキーの三角形
//
#define N 65

void triangle(MSGraph<sWord>* vp, float i, float j)
{
	wLine(*vp, i, j + 1, i - 1, j, 250);
	wLine(*vp, i - 1, j, i + 1, j, 250);
	wLine(*vp, i + 1, j, i, j + 1, 250);
}



/*
	処理用関数
		処理不能の場合：  NULL を返す
		処理失敗の場合：  xp->state = ERROR_GRAPH_NODATA にして返す．
		キャンセルの場合：xp->state = ERROR_GRAPH_CANCEL にして返す．
*/
TRIANGLE_API MSGraph<sWord>* triangle_proc(MSGraph<sWord>* vp)
{
	MSGraph<sWord>* xp = NULL;

	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// 以下に処理を書く
	//		入力 vp, 出力 xp, レベル val

	static char a[2 * N + 1], b[2 * N + 1];

	xp = new MSGraph<sWord>(600, 400);
	xp->setWindow(-N, 0.0, N, N + 1);		// ワールド座標系に対して，ビューポートを設定

	for (int i = 0; i <= 2 * N; i++) a[i] = 0;
	a[N] = 1;

	for (int j = 1; j < N; j++) {
		for (int i = N - j; i <= N + j; i++) {
			if (a[i]) triangle(xp, (float)(i - N), (float)N - j);
		}
		for (int i = N - j; i <= N + j; i++) {
			b[i] = (a[i - 1] != a[i + 1]);
		}
		for (int i = N - j; i <= N + j; i++) {
			a[i] = b[i];
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////


	return xp;
}





//
// TRUEを返すと，入力データ無しでもアクティブになる．
//
TRIANGLE_API BOOL triangle_active(void)
{
	return TRUE;
}



TRIANGLE_API void triangle_free(MSGraph<sWord>* xp)
{
	if (xp!=NULL) {
		xp->free();
		delete(xp);
	}
	return;
}

