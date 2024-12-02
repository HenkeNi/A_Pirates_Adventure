#include "Pch.h"
#include "EditorSystem.h"
#include "ECS.h"


EditorSystem::EditorSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::MouseClicked, this);

	// listen to some event instead; game finished loading or somethign...

	CreateEditorWindows();
}

EditorSystem::~EditorSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::MouseClicked, this);
}

void EditorSystem::Receive(Message& message)
{
	// listen to mouse button pressed?

	auto cursor = m_ecs->FindEntity(m_signatures["Cursor"]);

	if (auto* subentities = m_ecs->GetComponent<SubEntitiesComponent>(cursor.value()))
	{
		for (auto& entity : subentities->IDs)
		{
			auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);
			//transformComponent->CurrentPos = std::any_cast<FVector2>(message.GetData());
			transformComponent->CurrentPos = m_ecs->GetComponent<TransformComponent>(cursor.value())->CurrentPos;
		}

		subentities->IDs.clear();
	}
}

void EditorSystem::Update(float deltaTime)
{
	// check if any entities are selected....




}

void EditorSystem::SetSignature()
{
	m_signatures.insert({ "Cursor", m_ecs->GetSignature<CursorComponent>() });
}

void EditorSystem::CreateEditorWindows()
{
	auto imguiManager = Hi_Engine::ServiceLocator::GetImGuiManager().lock();

	if (!imguiManager)
		return;

	auto& leftWindow = imguiManager->AddWindow(Hi_Engine::ImGuiWindow{});
	leftWindow.SetTitle("Side window");
	leftWindow.SetDimensions({ 0.f, 0.f }, { 200.f, 600.f });
	leftWindow.SetWindowFlags(Hi_Engine::eImGuiWindowFlags::NoMove | Hi_Engine::eImGuiWindowFlags::NoResize | Hi_Engine::eImGuiWindowFlags::NoCollapse);


	//leftWindow.SetUpdateFunction([]() {
	//	ImGui::Begin(m_title, nullptr, (ImGuiWindowFlags)m_windowFlags);
	//	ImGui::SetWindowPos({ m_position.x, m_position.y });
	//	ImGui::SetWindowSize({ m_size.x, m_size.y });


	//	})

	auto& textInput = leftWindow.AddElement(0, Hi_Engine::ImGuiTextInput{}, "textInput");
	std::get_if<Hi_Engine::ImGuiTextInput>(&textInput)->Header = "Path";

	auto& searchButton = leftWindow.AddElement(0, Hi_Engine::ImGuiTextButton{}, "searchButton");
	std::get_if<Hi_Engine::ImGuiTextButton>(&searchButton)->Label = "Search";
	std::get_if<Hi_Engine::ImGuiTextButton>(&searchButton)->Callback = [&](Hi_Engine::ImGuiWindow& imguiWindow)
		{
			if (auto* inputElement = std::get_if<Hi_Engine::ImGuiTextInput>(imguiWindow.GetElement("textInput")))
			{
				if (Entity entity = m_ecs->CreateEntityFromBlueprint(inputElement->Buffer))
				{
					auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);
					transformComponent->CurrentPos = { 0.25f, 0.25f };
					transformComponent->Scale = { 50.f, 50.f };

					auto cursor = m_ecs->FindEntity(m_signatures["Cursor"]);
					if (!m_ecs->HasComponent<SubEntitiesComponent>(cursor.value()))
					{ 
						m_ecs->AddComponent<SubEntitiesComponent>(cursor.value());
					}

					auto* subEntitiesComponent = m_ecs->GetComponent<SubEntitiesComponent>(cursor.value());
					subEntitiesComponent->IDs.push_back(entity);

					// set to follow mouse.. also set render order infront of everything..	

					m_ecs->GetComponent<SpriteComponent>(entity)->RenderDepth = 2;
				}
			}
		};
	

	auto& saveButton = leftWindow.AddElement(0, Hi_Engine::ImGuiTextButton{}, "SaveButton");
	std::get_if<Hi_Engine::ImGuiTextButton>(&saveButton)->Label = "Save";
	std::get_if<Hi_Engine::ImGuiTextButton>(&saveButton)->Callback = [&](Hi_Engine::ImGuiWindow& imguiWindow) { m_ecs->Serialize("MainMenu.json"); };



	//std::get_if<Hi_Engine::ImGuiButton>(&searchButton)->Callback = [&]()
	//{
	//		// fetch instead every fra,e from eelemnets?
	//	const auto& header = std::get_if<Hi_Engine::ImGuiTextInput>(&textInput)->Header;
	//	std::cout << "Search; " << header << "\n";
	//};
	
		//Hi_Engine::ImGuiButton searchButton;
	//searchButton->Label = "Search";
	//searchButton.Callback = []() { std::cout << "Search; "; };


	// imguiManager->AddWindow(leftWindow);


	Hi_Engine::ImGuiWindow rightWindow;
	rightWindow.SetTitle("PropertyDetails");
	rightWindow.SetDimensions({ 1400.f - 200.f, 0.f }, { 200.f, 800.f });
	rightWindow.SetWindowFlags(Hi_Engine::eImGuiWindowFlags::NoMove | Hi_Engine::eImGuiWindowFlags::NoDecoration);

	imguiManager->AddWindow(rightWindow);

	auto& assetBrowser = imguiManager->AddWindow(Hi_Engine::ImGuiWindow{});
	assetBrowser.SetTitle("AssetBrowser");
	assetBrowser.SetDimensions({ 0, 800.f - 200.f }, { 1400.f - 200.f, 200.f });
	assetBrowser.SetWindowFlags(Hi_Engine::eImGuiWindowFlags::NoMove | Hi_Engine::eImGuiWindowFlags::NoDecoration);

	auto& assetTab = assetBrowser.AddElement(0, Hi_Engine::ImGuiTab{}, "assetTabs");
	auto* tab = std::get_if<Hi_Engine::ImGuiTab>(&assetTab);
	tab->Header = "Assets";
	tab->TabItems.push_back("UI");
	tab->TabItems.push_back("Environments");
	tab->TabItems.push_back("Characters");



	//auto document = Hi_Engine::ParseDocument("../../../../Assets/Json/Blueprints/UI/ui.json");
	//auto document = Hi_Engine::ParseDocument("../Game/Assets/Json/Blueprints/UI/ui.json");
	//for (auto& blueprint : document.GetArray())
	{
	//	auto id = blueprint["id"].GetString();
	//	std::cout << id;


		// create buttons with icons...  (samel ine)
	}
	//imguiManager->CreateWindow(buttons, FVector2{ 0.f, 0.f }, FVector2{ 200.f, 100.f }, "Left Window", false, false);

}