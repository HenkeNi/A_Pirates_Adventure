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

void TitleScene::Update(float aDeltaTime)
{
	m_elapsedTime += aDeltaTime;

	for (auto& object : m_objectManager.GetAllObjects())
		object.Update(aDeltaTime);
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
#include "../GameObject/Components/Transform/C_Transform.h"
#include "../GameObject/Components/Camera/C_Camera.h"
//#include "Core/Rendering/Texture/Texture2D.h"
void TitleScene::OnCreated()
{


	// m_sceneObjects = SceneFactory::GetInstance().CreateFromBlueprint("Title");

	GameObject camera;
	camera.CreateComponent<C_Camera>();
	camera.GetComponent<C_Camera>();
	camera.GetComponent<C_Transform>()->SetPosition({ 0.f, 0.f, 0.f});

	m_objectManager.AddObject(camera);
	
	//m_sceneObjects.push_back(camera);


	GameObject background;
	auto* transform = background.GetComponent<C_Transform>();
	auto* sprite = background.CreateComponent<C_Sprite>();
	auto& texture = Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("title_screen");
	sprite->SetTexture(&texture);


	m_objectManager.AddObject(background);
	// m_sceneObjects.push_back(background);
	
	
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

void TitleScene::HandleEvent(Hi_Engine::KeyEvent& anEvent)
{
	if (anEvent.GetKeyCode() == 1)
	{
		static int i = 10;
		i += 10;
	}
}