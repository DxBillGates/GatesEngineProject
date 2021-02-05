#include "Game.h"
#include "Scene/SceneManager.h"
#include "SampleScene.h"

Game::Game():Application()
{
	sceneManager->AddScene(new SampleScene("SampleScene"));
	sceneManager->ChangeScene("SampleScene");
}

Game::~Game()
{
}

bool Game::LoadContents()
{
	return true;
}

bool Game::Initialize()
{
	return true;
}

bool Game::Update()
{
	return true;
}

void Game::Draw()
{
}
