#pragma once
#include "Systems/SystemBuilder.h"
#include <../../Engine/Source/Utility/DataStructures/Non-Linear/Factory/Factory.hpp>

class ECS;

class SystemFactory
{
public:
	SystemFactory(ECS& ecs);

	template <typename T>
	void Register(const std::string& type);

	System* Create(const std::string& type);

private:
	Hi_Engine::Factory<SystemBuilder, System> m_factory;

	ECS& m_ecs;
};

template <typename T>
inline void SystemFactory::Register(const std::string& type)
{
	m_factory.RegisterBuilder(type, new ConcreteSystemBuilder<T>{});
}