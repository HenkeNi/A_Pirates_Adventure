#pragma once
#include "../Service/IService.h"

struct GLFWwindow;

namespace Hi_Engine
{
	struct WindowConfig;
	class Engine;

	class Window : public IService
	{
	public:
		Window();
		~Window() = default;

		bool Initialize(const WindowConfig& config);
		void Shutdown() override;
	
		[[nodiscard]] GLFWwindow* GetHandle() const noexcept;
		[[nodiscard]] const IVector2& GetSize() const noexcept;
		[[nodiscard]] bool IsOpen() const noexcept;

		void SwapBuffers() const;
		void Close();
		void SetTitle(const std::string& title); // strign view?
		void SetSize(const IVector2& size);
		void SetIcon(const std::filesystem::path& iconPath);
		void ToggleFullscreen();

	private:
		GLFWwindow* CreateWindow(const IVector2& size, const std::string& title);

		friend	class Engine;

		IVector2		m_size;
		GLFWwindow*		m_window;
	};
}