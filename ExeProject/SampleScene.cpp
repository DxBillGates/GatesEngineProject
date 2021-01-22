#include "SampleScene.h"
#include <stdio.h>

SampleScene::SampleScene():Scene()
{
}

SampleScene::SampleScene(const char * sceneName):Scene(sceneName)
{
}

SampleScene::~SampleScene()
{
}

void SampleScene::Initialize()
{
	printf("%c\n", sceneName);
}

void SampleScene::Update()
{
}

void SampleScene::Draw()
{
}
