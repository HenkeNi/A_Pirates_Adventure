#include "Pch.h"
#include "SceneManager.h"
#include "Scene.h"


SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	Clear();
}

void SceneManager::Init(int aSceneSet)
{
	for (int i = 1; i < (int)eScene::Count; i <<= 1)
	{
		auto type = static_cast<eScene>(i);

		if (aSceneSet & (int)type)
			m_sceneStack.Push(type);
	}

	LoadScenes();
	m_scenes[m_sceneStack.Top()]->OnEnter();
}

void SceneManager::Register(std::unique_ptr<Scene> aScene, eScene aType)
{
	assert(aScene != nullptr);

	m_scenes.insert_or_assign(aType, std::move(aScene));
	m_scenes[aType]->OnCreated();
}

void SceneManager::Push(eScene aType)
{
	if (!IsEmpty())
	{
		m_scenes[m_sceneStack.Top()]->OnExit();
	}

	m_sceneStack.Push(aType);
	m_scenes[m_sceneStack.Top()]->OnEnter();
}

void SceneManager::Pop()
{
	if (!IsEmpty())
	{
		m_scenes[m_sceneStack.Top()]->OnExit();
		m_sceneStack.Pop();

		m_scenes[m_sceneStack.Top()]->OnEnter();
	}
}

void SceneManager::SwapTo(eScene aType)
{
	if (!IsEmpty())
	{
		m_scenes[m_sceneStack.Top()]->OnExit();
		m_sceneStack.Pop();
	}

	m_sceneStack.Push(aType);
	m_scenes[m_sceneStack.Top()]->OnEnter();
}

void SceneManager::Clear()
{
	for (auto& scene : m_scenes)
	{
		if (scene.second)
			scene.second->OnDestroyed();
	}

	m_sceneStack.Clear();
}

bool SceneManager::IsEmpty() const
{
	return m_sceneStack.IsEmpty();
}

void SceneManager::Update(float aDeltaTime)
{
	if (!IsEmpty()) 
	{  
		m_scenes[m_sceneStack.Top()]->Update(aDeltaTime);
	}
}

void SceneManager::LateUpdate(float aDeltaTime)
{
	if (!IsEmpty()) 
	{
		m_scenes[m_sceneStack.Top()]->LateUpdate(aDeltaTime);
	}
}

void SceneManager::Draw() const
{
	if (!IsEmpty()) 
	{ 
		const auto iterator = m_scenes.find(m_sceneStack.Top());
		if (iterator != m_scenes.end())
		{
			// TODO;
			// Always render the game scene if the scene is transparent?? or render all scenes in the stack...
			if (iterator->second->IsTransparent() && m_sceneStack.Top() != eScene::Game)
			{
				auto gameSceneItr = m_scenes.find(eScene::Game);
				if (gameSceneItr != m_scenes.end())
				{
					gameSceneItr->second->Draw();
				}
			}

			iterator->second->Draw();
		}
	}
}

void SceneManager::LoadScenes()
{
	// TODO; rework... (move elsewhere??) -> read scene stack from json??
	std::ifstream ifs{ "../Bin/Assets/Json/Scenes/Scenes.json" };
	std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

	rapidjson::Document document;
	assert(!document.Parse(content.c_str()).HasParseError() && "Failed to Parse");
	// Put above part in engine??

	int sceneIndex = 0;
	for (auto& scene : document["scenes"].GetArray())
	{
		std::string type = scene["type"].GetString();
		int id = scene["id"].GetInt();

		auto Type = (eScene)id;

		//if (m_scenes[eScene(id)])	//F IX::::
			// m_scenes[eScene(id)]->Init(scene);
	}
}