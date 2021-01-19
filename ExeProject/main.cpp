#include "Math/GatesMath.h"
#include "Window/Window.h"
#include <stdio.h>

#ifdef _DEBUG
#include <crtdbg.h>
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif
	using Vector2 = GatesEngine::Math::Vector2;
	using Window = GatesEngine::Window::Window;

	Window window;
	window.Create(Vector2(1280,720), "title");
	window.PreviewWindow();

	printf("%f\n", window.GetWindowAspect());
	printf("%f\n", window.GetWindowSize().x);
	printf("%f\n", window.GetWindowSize().y);

	while (true)
	{
		if (!window.ProcessMessage()) break;
	}
	return 0;
}