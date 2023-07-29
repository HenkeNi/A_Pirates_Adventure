#pragma once
#include "../Base/ComponentBase.h"


struct PlayerControllerComponent : ComponentBase
{
	std::unordered_map<Hi_Engine::eInputType, class Command*> m_inputMapping; // TODO; rename, move Command from engine?
	// - Input/Gamepad mappings -> key, command?
};


//struct EnemyControllerComponent : ComponentBase
//{
//	// AI => Behavior tree..
//};
//
//
//// Animal Controller?	(steering behavuir?)