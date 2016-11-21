#include <windows.h>
#include <tchar.h>

#define	ID_MYTIMER	(32767)
#define	ID_MYCHILD	(100)
#define W_WIDTH (700)	//�E�B���h�E�T�C�Y��
#define W_HEIGHT (400)	//�E�B���h�E�T�C�Y����
#define	CHD_WIDTH	(100)
#define	CHD_HEIGHT	(57)

// �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChdProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL InitApp(HINSTANCE, WNDPROC, LPCTSTR);
BOOL InitInstance(HINSTANCE, int, LPCTSTR);

static TCHAR szClassName[] = _T("Win32AP_kadai3");
static TCHAR szchClassName[] = _T("child");
static TCHAR szTitle[] = _T("icehockey_reflect");

int img_start_x = 83;		//�X�^�[�g�n�_��x���W
int img_start_y = 29;		//�X�^�[�g�n�_��y���W
int img_end_x = 482;		//�E�[�n�_��x���W
int img_end_y = 245; //���n�_�ł�y���W

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
		szTitle,				//�^�C�g���o�[�ɂ��̖��O���\������܂�
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�̎��
		10,						//�w���W�@�K�X�w�肷��
		10,						//�x���W�@�K�X�w�肷��
		W_WIDTH,					//��	�@�K�X�w�肷��
		W_HEIGHT,					//����	�@�K�X�w�肷��
		NULL,					//�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
		NULL,					//���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
		hInst,					//�C���X�^���X�n���h��
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
		hDC = BeginPaint(hWnd, &ps);		// GDI�֐��ɂ��`����J�n����

		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//���F�̃X�g�b�N�u���V���擾
		SelectObject(hDC, hBrush);			//�擾�����u���V���g�p
		RoundRect(hDC, 10, 10, 643, 322, 70, 80); //iPhone7�̊O�g

		hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);	//�D�F�̃X�g�b�N�u���V���擾
		SelectObject(hDC, hBrush);	//�擾�����u���V���g�p
		Ellipse(hDC, 579, 139, 633, 193); //�{�^���̊O��

		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//���F�̃X�g�b�N�u���V���擾
		SelectObject(hDC, hBrush);	//�擾�����u���V���g�p
		Ellipse(hDC, 584, 144, 628, 188); //�{�^���̓���

		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);	//���F�̃X�g�b�N�u���V���擾
		SelectObject(hDC, hBrush);	//�擾�����u���V���g�p
		Ellipse(hDC, 25, 162, 33, 170);  //�����㕔�̊�
		Ellipse(hDC, 35, 221, 50, 236); //�����㕔���̊�
		RoundRect(hDC, 39, 129, 46, 207, 80, 10);//�O�ʑ��}�C�N

		hBrush = CreateSolidBrush(RGB(255, 255, 0));		// ���F���_���u���V���쐬����
		SelectObject(hDC, hBrush);	// �쐬�����_���u���V���g�p����
		Rectangle(hDC, 83, 29, 571, 303); //iPhone7�̉�ʃT�C�Y
		DeleteObject(hBrush); //�쐬�����_���u���V���폜����

		EndPaint(hWnd, &ps); 	// GDI�֐��ɂ��`����I������
	}

	switch (message) {
	case WM_CREATE:
		hInst = ((LPCREATESTRUCT)lParam)->hInstance;
		InitApp(hInst, ChdProc1, szchClassName);
		hChdWnd = CreateWindow(
			szchClassName,		// �E�B���h�E�N���X��
			NULL,				// �^�C�g���o�[�ɕ\�����镶����
			WS_CHILD,			// �E�B���h�E�̎��
			0,					// �E�B���h�E��\������ʒu(X���W�j
			0,					// �E�B���h�E��\������ʒu(Y���W�j
			CHD_WIDTH,			// �E�B���h�E�̕�
			CHD_HEIGHT,			// �E�B���h�E�̍���
			hWnd,				// �e�E�B���h�E�̃E�B���h�E�n���h��
			(HMENU)ID_MYCHILD,	// ���j���[�n���h��
			hInst,				// �C���X�^���X�n���h��
			NULL				// ���̑��̍쐬�f�[�^
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
				_T("�r�b�g�}�b�v�̃��[�h�Ɏ��s���܂���"),
				_T("�G���["),
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
