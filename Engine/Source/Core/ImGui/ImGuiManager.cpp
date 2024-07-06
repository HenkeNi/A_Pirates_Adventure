#include "Pch.h"
#include "ImGuiManager.h"
#include "ServiceLocator/ServiceLocator.h"
#include "Window/Window.h"
#include "Messaging/Events/Debug/DebugEvents.h"
//#include "Messaging/Events/Debug/DebugEvents.h"




// Test - remove later...
#include "Noise/NoiseGenerator.h" // TEST...
//#include "../../Utility/Noise/NoiseGenerator.h"

namespace Hi_Engine
{
	ImGuiManager::ImGuiManager(int initOrder)
		: Module{ initOrder }
	{
		Dispatcher::GetInstance().Subscribe(this);
	}

	void ImGuiManager::HandleEvent(CreateImGuiWindowRequest& event)
	{
		// CreateWindow(event.)
		m_windows.push_back(event.GetWindow());
		Dispatcher::GetInstance().Unsubscribe(this);
	}

	bool ImGuiManager::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io; // Suppresses the unused variable warning

		ImGui::StyleColorsDark();

		auto window = ServiceLocator::GetWindow(); // todo; send event instead?

		if (auto win = window.lock())
		{
			ImGui_ImplGlfw_InitForOpenGL(win->GetWindow(), true);
			ImGui_ImplOpenGL3_Init("#version 330");
			
			return true;
		}

		return false;
	}

	void ImGuiManager::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiManager::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiManager::Render()
	{

		for (const auto& [buttons, pos, size, title, isMovable, isResizable] : m_windows)
		{
			ImGui::Begin(title, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
			ImGui::SetWindowPos({ pos.x, pos.y });
			ImGui::SetWindowSize({ size.x, size.y });

			for (const auto& [callback, label] : buttons)
			{
				if (ImGui::Button(label))
					callback();
			}

			// TEMP:
			static float noiseValue = 0.f;
			if (ImGui::SliderFloat("Noise", &noiseValue, 0.0001f, 1.f, "%.6f"))
				NoiseGenerator::SetFrequency(noiseValue);
				
	
			static int currentItem = 0; // Index of the currently selected item
			
			const char* items[5];
			items[0] = "I";
			items[1] = "I";
			items[2] = "I";

			//const char* items[] = { "Item 1", "Item 2", "Item 3" }; // List of items for the combo box
			//if (ImGui::Combo("Combo Box", &currentItem, items, IM_ARRAYSIZE(items))) 
			if (ImGui::Combo("Combo Box", &currentItem, items, 3)) 
			{
			}


			ImGui::End();
		}

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}