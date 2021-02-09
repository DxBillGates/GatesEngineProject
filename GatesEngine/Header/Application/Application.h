#pragma once
#include "..\Input\Input.h"
#include "..\Window\Window.h"
#include "..\Scene\SceneManager.h"
#include "..\DirectX\Dx12Wrapper.h"
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
		MyDirectX::Dx12Wrapper* dx12;
	public:
		Application();
		Application(Vector2 windowSize, const char* title);
		virtual ~Application();
		virtual bool LoadContents();
		virtual bool Initialize();
		virtual bool Update();
		virtual void Draw();
		virtual void Run();
	};
}