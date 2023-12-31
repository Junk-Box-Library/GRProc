// Mandel.cpp : DLL アプリケーションのエントリ ポイントを定義します。
//

//#include "stdafx.h"
#include "Mandel.h"
#include "Window.h"

#include "InputNumDLG.h"
//#include "ProgressBarDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace  jbxwl;


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

MANDEL_API char* get_info(int n)
{
	switch(n) {
	  case 0 : 
		return "マンデルブロー集合";
	  case 1 :
		return "mandel_proc";
	  case 2 :
		return "mandel_free";
	  case 3 :
		return "mandel_active";
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
MANDEL_API MSGraph<sWord>* mandel_proc(MSGraph<sWord>* vp)
{
	MSGraph<sWord>* xp = NULL;

	int	   Xsize  = 600;	// スクリーンのXサイズ
	double Infnty = 1.0e8;	// 無限大

	double Xmin  = -2.5;	// X軸（実数部）の最小値の初期値
	double Xmax  = 1.0;		// X軸（実数部）の最大値の初期値
	double Ymin  = -1.5;	// Y軸（虚数部）の最小値の初期値
	double Ymax	 = 1.5;		// Y軸（虚数部）の最大値の初期値
	double val   = 200;		// 最大繰り返し回数の初期値

	// 数値入力用ダイアログ
	BOOL isok = InputMultiFloatNumDLG(_T("X軸の最小値"), &Xmin, _T("X軸の最大値"), &Xmax, 
									  _T("Y軸の最小値"), &Ymin, _T("Y軸の最大値"), &Ymax, 
									  _T("最大繰り返し回数"), &val);
	if (!isok) {
		xp = new MSGraph<sWord>();
		xp->state = JBXL_GRAPH_CANCEL;
		return xp;
	}

    /////////////////////////////////////////
    // 以下に処理コードを書く
    //		入力 vp, 出力 xp
    /////////////////////////////////////////

	int	   xsize = Xsize;
	int	   ysize = (int)(xsize*(Ymax-Ymin)/(Xmax-Xmin) + 0.5);
	double dC	 = (Xmax-Xmin)/xsize;		// = (Ymax-Ymin)/ysize;	// 刻み幅
	
	xp = new MSGraph<sWord>(xsize, ysize);	// (xsize × ysize) の画用紙を用意

	int    i, j, k;
	double Cr, Ci, Zr, Zi, Zrp, Zip;

	Ci = Ymax;
	for (j=0; j<xp->ys; j++) {
		Cr = Xmin;
		for (i=0; i<xp->xs; i++) {
			Zrp = 0.0;
			Zip = 0.0;
			k   = 0;

			// 漸化式の計算  Z(n+1) = Z(n)^2 + C
			do {
				Zr  = Zrp*Zrp - Zip*Zip + Cr;
				Zi  = 2.*Zrp*Zip        + Ci;
				Zrp = Zr;
				Zip = Zi;
				k++;
			} while (Zr<Infnty && Zi<Infnty && k<=(int)val);		// 発散のチェック
			
			xp->point(i, j) = (sWord)((double)(val-k+1)*4095/val);	// 色を作って点を打つ（ k==1:白, k==val+1:黒）
			Cr += dC;
		}
		Ci -= dC;
	}
	
	xp->color = GRAPH_COLOR_RGB16;	//GRAPH_COLOR_ARGB16;		// カラーモード

    /////////////////////////////////////////
    // 処理コードはここまで
    /////////////////////////////////////////

	return xp;
}


/* 
	TRUEを返すと，入力データ無しでもアクティブになる．
*/
MANDEL_API BOOL  mandel_active(void)
{
	return TRUE;
}


MANDEL_API void  mandel_free(MSGraph<sWord>* xp)
{
	if (xp!=NULL) {
		xp->free();
		delete(xp);
	}
	return;
}
