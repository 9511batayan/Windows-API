#include <windows.h>
#include <tchar.h>

#define	ID_MYTIMER	(32767)
#define	ID_MYCHILD	(100)
#define W_WIDTH (700)	//ウィンドウサイズ幅
#define W_HEIGHT (400)	//ウィンドウサイズ高さ
#define	CHD_WIDTH	(100)
#define	CHD_HEIGHT	(57)

// プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChdProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL InitApp(HINSTANCE, WNDPROC, LPCTSTR);
BOOL InitInstance(HINSTANCE, int, LPCTSTR);

static TCHAR szClassName[] = _T("Win32AP_kadai3");
static TCHAR szchClassName[] = _T("child");
static TCHAR szTitle[] = _T("icehockey_reflect");

int img_start_x = 83;		//スタート地点のx座標
int img_start_y = 29;		//スタート地点のy座標
int img_end_x = 482;		//右端地点のx座標
int img_end_y = 245; //下地点でのy座標

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow) {
	MSG msg;

	if (!hPrevInst) {
		if (!InitApp(hCurInst, WndProc, szClassName)) {
			return FALSE;
		}
	}
	if (!InitInstance(hCurInst, nCmdShow, szClassName)) {
		return FALSE;
	}
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

BOOL InitApp(HINSTANCE hInst, WNDPROC WndProc, LPCTSTR szClassName) {
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;

	return (RegisterClass(&wc));
}

BOOL InitInstance(HINSTANCE hInst, int nCmdShow, LPCTSTR szClassName) {
	HWND hWnd;

	hWnd = CreateWindow(
		szClassName,
		szTitle,				//タイトルバーにこの名前が表示されます
		WS_OVERLAPPEDWINDOW,	//ウィンドウの種類
		10,						//Ｘ座標　適宜指定する
		10,						//Ｙ座標　適宜指定する
		W_WIDTH,					//幅	　適宜指定する
		W_HEIGHT,					//高さ	　適宜指定する
		NULL,					//親ウィンドウのハンドル、親を作るときはNULL
		NULL,					//メニューハンドル、クラスメニューを使うときはNULL
		hInst,					//インスタンスハンドル
		NULL);

	if (!hWnd) {
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	RECT		rc;
	static int 	x = img_start_x;
	static int 	y = img_start_y;
	static int dx = 2;
	static int dy = 2;
	HDC hDC;
	HBRUSH  hBrush;
	static HWND		hChdWnd;
	HINSTANCE		hInst;
	PAINTSTRUCT ps;

	switch (message) {
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);		// GDI関数による描画を開始する

		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//黒色のストックブラシを取得
		SelectObject(hDC, hBrush);			//取得したブラシを使用
		RoundRect(hDC, 10, 10, 643, 322, 70, 80); //iPhone7の外枠

		hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);	//灰色のストックブラシを取得
		SelectObject(hDC, hBrush);	//取得したブラシを使用
		Ellipse(hDC, 579, 139, 633, 193); //ボタンの外丸

		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//黒色のストックブラシを取得
		SelectObject(hDC, hBrush);	//取得したブラシを使用
		Ellipse(hDC, 584, 144, 628, 188); //ボタンの内丸

		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);	//白色のストックブラシを取得
		SelectObject(hDC, hBrush);	//取得したブラシを使用
		Ellipse(hDC, 25, 162, 33, 170);  //中央上部の丸
		Ellipse(hDC, 35, 221, 50, 236); //中央上部下の丸
		RoundRect(hDC, 39, 129, 46, 207, 80, 10);//前面側マイク

		hBrush = CreateSolidBrush(RGB(255, 255, 0));		// 黄色い論理ブラシを作成する
		SelectObject(hDC, hBrush);	// 作成した論理ブラシを使用する
		Rectangle(hDC, 83, 29, 571, 303); //iPhone7の画面サイズ
		DeleteObject(hBrush); //作成した論理ブラシを削除する

		EndPaint(hWnd, &ps); 	// GDI関数による描画を終了する
	}

	switch (message) {
	case WM_CREATE:
		hInst = ((LPCREATESTRUCT)lParam)->hInstance;
		InitApp(hInst, ChdProc1, szchClassName);
		hChdWnd = CreateWindow(
			szchClassName,		// ウィンドウクラス名
			NULL,				// タイトルバーに表示する文字列
			WS_CHILD,			// ウィンドウの種類
			0,					// ウィンドウを表示する位置(X座標）
			0,					// ウィンドウを表示する位置(Y座標）
			CHD_WIDTH,			// ウィンドウの幅
			CHD_HEIGHT,			// ウィンドウの高さ
			hWnd,				// 親ウィンドウのウィンドウハンドル
			(HMENU)ID_MYCHILD,	// メニューハンドル
			hInst,				// インスタンスハンドル
			NULL				// その他の作成データ
			);

		ShowWindow(hChdWnd, SW_SHOW);
		UpdateWindow(hChdWnd);

		SetTimer(hWnd, ID_MYTIMER, 10, NULL);
		break;

	case WM_TIMER:
		GetClientRect(hWnd, &rc);
		MoveWindow(hChdWnd, x, y, CHD_WIDTH, CHD_HEIGHT, TRUE);

		x += dx;
		y += dy;

		if (x < img_start_x) dx *= -1;
		if (x > img_end_x)	dx *= -1;
		if (y < img_start_y)	dy *= -1;
		if (y> img_end_y)	dy *= -1;

		break;

	case WM_DESTROY:
		KillTimer(hWnd, ID_MYTIMER);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

LRESULT CALLBACK ChdProc1(HWND hChdWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HBITMAP	hBitmap1;
	static HBITMAP	hPrevBitmap;
	HINSTANCE		hInst;
	PAINTSTRUCT	ps;
	HDC			hDC;
	HDC			hCompatDC;

	switch (message) {
	case WM_PAINT:
		hInst = (HINSTANCE)GetWindowLong(hChdWnd, GWL_HINSTANCE);
		hDC = BeginPaint(hChdWnd, &ps);
		hBitmap1 = (HBITMAP)LoadImage(
			hInst,
			_T("icehockey.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE);

		if (hBitmap1 == NULL) {
			MessageBox(
				hChdWnd,
				_T("ビットマップのロードに失敗しました"),
				_T("エラー"),
				MB_OK | MB_ICONWARNING
				);
			return 0;
		}


		hCompatDC = CreateCompatibleDC(hDC);
		SelectObject(hCompatDC, hBitmap1);

		BitBlt(hDC, 0, 0, CHD_WIDTH, CHD_HEIGHT, hCompatDC, 0, 0, SRCCOPY);

		DeleteDC(hCompatDC);
		DeleteObject(hBitmap1);
		EndPaint(hChdWnd, &ps);
		break;

	default:
		return(DefWindowProc(hChdWnd, message, wParam, lParam));
	}
	return 0;
}
