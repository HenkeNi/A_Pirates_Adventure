#include "Pch.h"
#include "PauseScene.h"
#include "Systems/SystemManager.h"


PauseScene::PauseScene(SharedContext context)
	: Scene{ context }
{
}

PauseScene::~PauseScene()
{
}

void PauseScene::Update(float deltaTime)
{
}

void PauseScene::LateUpdate(float deltaTime)
{
}

void PauseScene::Draw() const
{
}

void PauseScene::OnCreated()
{
	//m_callbacks.push_back([&]() { m_sceneManager.Pop(); });
	//m_callbacks.push_back([&]() { m_sceneManager.SwapTo(eScene::Menu); });
}

void PauseScene::OnEnter()
{
}

void PauseScene::OnExit()
{
}
