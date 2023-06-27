#include "pch.h"

	WCHAR		WindowClass[MAX_NAME_STRING];
	WCHAR		WindowTitle[MAX_NAME_STRING];
	INT			WindowWidth;
	INT			WindowHeight;

//CALLBACK = allow to change logic of function
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

	}
	return DefWindowProc(hWnd, message, wparam, lparam);
}

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

	wcex.lpfnWndProc = WindowProcess;
	
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