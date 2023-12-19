// General.cpp : DLL アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "General.h"
#include "Window.h"

#include "InputNumDLG.h"
//#include "ProgressBarDLG.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace jbxl;
using namespace jbxwl;


// 唯一のアプリケーション オブジェクトです
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

GENERAL_API char* get_info(int n)
{
	switch(n) {
	  case 0 : 
		return "拡大・縮小（補間）";
	  case 1 :
		return "general_proc";		// 処理用関数の名前
	  case 2 :
		return "general_free";		// 処理後のメモリ開放用関数の名前
	  case 3 :
		return "general_active";	// アクティブ判定の関数の名前
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
GENERAL_API MSGraph<sWord>* general_proc(MSGraph<sWord>* vp)
{
	MSGraph<sWord>* xp = NULL;
		

	/// 整数値入力用ダイアログ
	/////// 必要な場合はコメントを外す．
	BOOL isok;
	int  val = 0;
	isok = InputNumDLG(_T("拡大縮小率"), &val);
	if (!isok) {
		xp = new MSGraph<sWord>();
		xp->state = JBXL_GRAPH_CANCEL;
		return xp;
	}
	

	////////////////////////////////////////////////////////////////////////////////
	// 以下に処理コードを書く
	//		入力 vp, 出力 xp
	//		vp->xs: 画像のXサイズ，vp->ys: 画像のYサイズ，vp->zs: 画像のZサイズ
	//		vp->point(i,j,k): 画像の (i,j,k) 位置の画素値への参照
	//		vp->max: vpの濃度値の最高, vp->min: vpの濃度値の最低
	//		vp->color: カラーモード  
	//			GRAPH_COLOR_MONO:	モノクロ 8bi，
	//			GRAPH_COLOR_RGB16:	RGB 16bit カラー, R5G6B5
    //			GRAPH_COLOR_RGB:	RGB 8bitx3=24bit カラー, R8G8B8
	////////////////////////////////////////////////////////////////////////////////

	double mag = val / 100.;
	if (mag <= 0.0) return xp;
	
	int i, j, k, l, px;
	double x, y, a, b, c, d, al, bt;

	int xs = (int)(vp->xs * mag) + 1;
	int ys = (int)(vp->ys * mag) + 1;
	xp = new MSGraph<sWord>(xs, ys);
	
	for (int jj = 0; jj < ys; jj++) {
		for (int ii = 0; ii < xs; ii++) {
			x = ii / mag;
			y = jj / mag;
	
			i = (int)x;
			j = (int)y;
			k = i + 1;
			l = j + 1;
			if (k >= vp->xs) k = vp->xs - 1;
			if (l >= vp->ys) l = vp->ys - 1;
			al = x - i;
			bt = y - j;
			
			a = vp->point(i, j);
			b = vp->point(k, j);
			c = vp->point(i, l);
			d = vp->point(k, l);
			
			px = a * (1 - al) * (1 - bt) + b * al * (1 - bt) + c * (1 - al) * bt + d * al * bt;
			
			if (px < 0) px = 0;
			else if (px > 255) px = 255;
			
			xp->point(ii, jj) = px;
		}
	}

	xp->color = vp->color;		// カラーモード	

    ////////////////////////////////////////////////////////////////////////////////
    // 処理コードはここまで
    ////////////////////////////////////////////////////////////////////////////////


	return xp;
}




/* 
	アクティブ判定の関数
		TRUEを返すと， 入力データ無しでもメニューがアクティブになる．
		FALSEを返すと，入力データが読み込まれるまでアクティブにならない．

*/
GENERAL_API BOOL  general_active(void)
{
	return FALSE;
}




/*
	メモリ開放用関数（ほとんどの場合，変更する必要はない）
	　	処理後のメモリ開放用関数
*/
GENERAL_API void general_free(MSGraph<sWord>* xp)
{
	if (xp!=NULL) {
		xp->free();
		delete(xp);
	}
	return;
}


