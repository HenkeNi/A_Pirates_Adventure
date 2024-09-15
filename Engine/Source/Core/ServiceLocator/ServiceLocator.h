#pragma once

namespace Hi_Engine
{
	class Window;
	class PhysicsEngine;
	class ImGuiManager;
	
	// Use static functions on module manager instead?
	class ServiceLocator
	{
	public:
		static void Register(std::weak_ptr<Window> window);
		static void Register(std::weak_ptr<PhysicsEngine> physics);
		static void Register(std::weak_ptr<ImGuiManager> imgui);

		static std::weak_ptr<Window> GetWindow();
		static std::weak_ptr<PhysicsEngine> GetPhysics();
		static std::weak_ptr<ImGuiManager> GetImGuiManager();

	private:
		inline static std::weak_ptr<Window> s_window;
		inline static std::weak_ptr<PhysicsEngine> s_physics;
		inline static std::weak_ptr<ImGuiManager> s_imGuiManager;
	};
}
