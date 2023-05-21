#include "Pch.h"
#include "GameScene.h"


GameScene::GameScene(SceneManagerProxy aProxy)
	: Scene{ aProxy }
{
}

GameScene::~GameScene()
{
}

void GameScene::Init(rapidjson::Value& aValue)
{
	auto type = aValue["type"].GetString();

	static int ax = 10;

}

void GameScene::Update(float aDeltaTime)
{
	for (auto& object : m_objectManager.GetAllObjects())
		object.Update(aDeltaTime);
}

void GameScene::LateUpdate(float aDeltaTime)
{
	for (auto& object : m_objectManager.GetAllObjects())
		object.LateUpdate(aDeltaTime);
}

void GameScene::Draw() const
{
	m_map.Draw();

	for (auto& object : m_objectManager.GetAllObjects())
		object.Draw();
}

#include "Core/Resources/ResourceHolder.hpp"
#include "../GameObject/Components/Core/Transform/C_Transform.h"
#include "../GameObject/Components/Core/Camera/C_Camera.h"
#include "../GameObject/Components/Rendering/Sprite/C_Sprite.h"
#include "../GameObject/Components/Gameplay/Controllers/C_PlayerController.h"
#include "../GameObject/Components/Gameplay/Movement/C_Movement.h"


void GameScene::OnCreated()
{
	
}

void GameScene::OnEnter()
{
	m_map.Init();

	GameObject camera;
	camera.AddComponent(new C_Camera);
	camera.AddComponent(new C_Transform);
	camera.GetComponent<C_Transform>()->SetPosition({ 0.f, 0.f, 2.f });
	m_objectManager.AddObject(std::move(camera));

	int id = m_objectManager.GetAllObjects().begin()->GetID();

	GameObject player;
	player.AddComponent(new C_Sprite);
	player.AddComponent(new C_Transform);
	player.AddComponent(new C_Movement);
	player.AddComponent(new C_PlayerController);

	auto& texture = Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("pirate");
	auto& shader = Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard");
	player.GetComponent<C_Sprite>()->SetMaterial({ &texture, &shader });
	player.GetComponent<C_Transform>()->SetPosition({ 0.f, 0.f, 0.f });
	m_objectManager.AddObject(std::move(player));

	id = m_objectManager.GetAllObjects().back().GetID();


	m_objectManager.GetAllObjects()[0].GetComponent<C_Camera>()->SetTarget(&m_objectManager.GetAllObjects().back());

	//GameObject inputListener;
	//inputListener.CreateComponent<C_


	/*GameObject background;
	auto* transform = background.GetComponent<C_Transform>();
	transform->SetPosition({ 0, 0, 0 });
	auto* sprite = background.CreateComponent<C_Sprite>();
	auto& texture = Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("title_screen");
	sprite->SetTexture(&texture);*/
	//m_objectManager.AddObject(background);






	// load components?

	for (auto& object : m_objectManager.GetAllObjects())
		object.Activate();
}

void GameScene::OnExit()
{
	for (auto& object : m_objectManager.GetAllObjects())
		object.Deactivate();

}