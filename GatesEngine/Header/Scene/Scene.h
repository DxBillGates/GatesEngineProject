#pragma once

namespace GatesEngine
{
	class Scene
	{
	private:
		const char* sceneName;
		bool changeNextSceneFlag;
	public:
		Scene();
		Scene(const char* sceneName);
		virtual ~Scene();
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		const char* GetSceneName();
		bool IsChangeScene();
	};
}
