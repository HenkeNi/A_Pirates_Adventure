#include "Pch.h"
#include "SceneManager.h"
#include "../Scenes/Scene.h"
#include "../Scenes/Scenes.h"


SceneManager::SceneManager()
	: m_scenes{ nullptr }
{
}

SceneManager::~SceneManager()
{
	Clear();
}

void SceneManager::Init(std::initializer_list<eSceneType> aList)
{
	for (auto& sceneType : aList)
		m_sceneStack.Push(sceneType);

	auto& test = m_scenes;

	// TODO; rework... (move elsewhere??) -> read scene stack from json??
	std::ifstream ifs{ "../Bin/Assets/Json/Scenes/Scenes.json" };
	std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

	rapidjson::Document document;
	assert(!document.Parse(content.c_str()).HasParseError() && "Failed to Parse");

	int sceneIndex = 0;
	for (auto& scene : document["scenes"].GetArray())
	{
		auto type = scene["type"].GetString();
		m_scenes[sceneIndex++]->Init(scene);

		// scene have an identifier?
	}




	m_scenes[(int)m_sceneStack.Top()]->OnEnter();
}

void SceneManager::Register(std::unique_ptr<Scene> aScene, eSceneType aType)
{
	assert(aScene != nullptr);

	int index = (int)aType;

	m_scenes[index] = std::move(aScene);
	m_scenes[index]->OnCreated();
}

void SceneManager::Push(eSceneType aType)
{
	if (!IsEmpty())
	{
		m_scenes[(int)m_sceneStack.Top()]->OnExit();
	}

	m_sceneStack.Push(aType);
	m_scenes[(int)m_sceneStack.Top()]->OnEnter();
}

void SceneManager::Pop()
{
	if (!IsEmpty())
	{
		m_scenes[(int)m_sceneStack.Top()]->OnExit();
		m_sceneStack.Pop();

		m_scenes[(int)m_sceneStack.Top()]->OnEnter();
	}
}

void SceneManager::SwapTo(eSceneType aType)
{
	if (!IsEmpty())
	{
		m_scenes[(int)m_sceneStack.Top()]->OnExit();
		m_sceneStack.Pop();
	}

	m_sceneStack.Push(aType);
	m_scenes[(int)m_sceneStack.Top()]->OnEnter();
}

void SceneManager::Update(float aDeltaTime)
{
	if (!IsEmpty()) 
	{  
		int index = (int)m_sceneStack.Top();
		m_scenes[index]->Update(aDeltaTime);	
	}
}

void SceneManager::LateUpdate(float aDeltaTime)
{
	if (!IsEmpty()) 
	{
		int index = (int)m_sceneStack.Top();
		m_scenes[index]->LateUpdate(aDeltaTime);
	}
}

void SceneManager::Draw() const
{
	if (!IsEmpty()) 
	{ 
		int index = (int)m_sceneStack.Top();

		if (m_scenes[index]->IsTransparent() && m_scenes[index - 1])  
			m_scenes[index - 1]->Draw();

		m_scenes[index]->Draw();
	}
}

bool SceneManager::IsEmpty() const
{
	return m_sceneStack.IsEmpty();
}

void SceneManager::Clear()
{
	for (auto& scene : m_scenes)
	{
		if (scene)
			scene->OnDestroyed();
	}

	m_sceneStack.Clear();
}