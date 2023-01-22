#pragma once
#include <Hi_Engine.h>

class Editor : public Hi_Engine::Application
{
public:
	void OnUpdate(float aDeltaTime) override;
	void OnRender() override;
};

Hi_Engine::Application* Hi_Engine::CreateApplication()
{
	return new Editor;
}