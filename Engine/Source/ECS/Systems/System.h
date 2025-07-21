#pragma once

namespace Hi_Engine
{
	class SystemManager;
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
		System(World& world, eUpdatePhase phase);
		virtual ~System() = default;

		virtual void Update(float deltaTime) {};

		[[nodiscard]] inline bool IsEnabled() const noexcept { return m_isEnabled; }
		[[nodiscard]] inline eUpdatePhase GetUpdatePhase() const noexcept { return m_updatePhase; }

	protected:
		virtual void OnCreated() {};
		virtual void OnDestroyed() {};

		virtual void OnDisabled() {};
		virtual void OnEnabled() {};

		World& m_world;

	private:
		void Enable();
		void Disable();

		friend class SystemManager;

		eUpdatePhase m_updatePhase;
		bool m_isEnabled;
	};
}