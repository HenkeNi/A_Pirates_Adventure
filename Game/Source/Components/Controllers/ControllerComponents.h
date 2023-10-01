#pragma once
#include "../Base/ComponentBase.h"


struct PlayerControllerComponent : ComponentBase
{
	std::unordered_map<Hi_Engine::eInputType, class Command*> InputMapping; // TODO; rename, move Command from engine?
	// - Input/Gamepad mappings -> key, command?
};

struct AIController : ComponentBase
{

};


//struct EnemyControllerComponent : ComponentBase
//{
//	// AI => Behavior tree..
//};
//
//
//// Animal Controller?	(steering behavuir?)