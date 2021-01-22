#include "..\..\Header\Application\Application.h"
#include "..\..\Header\Scene\SceneManager.h"

GatesEngine::Application::Application():window(Window()),input(Input::GetInstance()),sceneManager(SceneManager::GetInstance())
{
	window.Create(Vector2(1280,720), "test");
	window.PreviewWindow();
	input->Create(window.GetHandle(), window.GetInstance());
}

GatesEngine::Application::~Application()
{
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
		input->Update();
		if(!Update())break;
		sceneManager->Update();
		Draw();
		sceneManager->Draw();
		if(!window.ProcessMessage())break;
	}
}
