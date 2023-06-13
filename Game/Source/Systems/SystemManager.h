#pragma once
#include "Base/System.h"


namespace
{
	using Systems_t = std::vector<std::unique_ptr<System>>;
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
	void Draw() const;

	void Register(std::unique_ptr<System> aSystem);
	void Clear();


private:

	Systems_t m_systems; // Separate between registed systems and active systems??

	// system factory?? -> scene decides what systems to add (OnEnter) => clears on Exit?
};

// Maybe; Have base class RenderSystem, and UpdateSystem?

/*
* 



Store ID for relevant entities??
	->

// instead of Entities or EntityManager => a Wrapper class?? and store ID
	
	GameWorld? Contains pointer (or the actual implementation) Of EntityManager, and Systems

*/




/*
	- Movement System
	- Collision System
	- Animation System
	- Combat System
	- AI System
	- Player system

	CameraSystem
	Input System?
*/