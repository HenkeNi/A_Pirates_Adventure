#pragma once
#include "Event/Core/EventListener.h"
#include "../Service/ServiceRegistry.h"
#include "Config/EngineConfig.h"

namespace Hi_Engine
{
	class Application;

	class Engine : public EventListener
	{
	public:
		Engine(Application& app);
		~Engine() = default;


		void OnEvent(class TerminationEvent& event);

		bool Init();
		void Shutdown();
		void Run();

	private:
		void RegisterServiceTypes();
		void RegisterComponents();
		void RegisterSystems();
		bool SetupServices();
		
		// Store engine config..
		// display system?

		// Store core system here??

		ServiceRegistry m_services;
		EngineConfig m_engineConfig;
 		Application& m_application;
		bool m_isRunning;
	};
}