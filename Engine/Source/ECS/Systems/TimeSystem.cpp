#include "Pch.h"
#include "TimeSystem.h"
#include "Time/Timer.h"
#include "World/World.h"
#include "ECS/Components/CoreComponents.h"

namespace Hi_Engine
{
    TimeSystem::TimeSystem(World& ecs, Timer& timer)
        : System{ ecs }, m_timer{ timer }
    {
    }

    void TimeSystem::Update(float deltaTime)
    {
        auto view = m_ecs.GetComponentView<TimerComponent>();
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
                            
                            // if (timerComponent.Callback)
                                // timerComponent.Callback(); // solve by always using component view? and give access to entity when iterating over
                        }
            });

    //    for (auto& timerComponent : )
    //    {
    //        if (timerComponent.IsDone)
    //            continue;

    //        float& elapsedTime = timerComponent.ElapsedTime;
    //        elapsedTime += deltaTime;
    //            
    //        if (elapsedTime >= timerComponent.Duration)   
    //        {
    //            elapsedTime = 0.f;
    //            timerComponent.IsDone = true;
    //            
    //            // if (timerComponent.Callback)
    //                // timerComponent.Callback(); // solve by always using component view? and give access to entity when iterating over

    //            // TODO; consider removing component    
    //        }
    //    }
    }

    eUpdatePhase TimeSystem::GetUpdatePhase() const
    {
        return eUpdatePhase::PreUpdate;
    }
}