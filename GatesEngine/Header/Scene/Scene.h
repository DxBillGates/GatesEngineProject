#pragma once

namespace GatesEngine
{
	class Application;
	class Scene
	{
	protected:
		const char* sceneName;
		bool changeNextSceneFlag;
	public:
		Scene();
		Scene(const char* sceneName);
		Scene(const char* sceneName, Application* app);
		virtual ~Scene();
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		const char* GetSceneName();
		bool IsChangeScene();
	};
}
