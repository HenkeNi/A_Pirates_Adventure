#include "Pch.h"
#include "Window.h"


namespace Hi_Engine
{
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	void WindowFocusCallback(GLFWwindow* window, int focused);


	Window::Window()
		: m_window{ nullptr }
	{
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::Init(WindowData data)
	{
		std::swap(m_data, data);

		if (!InitGlfw() || !CreateWindow())
			return false;

		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);
		glfwSetWindowFocusCallback(m_window, WindowFocusCallback);
		glfwSwapInterval(0); // turns off V-sync

		glViewport(0, 0, m_data.Size.x, m_data.Size.y);
		SetIcon(m_data.IconPath);

		return true;
	}

	bool Window::IsOpen() const
	{
		return !glfwWindowShouldClose(m_window);
	}

	const CU::Vector2<unsigned>& Window::GetSize() const
	{
		return m_data.Size;
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

	void Window::SetSize(const CU::Vector2<unsigned>& size)
	{
		glfwSetWindowSize(m_window, size.x, size.y);
		m_data.Size = size;
	}

	void Window::SetIcon(const std::string& texturePath)
	{
		m_data.IconPath = texturePath;

		GLFWimage image;
		image.pixels = stbi_load(texturePath.c_str(), &image.width, &image.height, 0, 4);

		glfwSetWindowIcon(m_window, 1, &image);
		stbi_image_free(image.pixels);
	}

	void Window::ToggleFullscreen()
	{
	}

	bool Window::InitGlfw() const
	{
		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

		return true;
	}

	bool Window::CreateWindow()
	{
		m_window = glfwCreateWindow(m_data.Size.x, m_data.Size.y, m_data.Identifier.c_str(), nullptr, nullptr);
		if (!m_window)
		{
			glfwTerminate();
			return false;
		}

		return true;
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

#pragma endregion CALLBACK_FUNCTIONS
}