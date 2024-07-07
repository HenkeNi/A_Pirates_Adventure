#pragma once

namespace Hi_Engine
{
	class Window;
	
	class ServiceLocator
	{
	public:
		static void Register(std::weak_ptr<Window> window);

		static std::weak_ptr<Window> GetWindow();

	private:
		inline static std::weak_ptr<Window> s_window;
	};
}
