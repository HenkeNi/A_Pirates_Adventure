#include "Pch.h"
#include "Scene.h"

SystemManager Scene::s_systemManager;

Scene::Scene(SharedContext aContext)
	: m_sharedContext{ aContext }
{
}

bool Scene::IsTransparent() const
{
	return false;
}