#include <windows.h>
#include <tchar.h>

#define	ID_MYTIMER	(32767)
#define	ID_MYCHILD	(100)
#define WINDOW_WIDTH (310)
#define WINDOW_HEIGHT (600)
#define	CHD_WIDTH	(300)
#define	CHD_HEIGHT	(350)

// �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL InitApp(HINSTANCE, WNDPROC, LPCTSTR);
BOOL InitInstance(HINSTANCE, int, LPCTSTR);

//���ϐ�
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
		szTitle,						//�^�C�g���o�[�ɂ��̖��O���\������܂�
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�̎��
		CW_USEDEFAULT,			//�w���W�@�K�X�w�肷��
		CW_USEDEFAULT,			//�x���W�@�K�X�w�肷��
		CW_USEDEFAULT,			//��	�@�K�X�w�肷��
		CW_USEDEFAULT,			//����	�@�K�X�w�肷��
		NULL,						//�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
		NULL,			//���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
		hInst,			//�C���X�^���X�n���h��
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
			szchClassName,			// �E�B���h�E�N���X��
			szTitle,					// �^�C�g���o�[�ɕ\�����镶����
			WS_CHILD,				// �E�B���h�E�̎��
			0,						// �E�B���h�E��\������ʒu(X���W�j
			0,						// �E�B���h�E��\������ʒu(Y���W�j
			WINDOW_WIDTH,			// �E�B���h�E�̕�
			WINDOW_HEIGHT,			// �E�B���h�E�̍���
			hWnd,					// �e�E�B���h�E�̃E�B���h�E�n���h��
			(HMENU)ID_MYCHILD,	// ���j���[�n���h��
			hInst,					// �C���X�^���X�n���h��
			NULL					// ���̑��̍쐬�f�[�^
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

		hDC = BeginPaint(hWnd, &ps);		// GDI�֐��ɂ��`����J�n����
		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//���F�̃X�g�b�N�u���V���擾
		SelectObject(hDC, hBrush);			//�擾�����u���V���g�p
		RoundRect(hDC, 10, 10, 280, 548, 60, 60);	//iphone�O��

		hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);	//�D�F�̃X�g�b�N�u���V���擾
		SelectObject(hDC, hBrush);	//�擾�����u���V���g�p
		Ellipse(hDC, 121, 490, 169, 538);	//�z�[���{�^���O��

		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//���F�̃X�g�b�N�u���V���擾
		SelectObject(hDC, hBrush);	//�擾�����u���V���g�p
		Ellipse(hDC, 125, 494, 165, 534);	//�z�[���{�^��

		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);	//���F�̃X�g�b�N�u���V���擾
		SelectObject(hDC, hBrush);	//�擾�����u���V���g�p
		Ellipse(hDC, 141, 19, 149, 27);	//�ߐ�&�����Z���T
		Ellipse(hDC, 90, 32, 100, 42);	//�O�ʑ��J����
		RoundRect(hDC, 117, 35, 177, 40, 8, 8);//�O�ʑ��}�C�N

		hBrush = CreateSolidBrush(RGB(255, 255, 0));		// ���F�̘_���u���V���쐬����
		SelectObject(hDC, hBrush);	// �쐬�����_���u���V���g�p����
		Rectangle(hDC, 20, 70, 270, 480);	//���
		DeleteObject(hBrush);	//�쐬�����_���u���V���폜����

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
				_T("�r�b�g�}�b�v�̃��[�h�Ɏ��s���܂���"),
				_T("�G���["),
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
