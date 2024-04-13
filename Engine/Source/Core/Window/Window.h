#pragma once
#include "../Utility/Math/Vectors/Vector.hpp"

struct GLFWwindow;

namespace Hi_Engine
{
	namespace CU = CommonUtilities;
	class Engine;

	class Window
	{
	public:
		Window();
		~Window();

		bool			Init(WindowData data);
		bool			IsOpen()										const;
		const CU::Vector2<unsigned>& GetSize()							const;
		void			PollEvents()									const;
		void			ClearScreen()									const;
		void			SwapBuffers()									const;
		void			Close();

		void			SetTitle(const std::string& title);
		void			SetSize(const CU::Vector2<unsigned>& size);
		void			SetIcon(const std::string& texturePath);
		void			ToggleFullscreen();

	private:
		bool			InitGlfw()										const;	// integrate in Init?
		bool			CreateWindow();	// static?

		friend	class Engine;

		WindowData		m_data;
		GLFWwindow*		m_window;
	};
}