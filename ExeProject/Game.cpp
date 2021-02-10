#include "Game.h"
#include "Scene/SceneManager.h"
#include "SampleScene.h"
#include "..\Header\Math\Easing.h"

Game::Game():Application()
{
}

Game::Game(GatesEngine::Math::Vector2 windowSize, const char * title) :Application(windowSize, title)
{
}

Game::~Game()
{
}

bool Game::LoadContents()
{
	sceneManager->AddScene(new SampleScene("SampleScene"));
	sceneManager->ChangeScene("SampleScene");
	return true;
}

bool Game::Initialize()
{
	timer.SetIsShow(false);
	return true;
}

bool Game::Update()
{
	return true;
}

void Game::Draw()
{
	dx12->SetRenderTarget({ 0,0,0,0 });
	dx12->ScreenFlip();
}
