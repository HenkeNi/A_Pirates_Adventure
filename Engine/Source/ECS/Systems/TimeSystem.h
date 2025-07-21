#pragma once
#include "System.h"
#include "Core/Registry/RegistryAliases.h"

namespace Hi_Engine
{
	class EventService;
	class ServiceRegistry;
	class TimeService;
	class EventTrigger;

	// TODO; rename TimerSystem?
	class TimeSystem : public System
	{
	public:
		TimeSystem(World& world, ServiceRegistry& registry);

		void Update(float deltaTime) override;

	private:
		void DispatchEvent(EventTrigger& trigger);

		std::weak_ptr<TimeService> m_timeService;
		std::weak_ptr<EventService> m_eventService;
		std::weak_ptr<EventRegistryService> m_eventRegistry;
	};
}

/*
* 	bool TimeService::HasTimeElapsed(double duration, double startTime) const
	{
		return startTime + duration >= GetTotalTime();
	}
*/