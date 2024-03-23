#include "Pch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
	PostMaster::GetInstance().Subscribe(eMessage::TransitionToScene, this);
}

SceneManager::~SceneManager()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::TransitionToScene, this);
	Clear();
}

void SceneManager::Receive(Message& message)
{
	if (message.GetMessageType() == eMessage::TransitionToScene)
	{
		auto sceneType = std::any_cast<eScene>(message.GetData());

		if (m_scenes.contains(sceneType))
		{
			Push(sceneType);
		}
	}
}

void SceneManager::Init(std::initializer_list<eScene> scenes)
{
	for (auto& scene : m_scenes)
		scene.second->OnCreated();

	for (const auto scene : scenes)
		m_stack.Push(scene);


	// TODO: do elsewhere?
	m_paths.insert({ eScene::Menu, "../Game/Assets/Json/Scenes/MainMenu.json" });
	LoadEntities(m_paths.at(eScene::Menu)); // TEST
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
//	m_scenes[m_sceneStack.Top()]->OnEnter();
//}

std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	if (m_stack.IsEmpty()) // OR Return menu scene??
		return nullptr;

	return m_scenes[m_stack.Top()];
}

std::shared_ptr<const Scene> SceneManager::GetActiveScene() const
{
	if (m_stack.IsEmpty())
		return nullptr;

	return m_scenes.at(m_stack.Top());
}



void SceneManager::Push(eScene type)
{
	if (!m_stack.IsEmpty())
	{
		m_scenes[m_stack.Top()]->OnExit();
	}

	m_stack.Push(type);
	m_scenes[m_stack.Top()]->OnEnter();
}

void SceneManager::Pop()
{
	if (!m_stack.IsEmpty())
	{
		m_scenes[m_stack.Top()]->OnExit();
		m_stack.Pop();

		m_scenes[m_stack.Top()]->OnEnter();
	}
}

void SceneManager::SwapTo(eScene type)
{
	if (!m_stack.IsEmpty())
	{
		m_scenes[m_stack.Top()]->OnExit();
		m_stack.Pop();
	}

	m_stack.Push(type);
	m_scenes[m_stack.Top()]->OnEnter();
}

void SceneManager::Clear()
{
	for (auto& scene : m_scenes)
	{
		if (scene.second)
			scene.second->OnDestroyed();
	}

	m_stack.Clear();
}

void SceneManager::TransitionToScene(eScene type)
{
	LoadEntities(m_paths[type]);
}

//void SceneManager::Update(float aDeltaTime)
//{
//	if (!IsEmpty()) 
//	{  
//		m_scenes[m_sceneStack.Top()]->Update(aDeltaTime);
//	}
//}
//
//void SceneManager::LateUpdate(float aDeltaTime)
//{
//	if (!IsEmpty()) 
//	{
//		m_scenes[m_sceneStack.Top()]->LateUpdate(aDeltaTime);
//	}
//}

//void SceneManager::Draw() const
//{
//	if (!IsEmpty()) 
//	{ 
//		const auto iterator = m_scenes.find(m_sceneStack.Top());
//		if (iterator != m_scenes.end())
//		{
//			// TODO;
//			// Always render the game scene if the scene is transparent?? or render all scenes in the stack...
//			if (iterator->second->IsTransparent() && m_sceneStack.Top() != eScene::Game)
//			{
//				auto gameSceneItr = m_scenes.find(eScene::Game);
//				if (gameSceneItr != m_scenes.end())
//				{
//					gameSceneItr->second->Draw();
//				}
//			}
//
//			iterator->second->Draw();
//		}
//	}
//}


void SceneManager::LoadEntities(const std::string& aPath)
{
	auto document = CommonUtilities::ParseDocument(aPath);

	for (const auto& entity : document["entities"].GetArray())
	{
		std::string id = entity["entity_id"].GetString();

		// Get entity manager from current scene? make scene manager a friend class?

		int x = 10;
		x += 10;
	}


	// Store data

	// TODO; for each entity in list => create entity, for each component in entity => ComponentIntializer?
	// pass in data 

	// Call the component-initialize?





}

