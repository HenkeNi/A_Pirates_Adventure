#pragma once
#include "Base/System.h"
#include "Systems/SystemBuilder.h"
//#include <../Source/Utility/DataStructures/Linear/Dynamic/Stack/Stack.hpp>

//namespace ECS
namespace
{
	using Systems = std::vector<std::unique_ptr<System>>;
	// using SystemFactory = CU::Factory<SystemBuilder, System> m_systemFactory;
}

class EntityManager;

class SystemManager // TODO: listen for scene transition (fetch entity manager)?
{
public:
	SystemManager();
	~SystemManager();

	template <typename T>
	void Register();

	template <typename T>
	void RegisterSystemBuilder(const std::string& type);

	void Create(const std::string& system);

	void Init(EntityManager* entityManager);
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw()	const;
	
	void Clear();

private:
	Systems m_systems; // Separate between registed systems and active systems??
	//Hi_Engine::Factory<SystemBuilder, System> m_systemFactory;
	// SystemFactory	m_systemFactory; -> scene decides what systems to add (OnEnter) => clears on Exit?

};

template<typename T>
inline void SystemManager::Register()
{
	m_systems.emplace_back(std::make_unique<T>());
}

template<typename T>
inline void SystemManager::RegisterSystemBuilder(const std::string& type)
{
	//m_systemFactory.RegisterBuilder(type, new ConcreteSystemBuilder<T>{});
}
