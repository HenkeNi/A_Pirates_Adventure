#pragma once
#include "EventSystem/Core/EventListener.h"
#include "Modules/ModuleManager.h"

namespace Hi_Engine
{
	class Application;
	class Timer;

	class Engine : public EventListener
	{
	public:
		Engine(Application& app);
		~Engine();

		void HandleEvent(class TerminationEvent& event) override;

		bool Init();
		void Shutdown();
		void Run();

		static Timer& GetTimer();

	private:
		void RegisterModules();
		void LoadResources();

		ModuleManager m_moduleManager;
		Application& m_application;
		bool m_isRunning;
	};
}