#include "Pch.h"
#include "ImGuiTypes.h"


// TEMP
#include "Resources/ResourceHolder.h"
#include <Rendering/Texture/Subtexture2D.h>
#include <Rendering/Texture/Texture2D.h>


namespace Hi_Engine
{
	ImGuiWindow::ImGuiWindow()
		: ImGuiWindow("", { 0.f, 0.f }, { 0.f,0.f })
	{
	}

	ImGuiWindow::ImGuiWindow(const char* title, const FVector2& position, const FVector2& size)
		: m_title{ title }, m_position{ position }, m_size{ size }, m_windowFlags{ eImGuiWindowFlags::None }
	{
		for (auto& section : m_sections)
		{
			section.reserve(10);
		}
	}

	void ImGuiWindow::Update() 
	{
		// or have a "callback" function for update

		/*m_updateFunction();
		return;*/

		ImGui::Begin(m_title, nullptr, (ImGuiWindowFlags)m_windowFlags);
		ImGui::SetWindowPos({ m_position.x, m_position.y });
		ImGui::SetWindowSize({ m_size.x, m_size.y });



		// if (ImGui::Button)
		ImGui::BeginGroup();

		//auto subTexture = ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().GetResource({ "folder", 0, 0 });
		//auto texture = subTexture->GetTexture();

		//ImTextureID textureID = reinterpret_cast<void*>(static_cast<intptr_t>(texture.GetID()));
		// Draw the image as a button
		//if (ImGui::ImageButton(textureID, ImVec2(20, 20), ImVec2(0, 1), ImVec2(1, 0)))
		//{
			// Button clicked
	//	}


		//ImTextureID textureID = static_cast<void*>(texture.GetTexture().GetData());




		ImGui::SetWindowFontScale(0.5f); // Scale text 1.5x larger
		ImGui::Text("Button");
		ImGui::SetWindowFontScale(1.0f); // Reset scaling to normal

		ImGui::EndGroup();


		ImGui::Text("HELLO");


		//ImDrawList::AddText({ 0.f, 0.f }, 0, "HELLO DO");

	//	ImGui::SameLine(); // Keep the text on the same line
		//ImGui::Text("Button Title");
		/*ImGui::Button("HElo");
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("SUPRISE!");*/


	/*	if (ImGui::BeginTabBar("Tabs"))
		{
			if (ImGui::BeginTabItem("tab 1"))
			{
				ImGui::Text("HELLO");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("tab 2"))
			{
				ImGui::Text("BYE");
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}*/

		for (auto& section : m_sections)
		{
			for (auto& [id, imGuiElement] : section)
			{
				if (auto* button = std::get_if<ImGuiTextButton>(&imGuiElement))
				{
					UpdateTextButton(*button);
				}
				else if (auto* input = std::get_if<ImGuiTextInput>(&imGuiElement))
				{
					UpdateInput(*input);
				}
				else if (auto* combo = std::get_if<ImGuiCombo>(&imGuiElement))
				{

				}
				else if (auto* tab = std::get_if<ImGuiTab>(&imGuiElement))
				{
					UpdateTab(*tab);
				}
			}

			ImGui::Spacing();
		}


		

		//ImGui::Spacing();
		// ImGui::Separator();

		/*constexpr const char* name = "monkey";
		ImGui::Text("You are a %s", name);

		for (const auto& [callback, label] : m_buttons)
		{
			if (ImGui::Button(label))
				callback();
		}*/

		//ImGui::Columns(2);
		//ImGui::Text("First Column");

		//ImGui::NextColumn();
		//ImGui::Text("Second Column");

		//if (ImGui::BeginChild(1))
		//{
		//	ImGui::Button("DUMM!");

		//	ImGui::EndChild();
		//}



		// TEMP:
		//static float noiseValue = 0.f;
		//if (ImGui::SliderFloat("Noise", &noiseValue, 0.0001f, 1.f, "%.6f"))
		///	NoiseGenerator::SetFrequency(noiseValue);


		//static int currentItem = 0; // Index of the currently selected item

		//const char* items[5];
		//items[0] = "I";
		//items[1] = "I";
		//items[2] = "I";

		////const char* items[] = { "Item 1", "Item 2", "Item 3" }; // List of items for the combo box
		////if (ImGui::Combo("Combo Box", &currentItem, items, IM_ARRAYSIZE(items))) 
		//if (ImGui::Combo("Combo Box", &currentItem, items, 3))
		//{
		//}


		ImGui::End();

	}

