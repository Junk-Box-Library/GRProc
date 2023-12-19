// Koch.cpp : DLL アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Koch.h"
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

KOCH_API char* get_info(int n)
{
	switch(n) {
	  case 0 : 
		return "コッホ曲線";
	  case 1 :
		return "koch_proc";
	  case 2 :
		return "koch_free";
	  case 3 :
		return "koch_active";
	  default:
		return NULL;
	}
}





/////////////////////////////////////////////////////////////////////////////
//  コッホ曲線
//

double  dmax, costbl[6], sintbl[6];


void  koch(MSGraph<sWord>* vp, unsigned int a, double d)
{
    if (d<=dmax) {
       wDraw_rel(vp, (float)(d*costbl[a % 6]), (float)(d*sintbl[a%6]), 250);	// ワールド座標系で線を引く
    }
    else {
        d /= 3; koch(vp, a, d); a++; koch(vp, a, d);
        a += 4; koch(vp, a, d); a++; koch(vp, a, d);
        d *= 3;
    }
}



/*
	処理用関数
		処理不能の場合：  NULL を返す
		処理失敗の場合：  xp->state = ERROR_GRAPH_NODATA にして返す．
		キャンセルの場合：xp->state = ERROR_GRAPH_CANCEL にして返す．
*/
KOCH_API MSGraph<sWord>* koch_proc(MSGraph<sWord>* vp)
{
	MSGraph<sWord>* xp = NULL;

	
	// 整数値入力用ダイアログ
	int  val = 0;
	BOOL isok = InputNumDLG(_T("レベル"), &val);
	if (!isok) {
		xp = new MSGraph<sWord>();
		xp->state = JBXL_GRAPH_CANCEL;
		return xp;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////
	// 以下に処理を書く
	//		入力 vp, 出力 xp, レベル val

    unsigned int a;
    double d;

    dmax = 1.0/(val*val);

    xp = new MSGraph<sWord>(601, 301);		
    xp->setWindow(-0.1f, -0.1f, 2.1f, 1.0f);		// ワールド座標系に対して，ビューポートを設定

    for(a=0; a<6; a++){
        costbl[a] = cos(a*PI/3);
        sintbl[a] = sin(a*PI/3);
    }

    xp->wMove(0.0, 0.0);					// ペンをワールド座標 (0.0, 0.0) へ移動
    d = 2.0;
    a = 0;
    koch(xp, a, d);

	/////////////////////////////////////////////////////////////////////////////////////////////


	return xp;
}





//
// TRUEを返すと，入力データ無しでもアクティブになる．
//
KOCH_API BOOL koch_active(void)
{
	return TRUE;
}



KOCH_API void koch_free(MSGraph<sWord>* xp)
{
	if (xp!=NULL) {
		xp->free();
		delete(xp);
	}
	return;
}

