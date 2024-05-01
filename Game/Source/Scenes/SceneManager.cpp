#include "Pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "../DataTypes/Enumerations.h"


SceneManager::SceneManager()
{
	PostMaster::GetInstance().Subscribe(eMessage::TransitionToScene, this);
	PostMaster::GetInstance().Subscribe(eMessage::RemoveScene, this);
}

SceneManager::~SceneManager()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::TransitionToScene, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::RemoveScene, this);
	Clear();
}

void SceneManager::Receive(Message& message)
{
	auto sceneType = std::any_cast<eScene>(message.GetData());
	
	if (!m_registeredScenes.contains(sceneType))
		return;

	

	eMessage messageType = message.GetMessageType();

	if (messageType == eMessage::TransitionToScene)
	{
		// Todo, only call exit if pop:ing?! (so no exit on game when adding pause..

		Push(sceneType); 
	}

	// ERROR occurs because two  SceneManagers!!
	else if (messageType == eMessage::RemoveScene) // TODO, same event? contain data for type (pop, push, etc)?
	{
		if (sceneType == m_stack.Top())
		{
			message.HandleMessage();
			Pop();
		}
	}
}

void SceneManager::Init(const std::initializer_list<eScene>& scenes)
{
	for (auto& scene : m_registeredScenes)
		scene.second->OnCreated();

	for (const auto scene : scenes)
		m_stack.Push(scene);

	m_paths.insert({ eScene::Inventory, "../Game/Assets/Json/Scenes/Inventory.json" });
	m_paths.insert({ eScene::Settings, "../Game/Assets/Json/Scenes/Settings.json" });
	m_paths.insert({ eScene::Menu, "../Game/Assets/Json/Scenes/MainMenu.json" });
	m_paths.insert({ eScene::Title, "../Game/Assets/Json/Scenes/Title.json" });
}


//void SceneManager::Init(int aSceneSet)
//{
//	for (int i = 1; i < (int)eScene::Count; i <<= 1)
//	{
//		auto type = static_cast<eScene>(i);
//
//		//if (aSceneSet & (int)type)
//		if ((aSceneSet & i) == i)
//			m_sceneStack.Push(type);
//	}
//
//	//m_sceneStack.Push(eScene::Title);
//
//	LoadScenes();
//	m_registeredScenes[m_sceneStack.Top()]->OnEnter();
//}

std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	if (m_stack.IsEmpty()) // OR Return menu scene??
		return nullptr;

	return m_registeredScenes[m_stack.Top()];
}

std::shared_ptr<const Scene> SceneManager::GetActiveScene() const
{
	if (m_stack.IsEmpty())
		return nullptr;

	return m_registeredScenes.at(m_stack.Top());
}



void SceneManager::Push(eScene type)
{
	if (!m_stack.IsEmpty())
	{
		m_registeredScenes[m_stack.Top()]->OnExit();
	}

	m_stack.Push(type);
	
	TransitionToScene(m_stack.Top());
	//m_registeredScenes[m_stack.Top()]->OnEnter();
}

void SceneManager::Pop()
{
	if (!m_stack.IsEmpty())
	{
		m_registeredScenes[m_stack.Top()]->OnExit();
		m_stack.Pop();

		if (m_stack.IsEmpty())
			int x = 10;

		TransitionToScene(m_stack.Top());
		//m_registeredScenes[m_stack.Top()]->OnEnter();
	}
}

void SceneManager::SwapTo(eScene type)
{
	if (!m_stack.IsEmpty())
	{
		m_registeredScenes[m_stack.Top()]->OnExit();
		m_stack.Pop();
	}

	m_stack.Push(type);
	
	TransitionToScene(type);
	//m_registeredScenes[m_stack.Top()]->OnEnter();
}

void SceneManager::Clear()
{
	for (auto& scene : m_registeredScenes)
	{
		if (scene.second)
			scene.second->OnDestroyed();
	}

	m_stack.Clear();
}

void SceneManager::TransitionToScene(eScene type)
{
	//m_stack.Push(type);
	m_registeredScenes[type]->OnEnter();

	if (m_paths.contains(type))
		LoadScene(m_paths[type]);
}

//void SceneManager::Update(float aDeltaTime)
//{
//	if (!IsEmpty()) 
//	{  
//		m_registeredScenes[m_sceneStack.Top()]->Update(aDeltaTime);
//	}
//}
//
//void SceneManager::LateUpdate(float aDeltaTime)
//{
//	if (!IsEmpty()) 
//	{
//		m_registeredScenes[m_sceneStack.Top()]->LateUpdate(aDeltaTime);
//	}
//}

//void SceneManager::Draw() const
//{
//	if (!IsEmpty()) 
//	{ 
//		const auto iterator = m_registeredScenes.find(m_sceneStack.Top());
//		if (iterator != m_registeredScenes.end())
//		{
//			// TODO;
//			// Always render the game scene if the scene is transparent?? or render all scenes in the stack...
//			if (iterator->second->IsTransparent() && m_sceneStack.Top() != eScene::Game)
//			{
//				auto gameSceneItr = m_registeredScenes.find(eScene::Game);
//				if (gameSceneItr != m_registeredScenes.end())
//				{
//					gameSceneItr->second->Draw();
//				}
//			}
//
//			iterator->second->Draw();
//		}
//	}
//}


void SceneManager::LoadScene(const std::string& aPath) 
{
	// TODO; Load entities in EntityManager, or EntityFactory?
	auto activeScene = GetActiveScene(); // take as weak pointer?
	activeScene->m_entityManager.DestroyAll();

	auto document = Hi_Engine::ParseDocument(aPath);
	for (const auto& jsonEntity : document["entities"].GetArray())
	{
		std::string id = jsonEntity["entity_id"].GetString();
		
		auto* entity = activeScene->m_entityManager.Create(id);

		if (!jsonEntity.HasMember("components_data"))
			continue;

		for (const auto& component : jsonEntity["components_data"].GetArray())
		{
			std::string type = component["type"].GetString();
			const rapidjson::Value& properties = component["properties"];

			auto componentData = EntityFactory::ParseComponent(properties);

			//activeScene->m_entityManager.GetFactory().
			//ComponetnFactory::Build()
			auto* component = activeScene->m_entityManager.GetFactory().GetCompFactory().Build(type, componentData);
			entity->AddComponent(component);
		}

		// Send event spawned? Change to initailzied?
		PostMaster::GetInstance().SendMessage({ eMessage::EntitySpawned, entity });
	}
}