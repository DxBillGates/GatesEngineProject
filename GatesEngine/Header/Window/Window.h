#pragma once
#include "..\Math\Vector2.h"
#include <Windows.h>

namespace GatesEngine
{
	class Window
	{
		using Vector2 = GatesEngine::Math::Vector2;
	private:
		HWND hwnd;
		WNDCLASSEX wndClass;
		MSG msg;
		Vector2 windowSize;
	public:
		Window();
		~Window();
		bool Create(const Vector2& windowSize, const char* title);
		void PreviewWindow();
		bool ProcessMessage();

		HWND GetHandle();
		HINSTANCE GetInstance();
		Vector2 GetWindowSize();
		float GetWindowAspect();
	};
}
