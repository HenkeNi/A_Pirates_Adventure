#pragma once
#include "Core/Engine.h"


int main()
{
	auto* engine = new Hi_Engine::Engine;
	
	if (!engine->Init())
		return -1;

	while (engine->IsRunning())
	{
		engine->ProcessInput();
		engine->Update();
		engine->LateUpdate();
		engine->Draw();
	}

	engine->Shutdown();
	delete engine;

	return 0;
}