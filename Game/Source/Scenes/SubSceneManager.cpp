#include "Pch.h"
#include "SubSceneManager.h"

void SubSceneManager::Clear()
{
	m_subScenes.clear();
}

std::weak_ptr<const Scene> SubSceneManager::GetActive() const
{
	return m_subScenes.at(m_activeScene);
}

std::weak_ptr<Scene> SubSceneManager::GetActive()
{
	// Const cast here? or not possible with weak?
	return m_subScenes.at(m_activeScene);
}
