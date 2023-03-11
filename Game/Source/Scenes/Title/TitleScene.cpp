#include "Pch.h"
#include "TitleScene.h"
#include "../Factories/SceneFactory.h"

#define DEFAULT_DURATION 2.3f 


TitleScene::TitleScene(SceneManagerProxy aProxy)
	: Scene{ aProxy }, m_duration{ DEFAULT_DURATION } //, m_elapsedTime{ 0.f }
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float aDeltaTime)
{
	for (auto& object : m_sceneObjects)
		object.Update(aDeltaTime);
}

void TitleScene::LateUpdate(float aDeltaTime) {}

void TitleScene::Draw() const
{
	for (auto& object : m_sceneObjects)
		object.Draw();
}

#include "Core/Resources/ResourceHolder.hpp"
#include "../GameObject/Components/Sprite/C_Sprite.h"
//#include "Core/Rendering/Texture/Texture2D.h"
void TitleScene::OnCreated()
{
	m_sceneObjects = SceneFactory::GetInstance().Create("Title");


	GameObject background;
	auto* Sprite = background.CreateComponent<C_Sprite>();
	auto& Texture = Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("title_screen");
	Sprite->SetTexture(&Texture);

	m_sceneObjects.push_back(background);
}

void TitleScene::OnEnter()
{
	// Request timer notification

	for (auto& object : m_sceneObjects)
		object.Activate();
}

void TitleScene::OnExit()
{
	for (auto& object : m_sceneObjects)
		object.Deactivate();
}
