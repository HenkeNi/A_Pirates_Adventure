#pragma once
#include "../Core/Event/Core/EventListener.h"
#include "Services/IService.h"
#include "ImGui/ImGuiTypes.h"

struct GLFWwindow;

namespace Hi_Engine
{
	class Window;

	// Todo; consider making Editor a project (.exe)
	class Editor : public IService, public EventListener
	{
	public:
		Editor(Window& window);

		bool Initialize() override;
		void Shutdown() override;

		void HandleEvent(class WindowEvent& event) override;

		//template <typename... Args>
		//void CreateWindow(Args&&... args);

		ImGuiWindow& AddWindow(const ImGuiWindow& window);
		ImGuiWindow& AddWindow(ImGuiWindow&& window);

		//ImGuiWindow& AddWindow(ImGuiWindow window); // OR only this?

		template <typename ValueType>
		std::enable_if_t<std::is_base_of_v<ImGuiWindow, ValueType>, ImGuiWindow&> AddWindow(ValueType&& window)
		{
			m_imguiWindows.push_back(std::forward<ValueType>(window));
		}

		void BeginFrame();
		void Update(); // get windows instead??

		void Render();

	private:
		void Setup(GLFWwindow* window);
		void Destroy();

		std::vector<ImGuiWindow> m_imguiWindows;
		class Window& m_window; // pointer instead? listen to unregister? or store service registry?
	};

#pragma region Method_Definitions
	
	/*template <typename... Args>
	void ImGuiManager::CreateWindow(Args&&... args)
	{
		m_windows.emplace_back(std::forward<Args>(args)...);
	}*/

#pragma endregion Method_Definitions
}