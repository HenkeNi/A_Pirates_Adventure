#include "Pch.h"
#include "ShootCommand.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"
#include "ECS.h"


ShootCommand::ShootCommand()
	: m_timestamp{ 0.0 }, m_delayBetweenShots{ 0.5f }
{
}

void ShootCommand::Execute(Entity entity, ECS& ecs)
{
	double currentTime = Hi_Engine::Engine::GetTimer().GetTotalTime();

	if (currentTime < m_timestamp + m_delayBetweenShots)
		return;

	m_timestamp = currentTime;

	auto* transformComponent = ecs.GetComponent<TransformComponent>(entity);
	auto* inputComponent = ecs.GetComponent<InputComponent>(entity);

	// TODO; convert mouse to inworld position => store mouse pls in woorld coord on player?
	// MousePosToWorldCoords(mousePosition.x, mousePosition.y, 1400, 800, );

	auto mousePosition = inputComponent->MouseWorldPosition;

	ProjectileData data;
	data.Position = transformComponent->CurrentPos; // include offset?
	data.Directin = { (float)mousePosition.x - data.Position.x, (float)mousePosition.y - data.Position.y };
	data.Directin.Normalize();
	data.Speed = 400.f; // todo, send actual projectile data?

	PostMaster::GetInstance().SendMessage({ eMessage::EntityFired, data });
}

bool ShootCommand::CanPerform(Entity entity, ECS& ecs) const
{
	return false;
}