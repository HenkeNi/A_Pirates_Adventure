	 #pragma once
#include "Base/System.h"


namespace
{
	using Systems_t = std::vector<std::unique_ptr<System>>;
	// using SystemFactory = CU::Factory<SystemBuilder, System> m_systemFactory;
}

class EntityManager;

class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	void Init(EntityManager* aManager);
	void Update(float aDeltaTime);
	void LateUpdate(float aDeltaTime);
	void Draw()	const;

	void Register(std::unique_ptr<System> aSystem);
	void Clear();

private:
	Systems_t		m_systems; // Separate between registed systems and active systems??
	// SystemFactory	m_systemFactory; -> scene decides what systems to add (OnEnter) => clears on Exit?
};