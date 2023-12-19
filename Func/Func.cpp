// General.cpp : DLL アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Func.h"
#include "Window.h"

#include "InputNumDLG.h"
//#include "ProgressBarDLG.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace jbxwl;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 唯一のアプリケーション オブジェクトです。

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// MFC を初期化して、エラーの場合は結果を印刷します。
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0)) {
		// TODO: 必要に応じてエラー コードを変更してください。
		_tprintf(_T("致命的なエラー: MFC の初期化ができませんでした。\n"));
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

FUNC_API char* get_info(int n)
{
	switch(n) {
	  case 0 : 
		return "関数";
	  case 1 :
		return "func_proc";
	  case 2 :
		return "func_free";
	  case 3 :
		return "func_active";
	  default:
		return NULL;
	}
}



/* 
	TRUEを返すと，入力データ無しでもアクティブになる．
*/
FUNC_API BOOL  func_active(void)
{
	return TRUE;
}



FUNC_API void  func_free(MSGraph<sWord>* xp)
{
	if (xp!=NULL) {
		xp->free();
		delete(xp);
	}
	return;
}





//
// 描画する関数
//
double func(double x)
{
	return x*sin(x)*cos(x);
}




/*
	処理不能の場合：  NULL を返す
	処理失敗の場合：  xp->state=ERROR_GRAPH_NODATA にして返す．
	キャンセルの場合：xp->state=ERROR_GRAPH_CANCEL にして返す．
*/
FUNC_API MSGraph<sWord>* func_proc(MSGraph<sWord>* vp)
{
	MSGraph<sWord>* xp = NULL;
	

    /////////////////////////////////////////////////
    // 以下に処理コードを書く
    //		入力 vp, 出力 xp
    /////////////////////////////////////////////////

	double xx, yy, dx, ox, oy;
	int N = 100;			// x 軸の刻数
	
	double XMIN = -4.0;		// x 軸の最小値
	double XMAX = 4.0;		// x 軸の最大値
	double YMIN = -1.5;		// y 軸の最小値
	double YMAX = 1.5;		// y 軸の最大値

	xp = new MSGraph<sWord>(500, 500);
	xp->setWindow(XMIN, YMIN, XMAX, YMAX);
	
	wLine(*xp, XMIN, 0.0, XMAX, 0.0, 100);
	wLine(*xp, 0.0, YMIN, 0.0, YMAX, 100);
	
	dx = (XMAX-XMIN)/(double)N;
	ox = XMIN;
	oy = func(ox);

	for (int i=1; i<=N; i++) {
		xx = ox + dx;
		yy = func(xx);
		wLine(*xp, ox, oy, xx, yy, 250);	// (ox,oy)から (xx,yy) へ線を引く
		ox = xx;
		oy = yy;
	}

    /////////////////////////////////////////////////
    // 処理コードはここまで
    /////////////////////////////////////////////////


	return xp;
}

