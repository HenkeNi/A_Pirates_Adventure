#pragma once
#include "System.h"

namespace Hi_Engine
{
	class InputService;
	class WindowService;

	class InputSystem : public System
	{
	public:
		InputSystem(World& world, InputService& input, WindowService& window);

		void Update(float deltaTime) override;

	private:
		InputService& m_inputService;
		WindowService& m_windowService;
	};
}