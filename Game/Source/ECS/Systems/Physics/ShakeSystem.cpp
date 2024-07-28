#include "Pch.h"
#include "ShakeSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"


ShakeSystem::ShakeSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityAttacked, this);
}

ShakeSystem::~ShakeSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityAttacked, this);
}

void ShakeSystem::Receive(Message& message)
{
	if (message.GetMessageType() == eMessage::EntityAttacked)
	{
		if (auto entity = std::any_cast<Entity>(message.GetData()))
		{
			if (auto* shakeComponent = m_ecs->GetComponent<ShakeComponent>(entity))
			{
				shakeComponent->m_isShaking = true;

				shakeComponent->m_elapsedTime = 0.f;
			}
		}
	}
}

void ShakeSystem::Update(float deltaTime)
{
	assert(m_ecs && "ERROR: EntityManager is nullptr!");

	auto entities = m_ecs->FindEntities(m_signatures["Shake"]);

	for (auto entity : entities)
	{
		auto* shakeComponent = m_ecs->GetComponent<ShakeComponent>(entity);

		if (!shakeComponent->m_isShaking)
			continue;

		auto* transformeComponent = m_ecs->GetComponent<TransformComponent>(entity);

		if (shakeComponent->m_elapsedTime < shakeComponent->m_duration)
		{
			shakeComponent->m_elapsedTime += deltaTime;

			static float speed = 50.f;
			static float amount = 1.f;
			transformeComponent->Rotation += std::sin((float)Hi_Engine::Engine::GetTimer().GetTotalTime() * speed) * amount;
		}
		else
		{
			shakeComponent->m_isShaking = false;
			transformeComponent->Rotation = 0.f;
		}
	}
}

void ShakeSystem::SetSignature()
{
	m_signatures.insert({ "Shake", m_ecs->GetSignature<ShakeComponent>() });
}
