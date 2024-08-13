#pragma once

namespace Hi_Engine
{
	class Window;
	class PhysicsEngine;
	
	class ServiceLocator
	{
	public:
		static void Register(std::weak_ptr<Window> window);
		static void Register(std::weak_ptr<PhysicsEngine> physics);

		static std::weak_ptr<Window> GetWindow();
		static std::weak_ptr<PhysicsEngine> GetPhysics();

	private:
		inline static std::weak_ptr<Window> s_window;
		inline static std::weak_ptr<PhysicsEngine> s_physics;
	};
}
