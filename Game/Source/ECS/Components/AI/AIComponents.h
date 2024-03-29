#pragma once
#include "../Base/Component.h"

namespace CU = CommonUtilities;

//#################### AI Components //####################//

struct BlackboardComponent : public Component
{
	inline static CU::Vector2<float> PlayerPosition; // use std::any instead?
};

struct StateMachineComponent : public Component
{
	class State*				ActiveState;
	std::vector<class State*>	States;
};

struct BehaviorTreeComponent : public Component
{
	class BehaviorTreeNode* RootNode = nullptr;
	// current node?
};

// TODO; Maybe only need SteeringBehaviorComponent (or have separate)?
struct WanderBehaviorComponent : public Component
{
	class WanderBehavior*	Behavior = nullptr;
};

struct FlockBehaviorComponent : public Component
{
	class FlockBehavior*	Behavior = nullptr;
	unsigned				FlockID;
};

struct SeekBehaviorComponent : public Component
{
	class SeekBehavior*		Behavior = nullptr;
	CU::Vector2<float>		Target;
};

struct FleeBehaviorComponent : public Component
{
	class FleeBehavior*		Behavior = nullptr;
};

struct SteeringBehaviorComponent : public Component
{
	class SteeringBehavior* ActiveBehavior = nullptr;
	std::string				Layer;
};