#include "Pch.h"
#include "Window.h"
#include "Input/InputHandler.h"
#include <GLFW/glfw3.h>

#include "Core/Config/EngineConfig.h"

namespace Hi_Engine
{
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	void WindowFocusCallback(GLFWwindow* window, int focused);
	void WindowCloseCallback(GLFWwindow* window);


	Window::Window()
		: m_window{ nullptr }
	{
	}

	bool Window::Initialize(const WindowConfig& config)
	{
		if (!glfwInit())
		{
			Logger::LogError("Window::Init - Failed to initialize GLFW!");
			return false;
		}

		m_window = CreateWindow({ config.Width, config.Height }, config.Title);
		m_size = { config.Width, config.Height };

		glfwSwapInterval(0); // turns off V-sync
		glViewport(0, 0, m_size.x, m_size.y);

		// HERE?
		glfwSetKeyCallback(m_window, InputHandler::KeyCallback);
		glfwSetCursorPosCallback(m_window, InputHandler::CursorCallback);
		glfwSetMouseButtonCallback(m_window, InputHandler::MouseButtonCallback);
		glfwSetScrollCallback(m_window, InputHandler::MouseScrollCallback);
		
		// glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
		return true;
	}

	void Window::Shutdown()
	{
		if (IsOpen())
			Close();

		glfwTerminate();
	}

	bool Window::IsOpen() const noexcept
	{
		bool IsOpen = m_window ? !glfwWindowShouldClose(m_window) : false;
		return IsOpen;
	}

	GLFWwindow* Window::GetHandle() const noexcept
	{
		return m_window;
	}

	const IVector2& Window::GetSize() const noexcept
	{
		return m_size;
	}
	
	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(m_window);
	}	

	void Window::Close()
	{
		glfwSetWindowShouldClose(m_window, true);
	}

	void Window::SetTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_window, title.c_str());
	}

	void Window::SetSize(const IVector2& size)
	{
		glfwSetWindowSize(m_window, size.x, size.y);
		glViewport(0, 0, m_size.x, m_size.y);

		m_size = size;
	}

	void Window::SetIcon(const std::filesystem::path& iconPath)
	{
		GLFWimage image;
		image.pixels = stbi_load(iconPath.string().c_str(), &image.width, &image.height, 0, 4);

		glfwSetWindowIcon(m_window, 1, &image);
		stbi_image_free(image.pixels);
	}

	void Window::ToggleFullscreen()
	{
	}

	GLFWwindow* Window::CreateWindow(const IVector2& size, const std::string& title)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		if (auto* window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr))
		{
			glfwMakeContextCurrent(window);
			glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
			glfwSetWindowFocusCallback(window, WindowFocusCallback);
			glfwSetWindowCloseCallback(window, WindowCloseCallback);

			EventDispatcher::GetInstance().SendEventInstantly<WindowEvent>(eWindowEvent::Created, IVector2{ size.x, size.y }, window);

			return window;
		}

		glfwTerminate();
		return nullptr;
	}

#pragma region CALLBACK_FUNCTIONS

	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);	// Todo; send event?

		EventDispatcher::GetInstance().SendEventInstantly<WindowEvent>(eWindowEvent::Resize, IVector2{ width, height }, window);
	}

	void WindowFocusCallback(GLFWwindow* window, int focused)
	{
		//assert(false && "Not implemtend");

		//EventDispatcher::GetInstance().SendEvent(Event{ aFocused ? eEventType::WindowGainedFocus : eEventType::WindowLostFocus, nullptr });
	}

	void WindowCloseCallback(GLFWwindow* window)
	{
		EventDispatcher::GetInstance().SendEventInstantly<TerminationEvent>();
	}

#pragma endregion CALLBACK_FUNCTIONS
}