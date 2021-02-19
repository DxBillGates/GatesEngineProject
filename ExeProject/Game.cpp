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
	sceneManager->AddScene(new SampleScene("SampleScene",this));
	sceneManager->ChangeScene("SampleScene");
	GatesEngine::Audio::SetAudioEngine();
	audioManager.Add(new GatesEngine::Audio(new GatesEngine::AudioData("Resources/Music/test.wav"),"testBgm"));
	audioManager.Use("testBgm")->Start();
	return true;
}

bool Game::Initialize()
{
	timer.SetIsShow(false);
	return true;
}

bool Game::Update()
{
	sceneManager->Update();
	return true;
}

void Game::Draw()
{
	dx12->SetRenderTarget({ 0,0,0,0 });
	sceneManager->Draw();
	dx12->ScreenFlip();
}
