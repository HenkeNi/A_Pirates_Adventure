#include "Pch.h"
#include "SceneManagerProxy.h"
#include "SceneManager.h"
#include "../DataTypes/Enumerations.h"


SceneManagerProxy::SceneManagerProxy(SceneManager& sceneManager)
	: m_sceneManager{ sceneManager }
{
}

void SceneManagerProxy::Push(eScene type)
{
	m_sceneManager.Push(type);
}

void SceneManagerProxy::Pop()
{
	m_sceneManager.Pop();
}

void SceneManagerProxy::SwapTo(eScene type)
{
	m_sceneManager.SwapTo(type);
}

void SceneManagerProxy::Clear()
{
	m_sceneManager.Clear();
}