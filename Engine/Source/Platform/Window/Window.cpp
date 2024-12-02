#include "Pch.h"
#include "Window.h"
#include "Input/InputHandler.h"
#include <GLFW/glfw3.h>


namespace Hi_Engine
{
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	void WindowFocusCallback(GLFWwindow* window, int focused);
	void WindowCloseCallback(GLFWwindow* window);


	Window::Window(int initOrder)
		: Module{ initOrder }, m_window{ nullptr }
	{
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::Init()
	{
		if (!glfwInit())
			return false;

		m_window = CreateWindow({ 1200, 800 }, "");

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

	void Window::Deserialize(const rapidjson::Value& json)
	{
		auto window = json["window"].GetObject();

		std::string name = window["name"].GetString();
		SetTitle(name);

		std::string iconPath = window["icon_path"].GetString();
		SetIcon(iconPath);

		m_size.x = window["size"]["width"].GetInt();
		m_size.y = window["size"]["height"].GetInt();
		SetSize(m_size);
	}

	bool Window::IsOpen() const
	{
		bool IsOpen = m_window ? !glfwWindowShouldClose(m_window) : false;
		return IsOpen;
	}

	GLFWwindow* Window::GetWindow()
	{
		return m_window;
	}

	const IVector2& Window::GetSize() const
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

		WindowEvent* event = new WindowEvent;
		event->Init(eWindowEvent::Resize, { (unsigned)width, (unsigned)height });
		EventDispatcher::GetInstance().SendEventInstantly(event);
	}

	void WindowFocusCallback(GLFWwindow* window, int focused)
	{
		//assert(false && "Not implemtend");

		//EventDispatcher::GetInstance().SendEvent(Event{ aFocused ? eEventType::WindowGainedFocus : eEventType::WindowLostFocus, nullptr });
	}

	void WindowCloseCallback(GLFWwindow* window)
	{
		EventDispatcher::GetInstance().SendEventInstantly(new TerminationEvent);
	}

#pragma endregion CALLBACK_FUNCTIONS
}