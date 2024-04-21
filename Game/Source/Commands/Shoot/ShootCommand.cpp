#include "Pch.h"
#include "ShootCommand.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"

ShootCommand::ShootCommand()
	: m_timestamp{ 0.0 }, m_delayBetweenShots{ 0.5f }
{
}

void ShootCommand::Execute(Entity* entity)
{
	double currentTime = Hi_Engine::Engine::GetTimer().GetTotalTime();

	if (currentTime < m_timestamp + m_delayBetweenShots)
		return;

	m_timestamp = currentTime;

	auto* transformComponent = entity->GetComponent<TransformComponent>();
	auto* inputComponent = entity->GetComponent<InputComponent>();

	// TODO; convert mouse to inworld position => store mouse pls in woorld coord on player?
	//MousePosToWorldCoords(mousePosition.x, mousePosition.y, 1400, 800, );

	auto mousePosition = inputComponent->MouseWorldPosition;

	ProjectileData data;
	data.Position = transformComponent->CurrentPos; // include offset?
	data.Directin = { (float)mousePosition.x - data.Position.x, (float)mousePosition.y - data.Position.y };
	data.Directin.Normalize();
	data.Speed = 4.f;

	PostMaster::GetInstance().SendMessage({ eMessage::EntityFired, data });
}

bool ShootCommand::CanPerform(Entity* entity) const
{
	return false;
}