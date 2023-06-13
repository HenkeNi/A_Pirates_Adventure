#pragma once


enum eScene
{
	Game	= 1, 
	Pause	= 2,
	Menu	= 4,
	Loading = 8, 
	Title	= 16,
	Count	= 32
	//Settings, 
	//GameOver, 
};

enum class eMessage
{
	EntityCreated,
	EntityDestroyed,
	MapCreated,
};


// TODO: remove
enum class eComponentMessage
{
	PositionChanged, 
	Colliding
};

enum class eLayer
{
	Terrain,
	Characters,
	Items,
	Buildings,
	Effects,
	UI
};


enum class eBTNodeStatus
{
	Invalid,
	Running,
	Success,
	Failure
};