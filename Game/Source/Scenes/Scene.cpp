#include "Pch.h"
#include "Scene.h"


Scene::Scene(SharedContext context)
	: m_sharedContext{ context }
{
}

bool Scene::IsTransparent() const
{
	return false;
}