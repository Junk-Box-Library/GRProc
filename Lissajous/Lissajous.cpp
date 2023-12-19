// Lissajous.cpp : DLL アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Lissajous.h"
#include "Window.h"

#include "InputNumDLG.h"
//#include "ProgressBarDLG.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



using namespace jbxwl;



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

LISSAJOUS_API char* get_info(int n)
{
	switch(n) {
	  case 0 : 
		return "リサージュ";
	  case 1 :
		return "lissajous_proc";
	  case 2 :
		return "lissajous_free";
	  case 3 :
		return "lissajous_active";
	  default:
		return NULL;
	}
}





/* 
	TRUEを返すと，入力データ無しでもアクティブになる．
*/
LISSAJOUS_API BOOL  lissajous_active(void)
{
	return TRUE;
}



LISSAJOUS_API void lissajous_free(MSGraph<sWord>* xp)
{
	if (xp!=NULL) {
		xp->free();
		delete(xp);
	}
	return;
}




/*
	処理不能の場合：  NULL を返す
	処理失敗の場合：  xp->state=JBXL_GRAPH_NODATA_ERROR にして返す．
	キャンセルの場合：xp->state=JBXL_GRAPH_CANCEL にして返す．
*/
LISSAJOUS_API MSGraph<sWord>* lissajous_proc(MSGraph<sWord>* vp)
{
	MSGraph<sWord>* xp = NULL;

	// 整数値入力用ダイアログ
	BOOL isok;
	int  val = 0;
	isok = InputNumDLG(_T("X-Rate"), &val);
	if (!isok) {
		xp = new MSGraph<sWord>();
		xp->state = JBXL_GRAPH_CANCEL;
		return xp;
	}

	int  val2 = 0;
	isok = InputNumDLG(_T("Y-Rate"), &val2);
	if (!isok) {
		xp = new MSGraph<sWord>();
		xp->state = JBXL_GRAPH_CANCEL;
		return xp;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////
	// 以下に処理を書く
	//		入力 vp, 出力 xp, レイト val, val2

    int      N = 1000;
    int      i, rx, ry;
    double   th, rr, dt, xx, yy, ox, oy;

    rr = 1.0;                           // 半径
    dt = 2.0*PI/N;                      // 角度の刻み
    xp = new MSGraph<sWord>(500, 500);
	rx = val;
	ry = val2;

    xp->setWindow(-1.2*rr, -1.2*rr, 1.2*rr, 1.2*rr);    // 座標の再定義
    wLine(*xp, -1.2*rr, 0.0, 1.2*rr, 0.0, 100);         // x軸
    wLine(*xp, 0.0, -1.2*rr, 0.0, 1.2*rr, 100);         // y軸

    ox = rr;                            // 開始点の x座標
    oy = 0.0;                           // 開始点の y座標
    for (i=1; i<=N; i++) {
        th = dt*i;                      // 角度
        xx = rr*cos(th*rx);             // x座標
        yy = rr*sin(th*ry);             // y座標
        wLine(*xp, ox, oy, xx, yy, 250);// ラインを引く
        ox = xx;                        // ラインの終点を次回の始点にする(x)
        oy = yy;                        // ラインの終点を次回の始点にする(y)
    }

	/////////////////////////////////////////////////////////////////////////////////////////////



	return xp;
}









