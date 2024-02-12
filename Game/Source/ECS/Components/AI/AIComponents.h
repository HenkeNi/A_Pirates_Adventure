#pragma once
#include "../Base/Component.h"

namespace CU = CommonUtilities;

/* - Blackboard - */
struct BlackboardComponent : public Component
{
	inline static CU::Vector2<float> PlayerPosition; // use std::any instead?
};

/* - State Machine- */
struct StateMachineComponent : public Component
{
	class State*				ActiveState;
	std::vector<class State*>	States;

	// class StateMachine* m_stateMachine;
};


/* - Behavior Tree - */
struct BehaviorTreeComponent : public Component
{
	class BehaviorTreeNode* RootNode = nullptr;				// Call Execute in Update
	// current node?
};


/* - Steering Behaviors - */
struct WanderBehaviorComponent : public Component
{
	class WanderBehavior*	Behavior = nullptr;
	CU::Vector2<float>		Window;
	bool					IsActive; // Put in base?
};

struct FlockBehaviorComponent : public Component
{
	class FlockBehavior*	Behavior = nullptr;
	unsigned				FlockID;
};

struct SeekBehaviorComponent : public Component
{
	class SeekBehavior*		Behavior = nullptr;
	CU::Vector2<float>		Target; // Or entityID?
};

struct FleeBehaviorComponent : public Component
{
	class FleeBehavior*		Behavior = nullptr;
};







// Remove??
struct SteeringBehaviorComponent : public Component
{
	class SteeringBehavior* ActiveBehavior = nullptr;
	std::string				Layer;
};




struct AIController : public Component
{

};


//struct EnemyControllerComponent : ComponentBase
//{
//	// AI => Behavior tree..
//};
//
//
//// Animal Controller?	(steering behavuir?)







// If haveing a Steering BehaviorComponent....
// Can set what ever behavior you want...
//		Flock => flee (if player gets to close)  
// could have a flock component.,..

// With separate components (could swap components out for different behaviors...)