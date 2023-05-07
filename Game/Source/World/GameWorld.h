#pragma once

class Map;
class Area;

class GameWorld
{
public:


private:
	std::vector<Area*> m_areas;	// areas, regions, locations, levels

	Map* m_map; // Possibly by value..
};

