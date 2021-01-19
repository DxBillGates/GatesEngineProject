#pragma once
#include "..\Math\Vector2.h"
#include <Windows.h>

namespace GatesEngine
{
	namespace Window
	{
		class Window
		{
			using Vector2 = GatesEngine::Math::Vector2;
		private:
			HWND hwnd;
			WNDCLASSEX wndClass;
			Vector2 windowSize;
		public:
			Window();
			~Window();
			HRESULT Create(const Vector2& windowSize,const char* title);

			HWND GetHandle();
			HINSTANCE GetInstance();
			Vector2 GetWindowSize();
			float GetWindowAspect();
		};
	}
}
