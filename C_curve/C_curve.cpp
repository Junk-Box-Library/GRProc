// C_curve.cpp : DLL アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "C_curve.h"
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

C_CURVE_API char* get_info(int n)
{
	switch (n) {
	case 0:
		return "Ｃ曲線";
	case 1:
		return "c_curve_proc";
	case 2:
		return "c_curve_free";
	case 3:
		return "c_curve_active";
	default:
		return NULL;
	}
}




///////////////////////////////////////////////////////////////////////
//
//  C曲線関数
//
void c(MSGraph<sWord>* vp, int i, double dx, double dy, int cc)
{
	if (i == 0) {
		wDraw_rel(vp, (float)dx, (float)dy, cc);					// ワールド座標系で線を引く
	}
	else {
		c(vp, i - 1, (dx + dy) / 2.0, (dy - dx) / 2.0, cc);
		c(vp, i - 1, (dx - dy) / 2.0, (dy + dx) / 2.0, cc);
	}
}




/*
	処理用関数
		処理不能の場合：  NULL を返す
		処理失敗の場合：  xp->state = ERROR_GRAPH_NODATA にして返す．
		キャンセルの場合：xp->state = ERROR_GRAPH_CANCEL にして返す．
*/
C_CURVE_API MSGraph<sWord>* c_curve_proc(MSGraph<sWord>* vp)
{
	MSGraph<sWord>* xp = NULL;
	
	// 数値入力用ダイアログ
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

	xp = new MSGraph<sWord>(600, 400);

	xp->setWindow(-2.2f, -0.2f, 2.2f, 3.2f);	// ワールド座標系に対して，ビューポートを設定
	xp->wMove(-1.0, 2.0);						// ペンをワールド座標 (1.0, 2.0) へ移動

	c(xp, val, 2.0, 0.0, 1000);

	/////////////////////////////////////////////////////////////////////////////////////////////


	return xp;
}





//
// TRUEを返すと，入力データ無しでもアクティブになる．
//
C_CURVE_API BOOL c_curve_active(void)
{
	return TRUE;
}



C_CURVE_API void c_curve_free(MSGraph<sWord>* xp)
{
	if (xp!=NULL) {
		xp->free();
		delete(xp);
	}
	return;
}

