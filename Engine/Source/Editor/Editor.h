#pragma once
#include "../Core/Event/Core/EventListener.h"
#include "../Core/Modules/Module.h"
#include "ImGui/ImGuiTypes.h"

struct GLFWwindow;

namespace Hi_Engine
{
	// Todo; consider making Editor a project (.exe)
	class Editor : public Module, public EventListener
	{
	public:
		Editor(ModuleManager& manager);

		bool Init() override;
		void Shutdown() override;

		void HandleEvent(class WindowEvent& event) override;

		//template <typename... Args>
		//void CreateWindow(Args&&... args);

		ImGuiWindow& AddWindow(const ImGuiWindow& window);

		void BeginFrame();
		void Update(); // get windows instead??

		void Render();

	private:
		void Setup(GLFWwindow* window);
		void Destroy();

		std::vector<ImGuiWindow> m_imguiWindows;
	};

#pragma region Method_Definitions
	
	/*template <typename... Args>
	void ImGuiManager::CreateWindow(Args&&... args)
	{
		m_windows.emplace_back(std::forward<Args>(args)...);
	}*/

#pragma endregion Method_Definitions
}