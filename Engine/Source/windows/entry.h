#pragma once

#define NOMINMAX
#undef NOGDI
#include <Windows.h>
#include <Windowsx.h>
#define NOGDI

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HINSTANCE hInstance;
HDC hDc;
HWND hWnd;

static PIXELFORMATDESCRIPTOR GetPixelFormat()
{
	PIXELFORMATDESCRIPTOR result = {};
	result.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	result.nVersion = 1;
	result.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	result.iPixelType = PFD_TYPE_RGBA;
	result.cColorBits = 32;
	result.cDepthBits = 24;
	result.cStencilBits = 8;
	result.cAuxBuffers = 0;
	result.iLayerType = PFD_MAIN_PLANE;
	return result;
}

static PIXELFORMATDESCRIPTOR GetPixelFormat()
{
	PIXELFORMATDESCRIPTOR result = {};
	result.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	result.nVersion = 1;
	result.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	result.iPixelType = PFD_TYPE_RGBA;
	result.cColorBits = 32;
	result.cDepthBits = 24;
	result.cStencilBits = 8;
	result.cAuxBuffers = 0;
	result.iLayerType = PFD_MAIN_PLANE;
	return result;
}

bool PlatformInit()
{
	hInstance = (HINSTANCE)&__ImageBase;

	WNDCLASS winClass = {};
	winClass.hInstance = hInstance; // GetModuleHandle(0);
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc = (WNDPROC)WndProc;
	winClass.lpszClassName = "Sparky Win32 Window";
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassA(&winClass))
	{
		// TODO: Handle error
		SP_ERROR("Could not register Win32 class!");
		return false;
	}

	RECT size = { 0, 0, (LONG)m_Properties.width, (LONG)m_Properties.height };
	AdjustWindowRectEx(&size, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, false, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	hWnd = CreateWindowExA(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		winClass.lpszClassName, m_Title.c_str(),
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		GetSystemMetrics(SM_CXSCREEN) / 2 - m_Properties.width / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - m_Properties.height / 2,
		// TODO: This requires some... attention
		size.right + (-size.left), size.bottom + (-size.top), NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		SP_ERROR("Could not create window!");
		return false;
	}

	RegisterWindowClass(hWnd, this);

	hDc = GetDC(hWnd);
	PIXELFORMATDESCRIPTOR pfd = GetPixelFormat();
	int32 pixelFormat = ChoosePixelFormat(hDc, &pfd);
	if (pixelFormat)
	{
		if (!SetPixelFormat(hDc, pixelFormat, &pfd))
		{
			SP_ERROR("Failed setting pixel format!");
			return false;
		}
	}
	else
	{
		SP_ERROR("Failed choosing pixel format!");
		return false;
	}

	graphics::API::Context::Create(m_Properties, hWnd);

	ShowWindow(hWnd, SW_SHOW);
	SetFocus(hWnd);
	// resize

	return true;
}
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable  

					   // The parameters to CreateWindow explained:  
					   // szWindowClass: the name of the application  
					   // szTitle: the text that appears in the title bar  
					   // WS_OVERLAPPEDWINDOW: the type of window to create  
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
					   // 500, 100: initial size (width, length)  
					   // NULL: the parent of this window  
					   // NULL: this application dows not have a menu bar  
					   // hInstance: the first parameter from WinMain  
					   // NULL: not used in this application  
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
