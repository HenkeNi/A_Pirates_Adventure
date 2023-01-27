#include "Pch.h"
#include "Window.h"


namespace Hi_Engine
{
	void FrameBufferSizeCallback(GLFWwindow* aWindow, int aWidth, int aHeight);
	void WindowFocusCallback(GLFWwindow* aWindow, int aFocused);


	Window::Window()
		: m_window{ nullptr }
	{
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::Init(WindowData someData)
	{
		std::swap(m_data, someData);

		if (!InitGlfw() || !CreateWindow())
			return false;

		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);
		glfwSetWindowFocusCallback(m_window, WindowFocusCallback);

		glViewport(0, 0, m_data.m_size.x, m_data.m_size.y);
		SetIcon(m_data.m_iconPath);

		return true;
	}

	bool Window::IsOpen() const
	{
		return !glfwWindowShouldClose(m_window);
	}

	const CU::Vector2<unsigned>& Window::GetSize() const
	{
		return m_data.m_size;
	}

	void Window::PollEvents() const
	{
		glfwPollEvents();
	}

	void Window::ClearScreen() const
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(m_window);
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(m_window, true);
	}

	void Window::SetSize(const CU::Vector2<unsigned>& aSize)
	{
		glfwSetWindowSize(m_window, aSize.x, aSize.y);
		m_data.m_size = aSize;
	}

	void Window::SetIcon(const std::string& aTexturePath)
	{
		/*GLFWimage image;
		image.pixels = stbi_load(aTexturePath.c_str(), &image.width, &image.height, 0, 4);

		glfwSetWindowIcon(m_window, 1, &image);
		stbi_image_free(image.pixels);

		m_data.m_iconPath = aTexturePath;*/
	}

	bool Window::InitGlfw() const
	{
		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return true;
	}

	bool Window::CreateWindow()
	{
		m_window = glfwCreateWindow(m_data.m_size.x, m_data.m_size.y, m_data.m_name.c_str(), nullptr, nullptr);
		if (!m_window)
		{
			glfwTerminate();
			return false;
		}
	}

#pragma region CALLBACK_FUNCTIONS

	void FrameBufferSizeCallback(GLFWwindow* aWindow, int aWidth, int aHeight)
	{
		glViewport(0, 0, aWidth, aHeight);
	}

	void WindowFocusCallback(GLFWwindow* aWindow, int aFocused)
	{
		//assert(false && "Not implemtend");

		//Dispatcher::GetInstance().SendEvent(Event{ aFocused ? eEventType::WindowGainedFocus : eEventType::WindowLostFocus, nullptr });
	}

#pragma endregion CALLBACK_FUNCTIONS
}