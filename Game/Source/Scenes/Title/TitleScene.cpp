#include "Pch.h"
#include "TitleScene.h"
//#include "../Factories/SceneFactory.h"

#define DEFAULT_DURATION 2.3f 


TitleScene::TitleScene(SceneManagerProxy aProxy)
	: Scene{ aProxy }, m_duration{ DEFAULT_DURATION }, m_elapsedTime{ 0.f } 
{
	Hi_Engine::Dispatcher::GetInstance().Subscribe(this);
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init(rapidjson::Value& aValue)
{

}

void TitleScene::HandleEvent(Hi_Engine::KeyEvent& anEvent)
{
	if (anEvent.GetKeyCode() == 1)
	{
		static int i = 10;
		i += 10;
	}
}
#include "../GameObject/Components/Transform/C_Transform.h"

void TitleScene::Update(float aDeltaTime)
{
	m_elapsedTime += aDeltaTime;

	for (auto& object : m_objectManager.GetAllObjects())
		object.Update(aDeltaTime);


	//m_objectManager.GetAllObjects()[0].GetComponent<C_Transform>()->MoveBy({ 0.00000000000000000000000000000001f, 0.f, 0.f });

}

void TitleScene::LateUpdate(float aDeltaTime) {}

void TitleScene::Draw() const
{
	m_map.Draw();

	for (auto& object : m_objectManager.GetAllObjects())
		object.Draw();
}

#include "Core/Resources/ResourceHolder.hpp"
#include "../GameObject/Components/Sprite/C_Sprite.h"
#include "../GameObject/Components/Camera/C_Camera.h"
#include "../GameObject/Components/Controllers/C_PlayerController.h"
#include "../GameObject/Components/Movement/C_Movement.h"

//#include "Core/Rendering/Texture/Texture2D.h"
void TitleScene::OnCreated()
{


	// m_sceneObjects = SceneFactory::GetInstance().CreateFromBlueprint("Title");

	GameObject camera;
	camera.CreateComponent<C_Camera>();
	//camera.GetComponent<C_Camera>();
	camera.GetComponent<C_Transform>()->SetPosition({ 0.f, 0.f, 0.f});

	m_objectManager.AddObject(camera);
	
	//m_sceneObjects.push_back(camera);



	GameObject player;
	auto* sprite = player.CreateComponent<C_Sprite>();
	auto& texture = Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("pirate");
	sprite->SetTexture(&texture);
	player.CreateComponent<C_PlayerController>();
	player.CreateComponent<C_Movement>();
	//player.GetComponent<C_Transform>()->SetZPosition(-100);
	player.GetComponent<C_Transform>()->SetPosition({-0.4f, 0.2f, 0.2f });

	m_objectManager.AddObject(player);


	m_objectManager.GetAllObjects()[0].GetComponent<C_Camera>()->SetTarget(&m_objectManager.GetAllObjects().back());




	/*GameObject background;
	auto* transform = background.GetComponent<C_Transform>();
	transform->SetPosition({ 0, 0, 0 });
	auto* sprite = background.CreateComponent<C_Sprite>();
	auto& texture = Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("title_screen");
	sprite->SetTexture(&texture);*/
	//m_objectManager.AddObject(background);
	
	
	m_map.Init(); // REMOVE LATER...
}

void TitleScene::OnEnter()
{
	// Request timer notification

	m_elapsedTime = 0.f;

	for (auto& object : m_objectManager.GetAllObjects())
		object.Activate();
}

void TitleScene::OnExit()
{
	for (auto& object : m_objectManager.GetAllObjects())
		object.Deactivate();
}