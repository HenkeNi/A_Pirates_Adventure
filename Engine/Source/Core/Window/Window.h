#pragma once
#include "../Data/Structs.h"
#include "Utility/Math/Vectors/Vector.hpp"
#include <GLFW/glfw3.h>

namespace Hi_Engine
{
	namespace CU = CommonUtilities;
	class Engine;

	class Window
	{
	public:
		Window();
		~Window();

		bool							Init(WindowData someData);
		bool							IsOpen()										const;
		const CU::Vector2<unsigned>&	GetSize()										const;
		void							PollEvents()									const;
		void							ClearScreen()									const;
		void							SwapBuffers()									const;
		void							Close();

		void							SetSize(const CU::Vector2<unsigned>& aSize);
		void							SetIcon(const std::string& aTexturePath);
		void							ToggleFullscreen();
		
	private:
		friend class					Engine;

		bool							InitGlfw()										const;
		bool							CreateWindow();

		WindowData						m_data;
		GLFWwindow*						m_window;
	};
}