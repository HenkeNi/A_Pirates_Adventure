#include "Pch.h"
#include "Scene.h"


namespace Hi_Engine
{
	void Scene::Update(float deltaTime)
	{
		m_systemManager.Update(deltaTime);
		OnUpdate(deltaTime);
	}

	bool Scene::IsTransparent() const
	{
		return false;
	}
}