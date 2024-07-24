#include "Pch.h"
#include "SystemFactory.h"


SystemFactory::SystemFactory(ECS& ecs)
	: m_ecs{ ecs }
{
}

System* SystemFactory::Create(const std::string& type)
{
	System* system = nullptr;

	if (m_factory.HasResource(type))
	{
		system = m_factory.Build(type);
		system->Init(&m_ecs);
	}

	return system;
}
