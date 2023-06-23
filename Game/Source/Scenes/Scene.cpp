#include "Pch.h"
#include "Scene.h"


Scene::Scene(SharedContext aContext)
	: m_sharedContext{ aContext }
{
}

bool Scene::IsTransparent() const
{
	return false;
}