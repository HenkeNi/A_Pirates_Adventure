#pragma once

namespace Hi_Engine
{
	class ECSCoordinator;

	enum class eUpdatePhase
	{
		PreUpdate,
		Update,
		PostUpdate
	};

	class System
	{
	public:
		System(ECSCoordinator& ecs); // dont? forces systems in game to accept ECS as parameter as well..
		virtual ~System() = default;

		virtual void Update(float deltaTime) {};
		virtual eUpdatePhase GetUpdatePhase() const = 0;

	protected:
		ECSCoordinator& m_ecs;
	};
}