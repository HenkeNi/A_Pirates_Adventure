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
#include "../GameObject/Components/Rendering/Camera/C_Camera.h"
#include "../GameObject/Components/Rendering/Sprite/C_Sprite.h"
#include "../GameObject/Components/Controllers/C_PlayerController.h"
#include "../GameObject/Components/Physics/Movement/C_Movement.h"
#include "../GameObject/Components/AI/Behavior/C_Behavior.h"


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

	CU::Vector3<float> playerPos = { (float)Random::InRange(2, 62), 0.3f, (float)Random::InRange(2, 62) };
	player.GetComponent<C_Transform>()->SetPosition(playerPos);
	player.GetComponent<C_Sprite>()->SetMaterial({ 
		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("pirate_idle"), 
		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });
	m_objectManager.AddObject(std::move(player));

	id = m_objectManager.GetAllObjects().back().GetID();
	m_objectManager.GetAllObjects()[0].GetComponent<C_Camera>()->SetTarget(&m_objectManager.GetAllObjects()[1]);



	for (int i = 0; i < 70; ++i)
	{
		GameObject tree;
		tree.AddComponent(new C_Transform);
		tree.AddComponent(new C_Sprite);
		tree.GetComponent<C_Sprite>()->SetMaterial({ 
			&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("palm_01"),
			&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });
		tree.GetComponent<C_Transform>()->SetPosition({ (float)Random::InRange(2, 62), 0.45f, (float)Random::InRange(2, 62) });
		tree.GetComponent<C_Transform>()->SetScale({ 1.f, 1.35f, 1.f });

		m_objectManager.AddObject(std::move(tree));
	}



	for (int i = 0; i < 115; ++i)
	{
		GameObject grass;
		grass.AddComponent(new C_Transform);
		grass.AddComponent(new C_Sprite);
		grass.GetComponent<C_Sprite>()->SetMaterial({
			&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("grass"),
			&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });

		CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.25f, (float)Random::InRange(2, 62) };
		grass.GetComponent<C_Transform>()->SetPosition({ position });
		grass.GetComponent<C_Transform>()->SetScale({ 0.75f, 0.75f, 0.75f });
		m_objectManager.AddObject(std::move(grass));

		GameObject smallGrass;
		smallGrass.AddComponent(new C_Transform);
		smallGrass.AddComponent(new C_Sprite);
		smallGrass.GetComponent<C_Sprite>()->SetMaterial({
			&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("grass"),
			&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });
		smallGrass.GetComponent<C_Transform>()->SetPosition({ position.x, position.y - 0.1f, position.z + 0.1f });
		smallGrass.GetComponent<C_Transform>()->SetScale({ 0.5f, 0.5f, 0.5f });
		m_objectManager.AddObject(std::move(smallGrass));
	}





	GameObject crab;
	crab.AddComponent(new C_Sprite);
	crab.AddComponent(new C_Transform);
	crab.AddComponent(new C_Movement);
	crab.AddComponent(new C_Behavior);
	crab.GetComponent<C_Sprite>()->SetMaterial({
		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("crab"),
		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });
	crab.GetComponent<C_Transform>()->SetPosition({ playerPos.x, 0.1f, playerPos.z });
	crab.GetComponent<C_Transform>()->SetScale({0.4f, 0.4f, 0.4f});
	crab.GetComponent<C_Movement>()->SetMovementSpeed(0.006f);
	m_objectManager.AddObject(std::move(crab));






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