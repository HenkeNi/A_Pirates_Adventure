#pragma once
#include "../Services/Event/EventListener.h"
#include "../Services/ServiceRegistry.h" // add path in Premake...

namespace Hi_Engine
{
	class Application;

	class Engine : public EventListener // remove?
	{
	public:
		Engine(Application& app);
		~Engine() = default;

		bool Init();
		void Shutdown();
		void Run();

	private:
		void RegisterServices();
		void ConfigureRenderer();
		void LoadResources();

		void OnEvent(class TerminationEvent& event);
		
		// display system?

		ServiceRegistry m_serviceRegistry;
		Application& m_application;
		bool m_isRunning;
	};
}