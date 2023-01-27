#include "Pch.h"
#include "Scene.h"


Scene::Scene(SceneManagerProxy aProxy)
	: m_sceneManager{ aProxy }
{
}

bool Scene::IsTransparent() const
{
	return false;
}