#include "Pch.h"
#include "TimeSystem.h"
#include "Services/ServiceRegistry.h"
#include "Services/Time/TimeService.h"
#include "ECS/World/World.h"
#include "ECS/Components/CoreComponents.h"
#include "Registry/RegistryAliases.h"

namespace Hi_Engine
{
    TimeSystem::TimeSystem(World& world, ServiceRegistry& registry)
        : System{ world, eUpdatePhase::PreUpdate }, m_timeService{ registry.TryGetWeak<TimeService>() }, m_eventService{ registry.TryGetWeak<EventService>() }, m_eventRegistry{ registry.TryGetWeak<EventRegistryService>() }
    {
    }

    void TimeSystem::Update(float deltaTime)
    {
        auto view = m_world.GetComponentView<TimerComponent>();
        view.ForEach([=](TimerComponent& component)
            {
                if (component.IsDone)
                    return;
           
                float& elapsedTime = component.ElapsedTime;
                elapsedTime += deltaTime;
                        
                if (elapsedTime >= component.Duration)   
                {
                    elapsedTime = 0.f;
                    component.IsDone = true;

                    DispatchEvent(component.OnCompleted);
                }
            });
    }

    void TimeSystem::DispatchEvent(EventTrigger& trigger)
    {
        auto eventService = m_eventService.lock();

        if (!eventService)
        {
            Logger::LogWarning("[TimeSystem::DispatchEvent] - EventService is invalid!");
            return;
        }

        auto eventRegistry = m_eventRegistry.lock();

        if (!eventRegistry)
        {
            Logger::LogWarning("[TimeSystem::DispatchEvent] - EventRegistry is invalid!");
            return;
        }

        const auto& [name, dispatcher] = eventRegistry->Get(trigger.EventName);
        
        dispatcher(*eventService, trigger.Params);
    }
}