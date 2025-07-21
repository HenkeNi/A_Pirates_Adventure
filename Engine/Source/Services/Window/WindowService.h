#pragma once
#include "../IService.h"

struct GLFWwindow;

namespace Hi_Engine
{
	struct WindowConfig;
	class EventService;

	class WindowService : public IService
	{
	public:
		WindowService(std::weak_ptr<EventService> eventService);
		~WindowService() = default;

		// ==================== Lifecycle ====================
		bool Initialize(const WindowConfig& config);

		void Shutdown() noexcept override;
	
		// ==================== Queries ====================
		[[nodiscard]] bool IsOpen() const noexcept;

		[[nodiscard]] bool IsFullscreen() const noexcept;

		[[nodiscard]] const IVector2& GetSize() const noexcept;

		[[nodiscard]] float GetAspectRatio() const noexcept;

		[[nodiscard]] GLFWwindow* GetGLFWHandle() const noexcept;

		// ==================== Operations ====================
		void SwapBuffers() const;

		void ToggleFullscreen();
		
		void Close();
		
		void SetTitle(std::string_view title);
		
		void SetSize(const IVector2& size);
		
		void SetIcon(const std::filesystem::path& iconPath);

	private:
		// ==================== Interal Helpers ====================
		[[nodiscard]] GLFWwindow* CreateWindow(const IVector2& size, const std::string& title) const;

		// ==================== Data Members ====================
		IVector2		m_size;
		GLFWwindow*		m_window;
		std::weak_ptr<EventService> m_eventService;
	};
}