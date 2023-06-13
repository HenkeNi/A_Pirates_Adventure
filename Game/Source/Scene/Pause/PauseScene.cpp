#include "Pch.h"
#include "PauseScene.h"


PauseScene::PauseScene(SharedContext aContext)
	: Scene{ aContext }
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
	//m_callbacks.push_back([&]() { m_sceneManager.Pop(); });
	//m_callbacks.push_back([&]() { m_sceneManager.SwapTo(eScene::Menu); });
}

void PauseScene::OnEnter()
{
}

void PauseScene::OnExit()
{
}
