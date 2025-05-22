#include "Pch.h"
#include "Scene.h"


namespace Hi_Engine
{
	void Scene::Update(float deltaTime)
	{
		m_world.Update(deltaTime);
		OnUpdate(deltaTime);
	}

	bool Scene::IsTransparent() const
	{
		return false;
	}
}