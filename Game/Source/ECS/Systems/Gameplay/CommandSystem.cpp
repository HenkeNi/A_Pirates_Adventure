#include "Pch.h"
#include "CommandSystem.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS/ECS.h"

CommandSystem::CommandSystem()
{
}

CommandSystem::~CommandSystem()
{
}

void CommandSystem::Update(float deltaTime)
{
	for (Entity entity : m_ecs->FindEntities(m_signatures["Commands"]))
	{
		ProcessCommands(entity);
	}
}

void CommandSystem::SetSignature()
{
	m_signatures.insert({ "Commands", m_ecs->GetSignature<CommandQueueComponent>() });
}

void CommandSystem::ProcessCommands(Entity entity)
{
	auto* commandQueueComponent = m_ecs->GetComponent<CommandQueueComponent>(entity);

	if (!commandQueueComponent)
		return;

	auto& commands = commandQueueComponent->Commands;

	while (!commands.empty())
	{
		Command command = commands.front();
		commands.pop();

		switch (command.Type)
		{
		case eCommandType::Move:
			HandleMoveCommand(entity, std::get<MovementData>(command.Data));
			break;
		case eCommandType::Sprint:
			HandleSprintCommand(entity, std::get<SprintData>(command.Data));
			break;
		case eCommandType::Attack:
			HandleAttackCommand(entity);
			break;
		case eCommandType::Shoot:
			HandleProjectileCommand(entity);
			break;
		case eCommandType::Interact:
			break;
		//case eCommandType::Aim: -> send event? entered aim?
		}
	}
}

void CommandSystem::HandleMoveCommand(Entity entity, const MovementData& data)
{
	if (auto* velocityComponent = m_ecs->GetComponent<VelocityComponent>(entity))
	{
		auto& velocity = velocityComponent->Velocity;

		velocity += data.Direction;

		Hi_Engine::Math::Clamp(velocity.x, -1.f, 1.f);
		Hi_Engine::Math::Clamp(velocity.y, -1.f, 1.f);

		if (velocity.Length() > 1.0f) 
		{
			velocity.Normalize();
		}
	}
}

void CommandSystem::HandleSprintCommand(Entity entity, const SprintData& data)
{
	if (auto* velocityComponent = m_ecs->GetComponent<VelocityComponent>(entity))
	{
		velocityComponent->CurrentSpeed = data.Speed; // TODO; decrease speed in movement system?
	}
}

void CommandSystem::HandleAttackCommand(Entity entity)
{
	PostMaster::GetInstance().SendMessage({ eMessage::EntityAttacked, entity });
}

void CommandSystem::HandleProjectileCommand(Entity entity)
{
	// handle elsewhere??

	// wont work if enemies fires!!
	auto* inputComponent = m_ecs->GetComponent<InputComponent>(entity);
	auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);

	auto mousePosition = inputComponent->MouseWorldPosition;

	ProjectileData data;
	data.Position = transformComponent->CurrentPos; // include offset?
	data.Directin = { (float)mousePosition.x - data.Position.x, (float)mousePosition.y - data.Position.y };
	data.Directin.Normalize();
	data.Speed = 400.f; // todo, send actual projectile data?

	PostMaster::GetInstance().SendMessage({ eMessage::EntityFired, data });
}