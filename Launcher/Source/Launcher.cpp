#include "Pch.h"
#include "Launcher.h"
#include "Engine/Engine.h"
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
	Game game;
	Hi_Engine::Engine engine{ game };

	if (engine.Init())
	{
		engine.Run();
	}

	engine.Shutdown();
}