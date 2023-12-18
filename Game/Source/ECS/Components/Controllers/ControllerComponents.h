#pragma once
#include "../Base/Component.h"


struct PlayerControllerComponent : Component
{
	std::unordered_map<Hi_Engine::eKey, class Command*> InputMapping; // TODO; rename, move Command from engine?
	// - Input/Gamepad mappings -> key, command?
};

struct AIController : Component
{

};


//struct EnemyControllerComponent : ComponentBase
//{
//	// AI => Behavior tree..
//};
//
//
//// Animal Controller?	(steering behavuir?)