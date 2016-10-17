#include <windows.h>
#include <tchar.h>

#define WINDOW_WIDTH		(310)
#define WINDOW_HEIGHT		(600)

// �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// ���ϐ�
static TCHAR szWindowClass[] = _T("Win32AP_kadai1");
static TCHAR szTitle[] = _T("Win32AP_kadai1");
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

	switch (message) {
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
		RoundRect(hDC, 10, 10, 280, 548, 60,60);	//iphone�O��

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

		EndPaint(hWnd, &ps);				// GDI�֐��ɂ��`����I������
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
