#include <windows.h>

	#define MAX_NAME_STRING 256
	#define HInstance() GetModuleHandle(NULL);

	WCHAR		WindowClass[MAX_NAME_STRING];
	WCHAR		WindowTitle[MAX_NAME_STRING];
	INT			WindowWidth;
	INT			WindowHeight;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	/* - Initialize Global Variables - */

	wcscpy_s(WindowClass, TEXT("Class One"));
	wcscpy_s(WindowTitle, TEXT("DOOM - MaxStyle"));

	WindowWidth = 1366;
	WindowHeight = 768;
	
	/* - Create Window Class - */

	WNDCLASSEX wcex;

	//give the size
	wcex.cbSize = sizeof(WNDCLASSEX);
	//gives horizontal redraw and vertical redraw
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	//give extra memory
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = WindowClass;

	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = DefWindowProc;
	
	RegisterClassEx(&wcex);
	
	/* - Create and Display the Window - */

	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, WindowClass, WindowTitle, WS_EX_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, GetModuleHandleW(0), nullptr);
	
	if (!hWnd) {
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		return 0;
	}


	ShowWindow(hWnd, SW_SHOW);

	/* - Listen for Message events - */

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}