#include "Pch.h"
#include "Application.h"

namespace Hi_Engine
{
	Application::Application()
		: m_serviceRegistry{ nullptr }
	{
	}

	void Application::Initialize(ServiceRegistry* registry)
	{
		m_serviceRegistry = registry;
	}
}