#pragma once
#include "../Base/ComponentBase.h"



struct BehaviorTreeComponent : public ComponentBase
{
	class BehaviorTreeNode* RootNode = nullptr;				// Call Execute in Update
	// current node?
};




/* Steering Behaviors */
struct WanderBehaviorComponent : public ComponentBase
{
	class WanderBehavior*	Behavior = nullptr;
	CU::Vector2<float>		Window;
	bool					IsActive; // Put in base?
};

struct FlockBehaviorComponent : public ComponentBase
{
	class FlockBehavior*	Behavior = nullptr;
	unsigned				FlockID;
};

struct SeekBehaviorComponent : public ComponentBase
{
	class SeekBehavior*		Behavior = nullptr;
	CU::Vector2<float>		Target; // Or entityID?
};

struct FleeBehaviorComponent : public ComponentBase
{
	class FleeBehavior*		Behavior = nullptr;
};








struct StateMachineComponent : public ComponentBase
{
	class State*				ActiveState;
	std::vector<class State*>	States;

	// class StateMachine* m_stateMachine;
};




// Remove??
struct SteeringBehaviorComponent : public ComponentBase
{
	class SteeringBehavior* ActiveBehavior = nullptr;
	std::string				Layer;
};












// If haveing a Steering BehaviorComponent....
// Can set what ever behavior you want...
//		Flock => flee (if player gets to close)  
// could have a flock component.,..

// With separate components (could swap components out for different behaviors...)