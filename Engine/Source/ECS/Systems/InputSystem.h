#pragma once
#include "System.h"

namespace Hi_Engine
{
	class InputHandler;
	class Window;

	class InputSystem : public System
	{
	public:
		InputSystem(World& ecs, InputHandler& inputHandler, Window& window);

		void Update(float deltaTime) override;
		eUpdatePhase GetUpdatePhase() const override;

	private:
		InputHandler& m_inputHandler;
		Window& m_window;
	};
}