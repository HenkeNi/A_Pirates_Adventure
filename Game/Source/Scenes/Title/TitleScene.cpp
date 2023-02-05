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

void TitleScene::OnCreated()
{
	m_sceneObjects = SceneFactory::GetInstance().Create("Title");
}

void TitleScene::OnEnter()
{
	// Request timer notification
}

void TitleScene::OnExit()
{
}
