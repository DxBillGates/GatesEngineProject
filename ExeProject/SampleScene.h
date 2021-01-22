#pragma once
#include "Scene/Scene.h"
class SampleScene : public GatesEngine::Scene
{
private:
public:
	SampleScene();
	SampleScene(const char* sceneName);
	~SampleScene();
	void Initialize();
	void Update();
	void Draw();
};

