// Bin.cpp : DLL アプリケーションのエントリ ポイントを定義します。
//

//#include "stdafx.h"
#include "Bin.h"
#include "Window.h"

#include "InputNumDLG.h"
//#include "ProgressBarDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace jbxl;
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

BIN_API char* get_info(int n)
{
	switch(n) {
	  case 0 : 
		return "二値化";		// ここにプラグイン名を書く
	  case 1 :
		return "bin_proc";		// 処理用関数の名前
	  case 2 :
		return "bin_free";		// 処理後のメモリ開放用関数の名前
	  case 3 :
		return "bin_active";	// アクティブ判定の関数の名前
	  default:
		return NULL;
	}
}


/*
	処理用関数
		処理不能の場合：  NULL を返す
		処理失敗の場合：  xp->state = ERROR_GRAPH_NODATA にして返す．
		キャンセルの場合：xp->state = ERROR_GRAPH_CANCEL にして返す．
*/
BIN_API MSGraph<sWord>* bin_proc(MSGraph<sWord>* vp)
{
	MSGraph<sWord>* xp = NULL;
	
	// 整数値入力用ダイアログ
	int  val  = 0;
	BOOL isok = InputNumDLG(_T("数値を入れてください"), &val);
	if (!isok) {
		xp = new MSGraph<sWord>();
		xp->state = JBXL_GRAPH_CANCEL;
		return xp;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	// 以下に処理コードを書く
	//		入力 vp, 出力 xp, 閾値 val
	//		vp->xs: 画像のXサイズ，vp->ys: 画像のYサイズ，vp->zs: 画像のZサイズ
	//		vp->point(i,j,k): 画像の (i,j,k) 位置の画素値への参照
	//		vp->max: vpの濃度値の最高, vp->min: vpの濃度値の最低
	//		vp->color: カラーモード  GRAPH_COLOR_MONO: モノクロ，GRAPH_COLOR_RGB: RGBカラー
    /////////////////////////////////////////////////////////////////////////////////////////////

	xp = new MSGraph<sWord>(vp->xs, vp->ys, vp->zs);

	for (int k = 0; k < xp->zs; k++) {
		for (int j = 0; j < xp->ys; j++) {
			for (int i = 0; i < xp->xs; i++) {
				if (vp->point(i, j, k) >= val) xp->point(i, j, k) = vp->max;
				else                           xp->point(i, j, k) = vp->min;
			}
		}
	}

	xp->color = vp->color;		// カラーモード

    /////////////////////////////////////////////////////////////////////////////////////////////
    // 処理コードはここまで
    //////////////////////////////////////////////////////////////////////////////////////////////

	return xp;
}


/* 
	アクティブ判定の関数
		TRUEを返すと，入力データ無しでもアクティブになる．
		FALSEを返すと，入力データが読み込まれるまでアクティブにならない．
*/
BIN_API BOOL  bin_active(void)
{
	return FALSE;
}


/*
	メモリ開放用関数
	　	処理後のメモリ開放用関数
*/
BIN_API void bin_free(MSGraph<sWord>* xp)
{
	if (xp!=NULL) {
		xp->free();
		delete(xp);
	}
	return;
}

