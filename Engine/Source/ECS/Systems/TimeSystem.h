#pragma once
#include "System.h"
#include "Core/Registry/RegistryAliases.h"

namespace Hi_Engine
{
	class EventService;
	class ServiceRegistry;
	class TimeService;

	class TimeSystem : public System
	{
	public:
		TimeSystem(World& world, ServiceRegistry& registry);

		void Update(float deltaTime) override;
		eUpdatePhase GetUpdatePhase() const override;

	private:	
		std::weak_ptr<TimeService> m_timeService;
		std::weak_ptr<EventService> m_eventService;
		std::weak_ptr<EventRegistryService> m_eventRegistry;
	};
}