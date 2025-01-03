#include "Pch.h"
#include "TimeSystem.h"
#include "Time/Timer.h"
#include "ECS/ECS.h"
#include "ECS/Components/CoreComponents.h"

namespace Hi_Engine
{
    TimeSystem::TimeSystem(ECSCoordinator& ecs, Timer& timer)
        : System{ ecs }, m_timer{ timer }
    {
    }

    void TimeSystem::Update(float deltaTime)
    {
        for (auto& timerComponent : m_ecs.GetComponents<TimerComponent>())
        {
            if (timerComponent.IsDone)
                continue;

            float& elapsedTime = timerComponent.ElapsedTime;
            elapsedTime += deltaTime;
                
            if (elapsedTime >= timerComponent.Duration)   
            {
                elapsedTime = 0.f;
                timerComponent.IsDone = true;
                
                if (timerComponent.Callback)
                    timerComponent.Callback();

                // TODO; consider removing component    
            }
        }
    }

    eUpdatePhase TimeSystem::GetUpdatePhase() const
    {
        return eUpdatePhase::PreUpdate;
    }
}