#pragma once
#include "Event/Core/EventListener.h"
#include "Modules/ModuleManager.h"

namespace Hi_Engine
{
	class Application;
	class ThreadPool;
	class Timer;

	class Engine : public EventListener
	{
	public:
		Engine(Application& app);
		~Engine() = default;

		void HandleEvent(class TerminationEvent& event) override;

		bool Init();
		void Shutdown();
		void Run();

	private:
		void RegisterModules();
		void SetupECS();
		
		//void LoadResources(); // do in game/app!? load shaders in renderer Init?

		ModuleManager m_moduleManager;
		Application& m_application;
		bool m_isRunning;
	};
}