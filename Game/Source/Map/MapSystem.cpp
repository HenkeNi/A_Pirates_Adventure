#include "Pch.h"
#include "MapSystem.h"


MapSystem::MapSystem()
	: m_entityManager{ nullptr }
{
}

MapSystem::~MapSystem()
{
}

void MapSystem::Init(EntityManager* anEntityManager)
{	
	m_entityManager = anEntityManager;
	m_environmentGenerator.Init(anEntityManager);

	auto chunks = m_mapGenerator.GenerateStartArea();
	
	for (auto chunk : chunks)
	{
		m_environmentGenerator.PopulateMapChunk(chunk);
		m_map.AddMapChunk(chunk);
	}
}

void MapSystem::Update()
{
	// if entered a new map chunk... (update map..)


	// check if need to generate new map chunks? OR listen to event? 
}

void MapSystem::Draw() const
{
	// Get map chunks.. (filter out chunks in area around player??)

	m_map.Draw();

}
