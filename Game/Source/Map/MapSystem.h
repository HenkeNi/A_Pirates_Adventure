#pragma once
#include "Map.h"
#include "MapGenerator.h"
#include "EnvironmentGenerator.h"

class EntityManager;

// Or MapGenerationSystem --- TilemapSystem?
class MapSystem
{
public:
	MapSystem();
	~MapSystem();

	void Init(EntityManager* anEntityManager);	// Rename; GenerateStartArea()?

	void Update();
	void Draw()				const;

private:
	MapGenerator			m_mapGenerator;
	EnvironmentGenerator	m_environmentGenerator;
	Map						m_map;
	EntityManager*			m_entityManager;
};