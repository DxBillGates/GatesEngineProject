#include "..\..\Header\Window\Window.h"

using Vector2 = GatesEngine::Math::Vector2;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

GatesEngine::Window::Window() :hwnd(HWND()), wndClass(WNDCLASSEX()), msg(MSG()), windowSize(Vector2())
{
}

GatesEngine::Window::~Window()
{
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
}

bool GatesEngine::Window::Create(const Vector2 & windowSize, const char * title)
{
	// ウィンドウの設定
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = (WNDPROC)WinProc;
	wndClass.lpszClassName = title;
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	// Windowの登録
	RegisterClassEx(&wndClass);

	// Windowの生成
	RECT rect = { 0,0,(LONG)windowSize.x,(LONG)windowSize.y };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	hwnd = CreateWindow(wndClass.lpszClassName,
		wndClass.lpszClassName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr,
		nullptr,
		wndClass.hInstance,
		nullptr);

	this->windowSize = windowSize;

	if (hwnd == NULL)return false;
	return true;
}

void GatesEngine::Window::PreviewWindow()
{
	ShowWindow(hwnd, SW_SHOW);
}

bool GatesEngine::Window::Window::ProcessMessage()
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msg.message == WM_QUIT)
	{
		return false;
	}
	return true;
}

HWND GatesEngine::Window::GetHandle()
{
	return hwnd;
}

HINSTANCE GatesEngine::Window::GetInstance()
{
	return wndClass.hInstance;
}

Vector2 GatesEngine::Window::GetWindowSize()
{
	return windowSize;
}

float GatesEngine::Window::GetWindowAspect()
{
	return windowSize.x / windowSize.y;
}

void GatesEngine::Window::SetWindowTitle(const char * changeTitle)
{
	SetWindowText(hwnd, changeTitle);
}