#pragma once

namespace Hi_Engine
{
	class World;

	enum class eUpdatePhase
	{
		PreUpdate,
		Update,
		PostUpdate
	};

	class System
	{
	public:
		System(World& ecs); // dont? forces systems in game to accept ECS as parameter as well..
		virtual ~System() = default;

		virtual void Update(float deltaTime) {};
		virtual eUpdatePhase GetUpdatePhase() const = 0;

		void SetEnabled(bool isEnabled);
		[[nodiscard]] bool IsEnabled() const noexcept;

	protected:
		World& m_ecs;
		bool m_isEnabled;
	};
}