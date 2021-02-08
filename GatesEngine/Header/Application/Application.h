#pragma once
#include "..\Input\Input.h"
#include "..\Window\Window.h"
#include "..\Scene\SceneManager.h"
namespace GatesEngine
{
	//�A�v���P�[�V�����̊��N���X
	//�������p������ExeProject�Ŏg�p����
	class Application
	{
		using Vector2 = GatesEngine::Math::Vector2;
	protected:
		Input* input;
		Window window;
		SceneManager* sceneManager;
	public:
		Application();
		virtual ~Application();
		virtual bool LoadContents();
		virtual bool Initialize();
		virtual bool Update();
		virtual void Draw();
		virtual void Run();
	};
}