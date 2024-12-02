#pragma once
#include "../Core/Modules/Module.h"

struct GLFWwindow;

namespace Hi_Engine
{
	class Engine;

	class Window : public Module
	{
	public:
		Window(int initOrder);
		~Window();

		bool			Init()									  override;
		void			Shutdown()								  override;
		void			Deserialize(const rapidjson::Value& json) override;
	
		GLFWwindow*		GetWindow();
		const IVector2& GetSize()									const;
		bool			IsOpen()									const;
		void			SwapBuffers()								const;
		void			Close();

		void			SetTitle(const std::string& title);
		void			SetSize(const IVector2& size);
		void			SetIcon(const std::string& texturePath);
		void			ToggleFullscreen();

	private:
		GLFWwindow*		CreateWindow(const IVector2& size, const std::string& title);

		friend	class Engine;

		IVector2		m_size;
		GLFWwindow*		m_window;
	};
}