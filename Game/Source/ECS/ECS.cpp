#include "Pch.h"
#include "ECS.h"
#include "Entities/EntityManager.h"


void ECS::Init()
{
	m_entityManager = new EntityManager;
	m_entityManager->GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");
}

void ECS::Shutdown()
{
	m_systemManager.Clear();
	m_entityManager->DestroyAll();

	delete m_entityManager;
}

#include "Systems/Systems.h"

void ECS::RegisterSystems(const std::vector<std::string>& systems)
{
	// TODO: improve... (SystemBuilders??)

	for (const std::string& system : systems)
	{
		m_systemManager.Create(system);


		//if (system == "CameraSystem")
		//	m_systemManager.Register<CameraSystem>(); // or pass in m_entityManager?
		//if (system == "TextRenderSystem")
		//	m_systemManager.Register<TextRenderSystem>();
		//if (system == "SpriteRenderSystem")
		//	m_systemManager.Register<SpriteRenderSystem>();
		//if (system == "UISystem")
		//	m_systemManager.Register<UISystem>();
		//if (system == "UIRenderSystem")
		//	m_systemManager.Register<UIRenderSystem>();
	}

	m_systemManager.Init(m_entityManager); // Pass in systems...
}

// void ECS::LoadSystems(const std::string& path)
//{
	// Call SystemManager??

	// Create systems (read from json)
	// make sure to call init with EntityManager!
//}
