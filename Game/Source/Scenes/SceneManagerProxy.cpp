#include "Pch.h"
#include "SceneManagerProxy.h"
#include "SceneManager.h"


SceneManagerProxy::SceneManagerProxy(SceneManager& aSceneManager)
	: m_sceneManager{ aSceneManager }
{
}

void SceneManagerProxy::Push(eScene aType)
{
	m_sceneManager.Push(aType);
}

void SceneManagerProxy::Pop()
{
	m_sceneManager.Pop();
}

void SceneManagerProxy::SwapTo(eScene aType)
{
	m_sceneManager.SwapTo(aType);
}

void SceneManagerProxy::Clear()
{
	m_sceneManager.Clear();
}