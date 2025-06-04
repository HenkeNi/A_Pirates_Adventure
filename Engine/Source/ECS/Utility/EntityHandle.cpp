#include "Pch.h"
#include "EntityHandle.h"
#include "World/World.h"

namespace Hi_Engine
{
	EntityHandle::EntityHandle(Entity entity, World* world)
		: m_entity{ entity }, m_world{ world }
	{
	}

	EntityHandle::~EntityHandle()
	{
	}

	void EntityHandle::SetWorld(World* world)
	{
		m_world = world;
	}

	void EntityHandle::Destroy()
	{
		m_world->DestroyEntity(m_entity);
	}

	bool EntityHandle::IsAlive() const noexcept
	{
		return m_world->IsAlive(m_entity);
	}
}