#include "Pch.h"
#include "Scene.h"


Scene::Scene(ECS& ecs)
	: m_ecs{ ecs }
{
}

bool Scene::IsTransparent() const
{
	return false;
}