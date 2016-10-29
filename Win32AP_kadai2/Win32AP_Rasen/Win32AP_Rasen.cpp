#define _USE_MATH_DEFINES
#include <windows.h>
#include <tchar.h>
#include <math.h>

// プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// 大域変数
static TCHAR szWindowClass[] = _T("Win32AP_Rasen");
static TCHAR szTitle[] = _T("Win32AP_Rasen");
HINSTANCE	hInst;

int window_pos_x = 100;
int window_pos_y = 100;
int window_width = 350;
int window_height = 690;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pCmdLine,
	int nCmdShow) {

	WNDCLASSEX wcex;

	// ウィンドウクラスの情報を設定
	wcex.cbSize = sizeof(WNDCLASSEX);				// 構造体サイズ
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// スタイル
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
	wcex.lpszMenuName = NULL;							// メニュー名
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

	// ウィンドウを作成する
	HWND hWnd = CreateWindow(
		szWindowClass,					// ウィンドウクラス名
		szTitle,							// タイトルバーに表示する文字列
		WS_OVERLAPPEDWINDOW,		// ウィンドウの種類
		window_pos_x,								// ウィンドウを表示する位置(X座標)
		window_pos_y,								// ウィンドウを表示する位置(Y座標)
		window_width,								// ウィンドウの幅
		window_height,								// ウィンドウの高さ
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

	// メッセージ･ループ
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
	HBRUSH  hBrushBlack;
	HBRUSH  hBrushYellow;
	HBRUSH  hBrushWhite;
	PAINTSTRUCT ps;
	LPCTSTR STR1 = _T("i");
	LPCTSTR STR2 = _T("n");
	LPCTSTR STR3 = _T("f");
	LPCTSTR STR4 = _T("t");
	LPCTSTR STR5 = _T("y");
	static LOGFONT logfont;  //フォント情報の構造体
	HFONT hFont;
	int angle = 1;

	switch (message) {
	case WM_CREATE:
		ZeroMemory(&logfont, sizeof(logfont));	// フォント情報構造体を０で初期化
		logfont.lfCharSet = DEFAULT_CHARSET;	// システムのデフォルト文字セットを使う
		wsprintf(logfont.lfFaceName, _T("Times New Roman"));
		break;

	case WM_PAINT:{

					  hDC = BeginPaint(hWnd, &ps);		// GDI関数による描画を開始する

					  hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
					  SelectObject(hDC, hBrushBlack);
					  RoundRect(hDC, 10, 10, 322, 643, 70, 80);    //iPhone7の外枠
					  Rectangle(hDC, 7, 85, 20, 110);               //マナーモードON/OFFキー
					  Rectangle(hDC, 7, 135, 20, 185);               //音量＋ボタン
					  Rectangle(hDC, 7, 200, 20, 250);               //音量－ボタン
					  Rectangle(hDC, 321, 120, 325, 170);               //電源ボタン

					  hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
					  SelectObject(hDC, hBrushWhite);
					  Ellipse(hDC, 162, 25, 170, 33);              //中央上部の丸
					  Ellipse(hDC, 100, 35, 115, 50);              //中央上部下の丸
					  RoundRect(hDC, 129, 39, 207, 46, 10, 80);
					  Ellipse(hDC, 139, 579, 193, 633);            //ボタンの外丸

					  hBrushYellow = CreateSolidBrush(RGB(255, 255, 0));
					  SelectObject(hDC, hBrushYellow);
					  Rectangle(hDC, 29, 83, 303, 569);            //iPhone7の画面サイズ

					  //****  螺旋を描く ****
					  double x0 = 170;
					  double y0 = 310;
					  double x1, y1;
					  double a1 = 1.08;

					  int i = 1;
					  int n = 0;
					  MoveToEx(hDC, x0, y0, NULL);     //開始点に移動
					  for (double theta = 38; theta < 90; theta += 0.11){
						  while (angle >= 0){
							  hFont = CreateFontIndirect(&logfont);
							  SelectObject(hDC, hFont);

							  logfont.lfHeight = theta - 30;   //文字の大きさを指定

							  x1 = pow(a1, theta)*cos(theta) + x0;       //x座標を設定
							  y1 = pow(a1, theta)*sin(theta) + y0;       //y座標を設定

							  //**** 2点から角度を求める ****
							  double dx = x0 - x1;
							  double dy = y0 - y1;
							  double radian = atan2(dx, dy);
							  radian = radian*(180 / M_PI) * 10;

							  logfont.lfEscapement = radian;     //文字に傾きを付ける

							  //***** 最初に描かれる余分な「i」の消去  ****
							  if (n == 0){
								  n = 1;
								  break;
							  }

							  if ((x1 >= 10 && x1 <= 310) && (y1 >= 83 && y1 <= 569)){  //枠内のみ螺旋を描く
								  SetBkMode(hDC, TRANSPARENT);      //テキストの背景を透明にする
								  while (i < 9){
									  switch (i){
									  case 1:
									  case 4:
									  case 6:
										  TextOut(hDC, x1, y1, STR1, _tcslen(STR1));
										  break;
									  case 2:
									  case 5:
										  TextOut(hDC, x1, y1, STR2, _tcslen(STR2));
										  break;
									  case 3:
										  TextOut(hDC, x1, y1, STR3, _tcslen(STR3));
										  break;
									  case 7:
										  TextOut(hDC, x1, y1, STR4, _tcslen(STR4));
										  break;
									  case 8:
										  TextOut(hDC, x1, y1, STR5, _tcslen(STR5));
										  i = 0;
										  break;

									  }
									  i++;
									  break;

								  }

								  DeleteObject(hFont); 					// 作成した論理フォントを削除する
							  }
							  break;
						  }
					  }

					  SelectObject(hDC, hBrushBlack);
					  Ellipse(hDC, 144, 584, 188, 628);            //ボタンの内丸

					  EndPaint(hWnd, &ps);				// GDI関数による描画を終了する
	}break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}
