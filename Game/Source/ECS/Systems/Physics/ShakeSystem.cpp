#include "Pch.h"
#include "ShakeSystem.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"

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

		if (auto* entity = std::any_cast<Entity*>(message.GetData()))
		{
			if (auto* shake = entity->GetComponent<ShakeComponent>())
			{
				shake->m_isShaking = true;

				shake->m_elapsedTime = 0.f;
			}
		}
	}
}

void ShakeSystem::Update(float deltaTime)
{
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	auto entities = m_entityManager->FindAll<ShakeComponent>();

	for (auto* entity : entities)
	{
		auto* shake = entity->GetComponent<ShakeComponent>();
		if (!shake->m_isShaking)
			continue;

		auto* transform = entity->GetComponent<TransformComponent>();

		if (shake->m_elapsedTime < shake->m_duration)
		{
			shake->m_elapsedTime += deltaTime;

			static float speed = 50.f;
			static float amount = 1.f;
			transform->Rotation += std::sin((float)Hi_Engine::Engine::GetTimer().GetTotalTime() * speed) * amount;
		}
		else
		{
			shake->m_isShaking = false;
			transform->Rotation = 0.f;
		}
	}
}