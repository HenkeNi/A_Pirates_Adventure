#pragma once


enum class eSceneType
{
	Title, Loading, Menu, Settings, Game, Pause, GameOver, Count
};

enum class eCompMessage
{
	PositionChanged,
	Colliding,

	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
};