#include "Math/GatesMath.h"
#include "Window/Window.h"
#include "Input/Input.h"
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
	using namespace GatesEngine::Math;
	using namespace GatesEngine;

	Window window;
	window.Create(Vector2(1280, 720), "title");
	window.PreviewWindow();

	Input* input = Input::GetInstance();
	input->Create(window.GetHandle(), window.GetInstance());
	input->Initialize();


	while (true)
	{
		input->Update();

		if (!window.ProcessMessage()) break;
		if (input->GetKeyboard()->CheckHitKey(Keys::ESC))break;
	}
	return 0;
}