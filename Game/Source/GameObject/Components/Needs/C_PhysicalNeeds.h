#pragma once
#include "../Component.h"


// Combine Needs/Stats??

// Can remove or add component when needed! times when stats shouldnt be updated?! or just deactivate?
class C_PhysicalNeeds : public Component
{
public:
	void				Init(rapidjson::Value& aValue)			override;
	void				HandleMessage(eCompMessage aMessage)	override;
	void				Update(float aDeltaTime)				override;

	C_PhysicalNeeds*	Copy()									override;


private:
	std::unordered_map<std::string, float> m_needs;

	// Stat; members => mutable float => decrease rate => ..?

	// Mutable float? 
	// Decrease rate?
};
