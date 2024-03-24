#include "Pch.h"
#include "InventoryScene.h"
#include "Systems/SystemManager.h"

InventoryScene::InventoryScene(SharedContext context)
	: Scene{ context }
{
}

InventoryScene::~InventoryScene()
{
}

void InventoryScene::Update(float deltaTime)
{
	m_sharedContext.SystemManager.Update(deltaTime);
}

void InventoryScene::LateUpdate(float deltaTime)
{
}

void InventoryScene::Draw() const
{
	m_sharedContext.SystemManager.Draw();
}

void InventoryScene::OnCreated()
{
}

void InventoryScene::OnEnter()
{
	auto& systemManager = m_sharedContext.SystemManager;
	systemManager.Init(&m_entityManager);

	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");

	auto* background = m_entityManager.Create("image");
	background->GetComponent<SpriteComponent>()->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "sky", 0, 0 });

	auto* title = m_entityManager.Create("title_text");
	title->GetComponent<TextComponent>()->Text = "Inventory";
	title->GetComponent<TransformComponent>()->Pivot = { 0.5f, 0.5f };

	// background image..

	// UI element box...
	// render slots in grid...
	// todo. drag and drop

	// player stats
	// see player character
		// equip different items...


	auto* camera = m_entityManager.Create("camera");
	camera->GetComponent<CameraComponent>()->ShouldCull = false;
}

void InventoryScene::OnExit()
{
}
