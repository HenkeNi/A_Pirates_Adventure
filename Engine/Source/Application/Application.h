#pragma once
#include "Utility/NonCopyable.h"

namespace Hi_Engine
{
	// [Consider] - making OnCreated/OnDestroyed protected (friend class Engine)

	class ServiceRegistry;

	class Application : public NonCopyable
	{
	public:
		Application();
		virtual ~Application() = default;

		Application(Application&&) = delete;
		Application& operator=(Application&&) = delete;

		void Initialize(ServiceRegistry* registry);
		virtual void OnUpdate(float deltaTime) = 0;

		virtual void OnCreated() {};
		virtual void OnDestroyed() {};

	protected:
		ServiceRegistry* m_serviceRegistry;
	};
}