#pragma once
#include "../../Base/System.h"

// rename CharacterAttributeSystem?	
// or just AttributeSystem??

// Remmake to HealthSystem => listens to attacks, decreases health (fetches armor, and attributes)... 

class StatSystem : public System, public Subscriber
{
public:
	StatSystem();
	~StatSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

private:
	// std::vector<unsigned> m_entitiesToRemove;
};