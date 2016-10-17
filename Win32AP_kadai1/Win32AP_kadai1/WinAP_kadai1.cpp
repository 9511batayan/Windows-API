#include <windows.h>
#include <tchar.h>

#define WINDOW_WIDTH		(310)
#define WINDOW_HEIGHT		(600)

// プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// 大域変数
static TCHAR szWindowClass[] = _T("Win32AP_kadai1");
static TCHAR szTitle[] = _T("Win32AP_kadai1");
HINSTANCE	hInst;
RECT		g_windowPos;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pCmdLine,
	int nCmdShow) {

	WNDCLASSEX wcex;

	// ウィンドウクラスの情報を設定
	wcex.cbSize = sizeof(WNDCLASSEX);				// 構造体サイズ
	wcex.style = CS_HREDRAW | CS_VREDRAW;		// スタイル
	wcex.lpfnWndProc = WndProc;							// ウィンドウプロシージャ
	wcex.cbClsExtra = 0;									// 拡張情報１
	wcex.cbWndExtra = 0;									// 拡張情報２
	wcex.hInstance = hInstance;							// インスタンスハンドル
	wcex.hIcon = (HICON)LoadImage(					// アイコン
		NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED
		);
	wcex.hIconSm = wcex.hIcon;							// 子アイコン
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;						// メニュー名
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	// ウィンドウクラスを登録する
	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			_T("ウィンドウの登録に失敗しました"),
			_T("ウィンドウの登録エラー"),
			NULL);
		return 1;
	}

	hInst = hInstance; // インスタンス･ハンドルを大域変数に格納

	g_windowPos.left = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2;
	g_windowPos.top = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2;
	g_windowPos.right = g_windowPos.left + WINDOW_WIDTH;
	g_windowPos.bottom = g_windowPos.top + WINDOW_HEIGHT;

	// ウィンドウを作成する
	HWND hWnd = CreateWindow(
		szWindowClass,					// ウィンドウクラス名
		szTitle,							// タイトルバーに表示する文字列
		WS_OVERLAPPEDWINDOW,		// ウィンドウの種類
		g_windowPos.left,					// ウィンドウを表示する位置(X座標）
		g_windowPos.top,					// ウィンドウを表示する位置(Y座標）
		WINDOW_WIDTH,				// ウィンドウの幅
		WINDOW_HEIGHT,				// ウィンドウの高さ
		NULL,							// 親ウィンドウのウィンドウハンドル
		NULL,							// メニューハンドル
		hInst,							// インスタンスハンドル
		NULL							// その他の作成データ
		);

	if (!hWnd) {
		MessageBox(NULL,
			_T("ウィンドウの作成に失敗しました"),
			_T("ウィンドウの作成エラー"),
			NULL);
		return 1;
	}

	// ウィンドウを表示する
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	HBRUSH hBrush;
	PAINTSTRUCT ps;

	switch (message) {
	case WM_MOVING:
		((RECT*)lParam)->left = g_windowPos.left;
		((RECT*)lParam)->top = g_windowPos.top;
		((RECT*)lParam)->right = g_windowPos.right;
		((RECT*)lParam)->bottom = g_windowPos.bottom;
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);		// GDI関数による描画を開始する
		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//黒色のストックブラシを取得
		SelectObject(hDC, hBrush);			//取得したブラシを使用
		RoundRect(hDC, 10, 10, 280, 548, 60,60);	//iphone外側

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

		hBrush = CreateSolidBrush(RGB(255, 255, 0));		// 青い論理ブラシを作成する
		SelectObject(hDC, hBrush);	// 作成した論理ブラシを使用する
		Rectangle(hDC, 20, 70, 270, 480);	//画面
		DeleteObject(hBrush);	//作成した論理ブラシを削除する

		EndPaint(hWnd, &ps);				// GDI関数による描画を終了する
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}
