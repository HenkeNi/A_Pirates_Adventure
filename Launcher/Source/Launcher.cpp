#include "Pch.h"
#include "Launcher.h"
#include "Core/Engine.h"
#include "Game.h"

Launcher::Launcher()
{
}

Launcher::~Launcher()
{
}

bool Launcher::UpdatesAvailable()
{
	return false;
}

void Launcher::DownloadUpdatesAsync(std::function<void(bool)> callback)
{
	std::thread downloadThread([=]() {
		
		// bool success = PerformDownloadUpdates();

		// callback(success);
	});
}

void Launcher::StartGameLoop()
{
	auto* engine = new Hi_Engine::Engine{ new Game{} };

	if (engine->Init())
	{
		engine->Run();
	}

	engine->Shutdown();
	delete engine;
}