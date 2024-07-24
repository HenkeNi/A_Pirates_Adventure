#pragma once
#include "../Base/Component.h"


//#################### AI Components ####################//
struct BlackboardComponent : public Component
{
	inline static FVector2 PlayerPosition; // Todo; use std::any instead? store player ID AND vector of crew IDs??
	inline static std::vector<Entity> Friendly; // store ids instead??
	inline static std::vector<Entity> Hostile; // todo, have DeathSystem or garbage system that cleans up dead entities at the end of frame?
	
	std::vector<FVector2> PointOfInterests; // TargetWaypoint?
	//bool IsMovingToPOI = false; // replace with destination component instead?
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
	FVector2	Target;
	float		WalkDuration = 1.3f;
	float		ElapsedTime = 0.f;
};

struct FlockBehaviorComponent : public Component
{
	class FlockBehavior*	Behavior = nullptr;
	unsigned				FlockID;
};

struct SeekBehaviorComponent : public Component
{
	class SeekBehavior*		Behavior = nullptr;
	FVector2				Target;
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