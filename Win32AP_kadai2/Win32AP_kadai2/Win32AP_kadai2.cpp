#include <windows.h>
#include <tchar.h>
#include <math.h>


#define WINDOW_WIDTH		(310)
#define WINDOW_HEIGHT		(600)
#define PI 3.141592

// �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// ���ϐ�
static TCHAR szWindowClass[] = _T("Win32AP_kadai2");
static TCHAR szTitle[] = _T("Win32AP_kadai2");
HINSTANCE	hInst;
RECT		g_windowPos;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pCmdLine,
	int nCmdShow) {

	WNDCLASSEX wcex;

	// �E�B���h�E�N���X�̏���ݒ�
	wcex.cbSize = sizeof(WNDCLASSEX);				// �\���̃T�C�Y
	wcex.style = CS_HREDRAW | CS_VREDRAW;		// �X�^�C��
	wcex.lpfnWndProc = WndProc;							// �E�B���h�E�v���V�[�W��
	wcex.cbClsExtra = 0;									// �g�����P
	wcex.cbWndExtra = 0;									// �g�����Q
	wcex.hInstance = hInstance;							// �C���X�^���X�n���h��
	wcex.hIcon = (HICON)LoadImage(					// �A�C�R��
		NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED
		);
	wcex.hIconSm = wcex.hIcon;							// �q�A�C�R��
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;						// ���j���[��
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	// �E�B���h�E�N���X��o�^����
	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			_T("�E�B���h�E�̓o�^�Ɏ��s���܂���"),
			_T("�E�B���h�E�̓o�^�G���["),
			NULL);
		return 1;
	}

	hInst = hInstance; // �C���X�^���X��n���h������ϐ��Ɋi�[

	g_windowPos.left = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2;
	g_windowPos.top = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2;
	g_windowPos.right = g_windowPos.left + WINDOW_WIDTH;
	g_windowPos.bottom = g_windowPos.top + WINDOW_HEIGHT;

	// �E�B���h�E���쐬����
	HWND hWnd = CreateWindow(
		szWindowClass,					// �E�B���h�E�N���X��
		szTitle,							// �^�C�g���o�[�ɕ\�����镶����
		WS_OVERLAPPEDWINDOW,		// �E�B���h�E�̎��
		g_windowPos.left,					// �E�B���h�E��\������ʒu(X���W�j
		g_windowPos.top,					// �E�B���h�E��\������ʒu(Y���W�j
		WINDOW_WIDTH,				// �E�B���h�E�̕�
		WINDOW_HEIGHT,				// �E�B���h�E�̍���
		NULL,							// �e�E�B���h�E�̃E�B���h�E�n���h��
		NULL,							// ���j���[�n���h��
		hInst,							// �C���X�^���X�n���h��
		NULL							// ���̑��̍쐬�f�[�^
		);

	if (!hWnd) {
		MessageBox(NULL,
			_T("�E�B���h�E�̍쐬�Ɏ��s���܂���"),
			_T("�E�B���h�E�̍쐬�G���["),
			NULL);
		return 1;
	}

	// �E�B���h�E��\������
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	HBRUSH hBrush;
	PAINTSTRUCT ps;
	static LOGFONT logfont;
	HFONT hFont;

	static LPCTSTR TEXT = _T("i");
	static LPCTSTR TEXT1 = _T("n");
	static LPCTSTR TEXT2 = _T("f");
	static LPCTSTR TEXT3 = _T("t");
	static LPCTSTR TEXT4 = _T("y");

	double X, Y;	//���W
	double x0 = 170;double y0 = 300;
	double Cx = 135;	//���_x���W
	double Cy = 269;	//���_y���W
	double angle;	//�p�x
	int r = 35;		//�~�̔��a
	int rd = 40;	//���a�̉��Z�n
	int a = 1;
	int i=0;

	switch (message) {
	case WM_CREATE:			// �E�B���h�E���쐬���ꂽ�Ƃ�
		ZeroMemory(&logfont, sizeof(logfont));	// �t�H���g���\���̂��O�ŏ�����
		logfont.lfCharSet = DEFAULT_CHARSET;	// �V�X�e���̃f�t�H���g�����Z�b�g���g��
		//logfont.lfWeight = 700;
		wsprintf(logfont.lfFaceName, _T("Times New Roman"));
		break;


	case WM_MOVING:
		((RECT*)lParam)->left = g_windowPos.left;
		((RECT*)lParam)->top = g_windowPos.top;
		((RECT*)lParam)->right = g_windowPos.right;
		((RECT*)lParam)->bottom = g_windowPos.bottom;
		break;

	case WM_PAINT:
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

		hBrush = CreateSolidBrush(RGB(255, 255, 0));		// ���_���u���V���쐬����
		SelectObject(hDC, hBrush);	// �쐬�����_���u���V���g�p����
		Rectangle(hDC, 20, 70, 270, 480);	//���
		DeleteObject(hBrush);	//�쐬�����_���u���V���폜����

		logfont.lfHeight = 25;		//�t�H���g�T�C�Y�̎w��
		while (i < 3){				//���S�~���3��J��Ԃ�
			for (angle = 0; angle < 350; angle += 30){
				double radian = angle*(PI / 180);	//�p�x�����W�A���ɕϊ�
				X = Cx + (cos(radian)*r); Y = Cy + (sin(radian)*r);

				hFont = CreateFontIndirect(&logfont);
				SelectObject(hDC, hFont);

				//**** 2�_����p�x�����߂� ****
				double dx = x0 - X;
				double dy = y0 - Y;
				double radian1 = atan2(dx, dy);
				radian1 = radian1*(180 / PI) * 10;

				logfont.lfEscapement = radian1; //�����ɌX����t����

				SetBkMode(hDC, TRANSPARENT);	//�w�i�F��ݒ�
				while (a < 9){
					switch (a){
					case 1:
					case 4:
					case 6:
						TextOut(hDC, X, Y, TEXT, _tcslen(TEXT));
						break;
					case 2:
					case 5:
						TextOut(hDC, X, Y, TEXT1, _tcslen(TEXT1));
						break;
					case 3:
						TextOut(hDC, X, Y, TEXT2, _tcslen(TEXT2));
						break;
					case 7:
						TextOut(hDC, X, Y, TEXT3, _tcslen(TEXT3));
						break;
					case 8:
						TextOut(hDC, X, Y, TEXT4, _tcslen(TEXT4));
						a = 0;
						break;
					}
					a++;
					break;
				}
			}
			r += rd;		//���a��傫��������
			logfont.lfHeight += 10;		//�t�H���g�T�C�Y��10���傫���Ȃ�
			i++;
		}


		ReleaseDC(hWnd, hDC);
		EndPaint(hWnd, &ps);	// GDI�֐��ɂ��`����I������
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
