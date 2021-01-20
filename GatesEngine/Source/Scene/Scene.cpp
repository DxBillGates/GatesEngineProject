#include "..\..\Header\Scene\Scene.h"

GatesEngine::Scene::Scene() :sceneName("scene"), changeNextSceneFlag(false)
{
}

GatesEngine::Scene::Scene(const char * sceneName):sceneName(sceneName),changeNextSceneFlag(false)
{
}

GatesEngine::Scene::~Scene()
{
}

const char * GatesEngine::Scene::GetSceneName()
{
	return sceneName;
}

bool GatesEngine::Scene::IsChangeScene()
{
	return changeNextSceneFlag;
}
