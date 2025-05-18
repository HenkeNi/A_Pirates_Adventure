#pragma once
#include "Utility/NonCopyable.h"

namespace Hi_Engine
{
	class ServiceRegistry;

	class Application : public NonCopyable
	{
	public:
		Application();
		virtual ~Application() = default;

		Application(Application&&) = delete;
		Application& operator=(Application&&) = delete;

		void Initialize(ServiceRegistry* registry);
		virtual void OnUpdate(float deltaTime)		= 0;

		virtual void OnCreate()						 {};
		virtual void OnDestroy()					 {};

	protected:
		ServiceRegistry* m_serviceRegistry;
	};
}