	void ImGuiWindow::SetTitle(const char* title)
	{
		m_title = title;
	}

	void ImGuiWindow::SetDimensions(const FVector2& position, const FVector2& size)
	{
		m_position = position;
		m_size = size;
	}

	void ImGuiWindow::SetWindowFlags(eImGuiWindowFlags flag, bool enable)
	{
		m_windowFlags = m_windowFlags | flag;

	/*	if (enable)
			m_windowFlags |= flag;
		else
			m_windowFlags &= ~flag;*/
	}

	ImGuiElement& ImGuiWindow::AddElement(int section, const ImGuiElement& element, const char* id)
	{
		m_sections[section].insert_or_assign(id, element);
		return m_sections[section][id];
	}

	ImGuiElement* ImGuiWindow::GetElement(const char* id)
	{
		ImGuiElement* element = nullptr;

		for (auto& section : m_sections)
		{
			if (section.contains(id))
			{
				element = &section.at(id);
				break;
			}
		}

		return element;
	}

	void ImGuiWindow::ProcessElements()
	{
	}

	void ImGuiWindow::UpdateTextButton(ImGuiTextButton& button)
	{
		if (ImGui::Button(button.Label))
		{
			if (button.Callback)
				button.Callback(*this);
		}
	}

	void ImGuiWindow::UpdateInput(ImGuiTextInput& input)
	{
		if (ImGui::InputText(input.Header, input.Buffer, IM_ARRAYSIZE(input.Buffer)))
			std::cout << input.Buffer << "\n";


		//ImGui::InputText(input.Header, input.Buffer, IM_ARRAYSIZE(input.Buffer), ImGuiInputTextFlags_CallbackCharFilter, input.Callback);
	}

	void ImGuiWindow::UpdateTab(ImGuiTab& tab)
	{
		if (ImGui::BeginTabBar("Tabs"))
		{
			for (const auto* name : tab.TabItems)
			{
				if (ImGui::BeginTabItem(name))
				{
					ImGui::EndTabItem();
				}
			}
			
			ImGui::EndTabBar();
		}
	}

	//int ImGuiWindow::GetWindowFlags() const
	//{
	//	ImGuiWindowFlags flags = 0;

	//	if ((m_windowFlags & eImGuiWindowFlags::NoTitleBar) != eImGuiWindowFlags::None)
	//		flags |= ImGuiWindowFlags_NoTitleBar;
	//	if ((m_windowFlags & eImGuiWindowFlags::NoResize) != eImGuiWindowFlags::None)
	//		flags |= ImGuiWindowFlags_NoResize; // 2
	//	if ((m_windowFlags & eImGuiWindowFlags::NoMove) != eImGuiWindowFlags::None)
	//		flags |= ImGuiWindowFlags_NoMove; // 4
	//	if ((m_windowFlags & eImGuiWindowFlags::NoCollapse) != eImGuiWindowFlags::None)
	//		flags |= ImGuiWindowFlags_NoCollapse;

	void AssetBrowser::Update()
	{
		///ImGui::Begin("AssetBrowser", nullptr, (ImGuiWindowFlags)m_windowFlags);
		//ImGui::SetWindowPos({ m_position.x, m_position.y });
		//ImGui::SetWindowSize({ m_size.x, m_size.y });
	}

	//	return flags;
	//}
}