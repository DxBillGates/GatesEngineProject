#pragma once
#include "..\Input\Input.h"
#include "..\Window\Window.h"
namespace GatesEngine
{
	class Application
	{
		using Vector2 = GatesEngine::Math::Vector2;
	protected:
		Input* input;
		Window window;
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