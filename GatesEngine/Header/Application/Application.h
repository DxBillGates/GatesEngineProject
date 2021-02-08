#pragma once
#include "..\Input\Input.h"
#include "..\Window\Window.h"
#include "..\Scene\SceneManager.h"
namespace GatesEngine
{
	//アプリケーションの基底クラス
	//こいつを継承してExeProjectで使用する
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