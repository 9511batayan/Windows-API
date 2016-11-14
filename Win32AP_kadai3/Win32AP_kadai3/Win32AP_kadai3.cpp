#include <windows.h>
#include <tchar.h>

#define	ID_MYTIMER	(32767)
#define	ID_MYCHILD	(100)
#define WINDOW_WIDTH (310)
#define WINDOW_HEIGHT (600)
#define	CHD_WIDTH	(300)
#define	CHD_HEIGHT	(350)

// プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL InitApp(HINSTANCE, WNDPROC, LPCTSTR);
BOOL InitInstance(HINSTANCE, int, LPCTSTR);

//大域変数
static TCHAR szClassName[] = _T("Win32AP_kadai3");
static TCHAR szchClassName[] = _T("child");
static TCHAR szTitle[] = _T("Discovery");
HINSTANCE	hInst;
RECT		g_windowPos;

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
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;

	return (RegisterClass(&wc));
}


BOOL InitInstance(HINSTANCE hInst, int nCmdShow, LPCTSTR szClassName) {
	HWND hWnd;

	hWnd = CreateWindow(
		szClassName,
		szTitle,						//タイトルバーにこの名前が表示されます
		WS_OVERLAPPEDWINDOW,	//ウィンドウの種類
		CW_USEDEFAULT,			//Ｘ座標　適宜指定する
		CW_USEDEFAULT,			//Ｙ座標　適宜指定する
		CW_USEDEFAULT,			//幅	　適宜指定する
		CW_USEDEFAULT,			//高さ	　適宜指定する
		NULL,						//親ウィンドウのハンドル、親を作るときはNULL
		NULL,			//メニューハンドル、クラスメニューを使うときはNULL
		hInst,			//インスタンスハンドル
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
	static int 	x;
	static int 	y;
	static int dx;
	static int dy;

	
	HINSTANCE		hInst;

	switch (message) {
	case WM_CREATE:
		hInst = ((LPCREATESTRUCT)lParam)->hInstance;
		InitApp(hInst, ChdProc, szchClassName);

		g_windowPos.left = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2;
		g_windowPos.top = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2;
		g_windowPos.right = g_windowPos.left + WINDOW_WIDTH;
		g_windowPos.bottom = g_windowPos.top + WINDOW_HEIGHT;

		HWND hWnd = CreateWindow(
			szchClassName,			// ウィンドウクラス名
			szTitle,					// タイトルバーに表示する文字列
			WS_CHILD,				// ウィンドウの種類
			0,						// ウィンドウを表示する位置(X座標）
			0,						// ウィンドウを表示する位置(Y座標）
			WINDOW_WIDTH,			// ウィンドウの幅
			WINDOW_HEIGHT,			// ウィンドウの高さ
			hWnd,					// 親ウィンドウのウィンドウハンドル
			(HMENU)ID_MYCHILD,	// メニューハンドル
			hInst,					// インスタンスハンドル
			NULL					// その他の作成データ
			);

		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);

		dx = 3;
		dy = 2;

		SetTimer(hWnd, ID_MYTIMER, 10, NULL);
		break;

	case WM_TIMER:
		GetClientRect(hWnd, &rc);
		MoveWindow(hWnd, x, y, CHD_WIDTH, CHD_HEIGHT, TRUE);

			x += dx;
			y += dy;
			if (x < 0)	dx *=-1;
			if (x >=rc.right - CHD_WIDTH){

				dx *= -1;
			}
			if (y < 0)	dy *=-1;
			if (y >= CHD_HEIGHT){

				dy *= -1;
			}


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


LRESULT CALLBACK ChdProc(HWND hChdWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HBITMAP	hBitmap;
	static HBITMAP	hPrevBitmap;
	HINSTANCE		hInst;
	PAINTSTRUCT	ps;
	HDC			hDC;
	HWND		hWnd;
	HDC			hCompatDC;
	HBRUSH hBrush;

	switch (message) {
	case WM_MOVING:
		((RECT*)lParam)->left = g_windowPos.left;
		((RECT*)lParam)->top = g_windowPos.top;
		((RECT*)lParam)->right = g_windowPos.right;
		((RECT*)lParam)->bottom = g_windowPos.bottom;
		break;

	case WM_PAINT:
		hInst = (HINSTANCE)GetWindowLong(hChdWnd, GWL_HINSTANCE);

		hDC = BeginPaint(hWnd, &ps);		// GDI関数による描画を開始する
		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//黒色のストックブラシを取得
		SelectObject(hDC, hBrush);			//取得したブラシを使用
		RoundRect(hDC, 10, 10, 280, 548, 60, 60);	//iphone外側

		hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);	//灰色のストックブラシを取得
		SelectObject(hDC, hBrush);	//取得したブラシを使用
		Ellipse(hDC, 121, 490, 169, 538);	//ホームボタン外周

		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//黒色のストックブラシを取得
		SelectObject(hDC, hBrush);	//取得したブラシを使用
		Ellipse(hDC, 125, 494, 165, 534);	//ホームボタン

		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);	//白色のストックブラシを取得
		SelectObject(hDC, hBrush);	//取得したブラシを使用
		Ellipse(hDC, 141, 19, 149, 27);	//近接&環境光センサ
		Ellipse(hDC, 90, 32, 100, 42);	//前面側カメラ
		RoundRect(hDC, 117, 35, 177, 40, 8, 8);//前面側マイク

		hBrush = CreateSolidBrush(RGB(255, 255, 0));		// 黄色の論理ブラシを作成する
		SelectObject(hDC, hBrush);	// 作成した論理ブラシを使用する
		Rectangle(hDC, 20, 70, 270, 480);	//画面
		DeleteObject(hBrush);	//作成した論理ブラシを削除する

		hBitmap = (HBITMAP)LoadImage(
			hInst,
			_T("Discovery.bmp"),
			IMAGE_BITMAP,
			50,
			100,
			LR_LOADFROMFILE);

		if (hBitmap == NULL) {
			MessageBox(
				hWnd,
				_T("ビットマップのロードに失敗しました"),
				_T("エラー"),
				MB_OK | MB_ICONWARNING
				);
			return 0;
		}

	
		hCompatDC = CreateCompatibleDC(hDC);
		SelectObject(hCompatDC, hBitmap);

		BitBlt(hDC, 0, 0, CHD_WIDTH, CHD_HEIGHT, hCompatDC, 0, 0, SRCCOPY);

		DeleteDC(hCompatDC);
		DeleteObject(hBitmap);
		EndPaint(hChdWnd, &ps);
		break;

	default:
		return(DefWindowProc(hChdWnd, message, wParam, lParam));
	}
	return 0;
}
