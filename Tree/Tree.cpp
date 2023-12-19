// Tree.cpp : DLL アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Tree.h"
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


TREE_API char* get_info(int n)
{
	switch (n) {
	case 0:
		return "木";
	case 1:
		return "tree_proc";
	case 2:
		return "tree_free";
	case 3:
		return "tree_active";
	default:
		return NULL;
	}
}






//////////////////////////////////////////////////////////////////////////////////
//  ツリー関数
//

#define  FACTOR  0.7
#define  TURN    0.5


void  tree(MSGraph<sWord>* vp, int n, double length, double angle, int cc)
{
	double dx, dy;

	dx = length * sin(angle);
	dy = length * cos(angle);

	wDraw_rel(vp, (float)dx, (float)dy, cc);			// ワールド座標系で線を引く
	if (n > 0) {
		tree(vp, n - 1, length * FACTOR, angle + TURN, cc);
		tree(vp, n - 1, length * FACTOR, angle - TURN, cc);
	}
	vp->wMove_rel(-(float)dx, -(float)dy);			// ペンをワールド座標での相対位置 (-dx, -dy) へ移動
}




/*
	処理用関数
		処理不能の場合：  NULL を返す
		処理失敗の場合：  xp->state = ERROR_GRAPH_NODATA にして返す．
		キャンセルの場合：xp->state = ERROR_GRAPH_CANCEL にして返す．
*/
TREE_API MSGraph<sWord>* tree_proc(MSGraph<sWord>* vp)
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

	xp = new MSGraph<sWord>(500, 500);

	xp->setWindow(-3, -1, 3, 5);		// ワールド座標系に対して，ビューポートを設定
	xp->wMove(0.0, 0.0);				// ペンをワールド座標 (3.0, 0.0) へ移動

	tree(xp, val, 1.0, 0.0, 300);

	/////////////////////////////////////////////////////////////////////////////////////////////


	return xp;
}





//
// TRUEを返すと，入力データ無しでもアクティブになる．
//
TREE_API BOOL tree_active(void)
{
	return TRUE;
}



TREE_API void tree_free(MSGraph<sWord>* xp)
{
	if (xp!=NULL) {
		xp->free();
		delete(xp);
	}
	return;
}

