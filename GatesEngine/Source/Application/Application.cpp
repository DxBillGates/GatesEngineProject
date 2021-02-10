#include "..\..\Header\Application\Application.h"
#include "..\..\Header\Scene\SceneManager.h"

GatesEngine::Application::Application():window(Window()),input(Input::GetInstance()),sceneManager(SceneManager::GetInstance()),timer(Util::Timer())
{
	window.Create(Vector2(1280,720), "test");
	window.PreviewWindow();
	dx12 = new GatesEngine::MyDirectX::Dx12Wrapper(window.GetHandle(), 1280, 720);
	input->Create(window.GetHandle(), window.GetInstance());
}

GatesEngine::Application::Application(Vector2 windowSize, const char * title)
	:window(Window()), input(Input::GetInstance()), sceneManager(SceneManager::GetInstance())
{
	window.Create(windowSize, title);
	window.PreviewWindow();
	dx12 = new GatesEngine::MyDirectX::Dx12Wrapper(window.GetHandle(), (int)windowSize.x, (int)windowSize.y);
	input->Create(window.GetHandle(), window.GetInstance());
}

GatesEngine::Application::~Application()
{
	delete dx12;
}

bool GatesEngine::Application::LoadContents()
{
	return true;
}

bool GatesEngine::Application::Initialize()
{
	return true;
}

bool GatesEngine::Application::Update()
{
	return true;
}

void GatesEngine::Application::Draw()
{
}

void GatesEngine::Application::Run()
{
	if(!LoadContents())return;
	if (!Initialize())return;

	input->Initialize();
	sceneManager->Initialize();

	while (!input->GetKeyboard()->CheckHitKey(Keys::ESC))
	{
		if (timer.Wait())continue;
		input->Update();
		if(!Update())break;
		sceneManager->Update();
		Draw();
		sceneManager->Draw();
		if(!window.ProcessMessage())break;
	}
}
