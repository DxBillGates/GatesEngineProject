#include "..\..\Header\Scene\Scene.h"
#include <stdio.h>

GatesEngine::Scene::Scene() :sceneName("scene"), changeNextSceneFlag(false)
{
#ifdef _DEBUG
	printf("名無しのScene生成\n");
#endif 
}

GatesEngine::Scene::Scene(const char * sceneName):sceneName(sceneName),changeNextSceneFlag(false)
{
#ifdef _DEBUG
	printf("%s生成\n", sceneName);
#endif 
}

GatesEngine::Scene::Scene(const char * sceneName,Application* app) :sceneName(sceneName), changeNextSceneFlag(false)
{
#ifdef _DEBUG
	printf("%s生成\n", sceneName);
#endif 
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
