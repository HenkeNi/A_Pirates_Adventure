	 #pragma once
#include "Base/System.h"

namespace ECS
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

	void Init(EntityManager* entityManager);
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw()	const;

	void Register(std::unique_ptr<System> system);
	void Clear();

private:
	ECS::Systems m_systems; // Separate between registed systems and active systems??
	// SystemFactory	m_systemFactory; -> scene decides what systems to add (OnEnter) => clears on Exit?
};