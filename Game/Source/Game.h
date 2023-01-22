#pragma once
#include <Hi_Engine.h>


class Game : public Hi_Engine::Application
{
public:
	void OnUpdate(float aDeltaTime)		override;
	void OnRender()		override;

private:
	void SetupScenes();

};

Hi_Engine::Application* Hi_Engine::CreateApplication()
{
	return new Game;
}