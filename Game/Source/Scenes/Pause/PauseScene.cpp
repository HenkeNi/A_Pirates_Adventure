#include "Pch.h"
#include "PauseScene.h"


PauseScene::PauseScene(SceneManagerProxy aProxy)
	: Scene{ aProxy }
{
}

PauseScene::~PauseScene()
{
}

void PauseScene::Update(float aDeltaTime)
{
}

void PauseScene::LateUpdate(float aDeltaTime)
{
}

void PauseScene::Draw() const
{
}

void PauseScene::OnCreated()
{
	m_callbacks.push_back([&]() { m_sceneManager.Pop(); });
	m_callbacks.push_back([&]() { m_sceneManager.SwapTo(eSceneType::Menu); });
}

void PauseScene::OnEnter()
{
}

void PauseScene::OnExit()
{
}
