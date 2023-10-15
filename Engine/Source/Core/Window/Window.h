#pragma once
#include "../Data/Structs.h"
#include "../Utility/Math/Vectors/Vector.hpp"
#include <../GLFW/include/GLFW/glfw3.h>
//#include <GLFW/glfw3.h>
//#include <../GLEW/include/GL/glew.h>

namespace
{
	using WndSize = CU::Vector2<unsigned>;
}

namespace Hi_Engine
{
	namespace CU = CommonUtilities;
	class Engine;

	class Window
	{
	public:
		Window();
		~Window();

		bool			Init(WindowData someData);
		bool			IsOpen()										const;
		const WndSize&	GetSize()										const;
		void			PollEvents()									const;
		void			ClearScreen()									const;
		void			SwapBuffers()									const;
		void			Close();

		void			SetTitle(const std::string& aTitle);
		void			SetSize(const CU::Vector2<unsigned>& aSize);
		void			SetIcon(const std::string& aTexturePath);
		void			ToggleFullscreen();

	private:
		bool			InitGlfw()										const;	// integrate in Init?
		bool			CreateWindow();	// static?

		friend	class Engine;

		WindowData		m_data;
		GLFWwindow*		m_window;
	};
}