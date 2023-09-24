#pragma once
#include "../Base/ComponentBase.h"



struct BehaviorTreeComponent : public ComponentBase
{
	class BehaviorTreeNode* m_rootNode = nullptr;				// Call Execute in Update
	// current node?
};




/* Steering Behaviors */
struct WanderBehaviorComponent : public ComponentBase
{
	class WanderBehavior*	m_behavior = nullptr;
	CU::Vector2<float>		m_window;
	bool					m_isActive; // Put in base?
};

struct FlockBehaviorComponent : public ComponentBase
{
	class FlockBehavior*	m_behavior = nullptr;
	unsigned				m_flockID;
};

struct SeekBehaviorComponent : public ComponentBase
{
	class SeekBehavior*		m_behavior = nullptr;
	CU::Vector2<float>		m_taget; // Or entityID?
};

struct FleeBehaviorComponent : public ComponentBase
{
	class FleeBehavior*		m_behavior = nullptr;
};








struct StateMachineComponent : public ComponentBase
{
	class State*				m_activeState;
	std::vector<class State*>	m_states;

	// class StateMachine* m_stateMachine;
};




// Remove??
struct SteeringBehaviorComponent : public ComponentBase
{
	class SteeringBehavior* m_activeBehavior = nullptr;
	std::string				m_layer;
};












// If haveing a Steering BehaviorComponent....
// Can set what ever behavior you want...
//		Flock => flee (if player gets to close)  
// could have a flock component.,..

// With separate components (could swap components out for different behaviors...)