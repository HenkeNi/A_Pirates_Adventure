#pragma once
#include "Systems/SystemBuilder.h"
//#include <../Hi_Engine.h> //?
#include <../../Engine/Source/Utility/DataStructures/Non-Linear/Factory/Factory.hpp>

class System;

namespace // ECS
{
	//using Systems = std::vector<std::unique_ptr<System>>;
}

//namespace Hi_Engine
//{
//	template <typename BuilderType, typename ReturnType>
//	class Factory<BuilderType, ReturnType>;
//}

class EntityManager;
class SystemBuilder;

class SystemManager // TODO: listen for scene transition (fetch entity manager)?
{
public:
	SystemManager();
	~SystemManager();

	template <typename T>
	void Register(const std::string& type);
	void Create(const std::string& identifier);

	void Init(EntityManager* entityManager); // ECS instead?
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw()	const;
	
	void Clear();

private:
	Hi_Engine::Factory<SystemBuilder, System> m_factory;
	std::vector<System*> m_systems;	// Set?
};

template <typename T>
inline void SystemManager::Register(const std::string& type)
{
	m_factory.RegisterBuilder(type, new ConcreteSystemBuilder<T>{});
}
