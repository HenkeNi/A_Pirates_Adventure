#pragma once
// #include "Messaging/Listener/EventListener.h"
#include "../Modules/Base/Module.h"
#include "ImGuiTypes.h"

namespace Hi_Engine
{
	// Todo; consider making Editor a project (.exe)
	class ImGuiManager : public Module, public EventListener
	{
	public:
		ImGuiManager(int initOrder);

		void HandleEvent(class CreateImGuiWindowRequest& event) override;

		bool Init() override;
		void Shutdown() override;

		template <typename... Args>
		void CreateWindow(Args&&... args);

		void BeginFrame();
		void Render();

	private:
		std::vector<ImGuiWindow> m_windows;
	};

#pragma region Method_Definitions
	
	template <typename... Args>
	void ImGuiManager::CreateWindow(Args&&... args)
	{
		m_windows.emplace_back(std::forward<Args>(args)...);
	}

#pragma endregion Method_Definitions
}