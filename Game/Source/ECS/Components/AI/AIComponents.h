#pragma once
#include "../Base/Component.h"

namespace CU = CommonUtilities;

//#################### AI Components ####################//
struct BlackboardComponent : public Component
{
	inline static CU::Vector2<float> PlayerPosition; // Todo; use std::any instead? store player ID AND vector of crew IDs??
};

struct BehaviorTreeComponent : public Component
{
	class BehaviorTreeNode* RootNode = nullptr;
	// current node?
};




struct IdleComponent : public Component
{
	const float Duration = 10.f;
	double Timestamp = 0.0;
};

struct AlertComponent : public Component
{};

struct PatrolComponent : public Component
{};

struct ChaseComponent : public Component
{};

struct FleeComponent : public Component
{};

//struct AttackComponent : public Component
//{};

//struct CharacterStateComponent : public Component
//{
//	bool IsIdle;
//	bool IsWalking;
//	bool IsRunning;
//	bool IsAttacking;
//	bool IsAlive;
//	bool IsAiming;
//};




//struct StateMachineComponent : public Component
//{
//	class State* ActiveState;
//	std::vector<class State*>	States;
//};



// TODO; Maybe only need SteeringBehaviorComponent (or have separate)?
struct WanderBehaviorComponent : public Component
{
	CU::Vector2<float>		Target;
	float					WalkDuration = 1.3f;
	float					ElapsedTime = 0.f;
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