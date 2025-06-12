#include "Pch.h"
#include "Editor.h"
#include "Platform/Window/Window.h"

namespace Hi_Engine
{
	Editor::Editor()
	{
		m_imguiWindows.reserve(10);
	}

	bool Editor::Initialize(Window* window)
	{
		// m_window = window;
		Setup(window->GetHandle());
		return true;
	}

	void Editor::Shutdown()
	{
		Destroy();
	}

	void Editor::HandleEvent(WindowEvent& event)
	{
		if (event.GetEventType() == eWindowEvent::Created)
		{
			Setup(event.GetWindow());
		}
	}

	ImGuiWindow& Editor::AddWindow(const ImGuiWindow& window)
	{
		assert(m_imguiWindows.size() < 10 && "Adding to many windows!");
		m_imguiWindows.push_back(window);

		return m_imguiWindows.back();
	}

	void Editor::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Editor::Update()
	{
		for (auto& window : m_imguiWindows)
		{
			window.Update();
		}


		//for (const auto& [buttons, pos, size, title, isMovable, isResizable] : m_windows)
		//{
		//	ImGui::Begin(title, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		//	ImGui::SetWindowPos({ pos.x, pos.y });
		//	ImGui::SetWindowSize({ size.x, size.y });

		//	for (const auto& [callback, label] : buttons)
		//	{
		//		if (ImGui::Button(label))
		//			callback();
		//	}

		//	// TEMP:
		//	static float noiseValue = 0.f;
		//	if (ImGui::SliderFloat("Noise", &noiseValue, 0.0001f, 1.f, "%.6f"))
		//		NoiseGenerator::SetFrequency(noiseValue);
		//		
	
		//	static int currentItem = 0; // Index of the currently selected item
		//	
		//	const char* items[5];
		//	items[0] = "I";
		//	items[1] = "I";
		//	items[2] = "I";

		//	//const char* items[] = { "Item 1", "Item 2", "Item 3" }; // List of items for the combo box
		//	//if (ImGui::Combo("Combo Box", &currentItem, items, IM_ARRAYSIZE(items))) 
		//	if (ImGui::Combo("Combo Box", &currentItem, items, 3)) 
		//	{
		//	}


		//	ImGui::End();
		//}



		// Render dear imgui into screen
		// 
		Render();
	}

	void Editor::Render() // do in render system?
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Editor::Setup(GLFWwindow* window)
	{
		if (window)
		{
			if (ImGui::GetCurrentContext())
				Destroy();

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io; // Suppresses the unused variable warning
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;

			ImGui::StyleColorsDark();

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
		}
	}

	void Editor::Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		ImGui::DestroyContext();
	}
}