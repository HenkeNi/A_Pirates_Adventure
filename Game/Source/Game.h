#pragma once
#include <../Application/Application.h>

class Game : public Hi_Engine::Application
{
public:
	Game();
	~Game();

	void OnUpdate(float deltaTime) override;

	void OnCreated() override;
	void OnDestroyed() override;

private:
	void LoadResources();
};