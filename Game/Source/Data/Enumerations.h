#pragma once


enum class eScene
{
	Game		= 1, 
	Pause		= 2,
	Menu		= 4,
	Loading		= 8, 
	Title		= 16,
	Overworld	= 32,
	Dungeon		= 64,
	Count		= 128
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

enum class eTile
{
	Sand, Water
};