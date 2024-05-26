#include "Pch.h"
#include "Window.h"
#include <GLFW/glfw3.h>


namespace Hi_Engine
{
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	void WindowFocusCallback(GLFWwindow* window, int focused);
	void WindowCloseCallback(GLFWwindow* window);


	Window::Window()
		: m_window{ nullptr }
	{
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::Init(IVector2 size, const std::string& name)
	{
		if (!glfwInit())
			return false;

		m_window = CreateWindow(size, name);
		
		if (!m_window)
			return false;

		m_size = size;

		glfwSwapInterval(0); // turns off V-sync
		glViewport(0, 0, m_size.x, m_size.y);
		//

		return true;
	}

	void Window::Shutdown()
	{
		if (IsOpen())
			Close();

		glfwTerminate();
	}

	bool Window::IsOpen() const
	{
		return !glfwWindowShouldClose(m_window);
	}

	const IVector2& Window::GetSize() const
	{
		return m_size;
	}

	void Window::PollEvents() const
	{
		glfwPollEvents();
	}

	void Window::ClearScreen() const
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		m_size = size;
	}

	void Window::SetIcon(const std::string& texturePath)
	{
		GLFWimage image;
		image.pixels = stbi_load(texturePath.c_str(), &image.width, &image.height, 0, 4);

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

			return window;
		}

		glfwTerminate();
		return nullptr;
	}

#pragma region CALLBACK_FUNCTIONS

	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);	// Todo; send event?
	}

	void WindowFocusCallback(GLFWwindow* window, int focused)
	{
		//assert(false && "Not implemtend");

		//Dispatcher::GetInstance().SendEvent(Event{ aFocused ? eEventType::WindowGainedFocus : eEventType::WindowLostFocus, nullptr });
	}

	void WindowCloseCallback(GLFWwindow* window)
	{
		Dispatcher::GetInstance().SendEventInstantly(new TerminationEvent);
	}

#pragma endregion CALLBACK_FUNCTIONS
}