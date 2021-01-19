#include "..\..\Header\Window\Window.h"

using Vector2 = GatesEngine::Math::Vector2;

GatesEngine::Window::Window::Window():hwnd(HWND()),wndClass(WNDCLASSEX()),windowSize(Vector2())
{
}

GatesEngine::Window::Window::~Window()
{
}

HRESULT GatesEngine::Window::Window::Create(const Vector2 & windowSize, const char * title)
{
	return E_NOTIMPL;
}

HWND GatesEngine::Window::Window::GetHandle()
{
	return hwnd;
}

HINSTANCE GatesEngine::Window::Window::GetInstance()
{
	return wndClass.hInstance;
}

Vector2 GatesEngine::Window::Window::GetWindowSize()
{
	return windowSize;
}

float GatesEngine::Window::Window::GetWindowAspect()
{
	return windowSize.y / windowSize.x;
}
