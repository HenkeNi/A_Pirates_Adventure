#pragma once


enum class eSceneType
{
	Game, 
	Loading, 
	Menu, 
	Pause, 
	Title, 
	//Settings, 
	//GameOver, 
	Count
};

enum class eMessageType
{
	PositionChanged,
	Colliding,

	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
};