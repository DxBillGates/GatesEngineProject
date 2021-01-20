#pragma once
#include "Application/Application.h"
class Game : public GatesEngine::Application
{
private:
public:
	Game();
	~Game();
	bool LoadContents() override;
	bool Initialize() override;
	bool Update() override;
	void Draw() override;
};

