#pragma once

class EntityManager;

class EnvironmentGenerator
{
public:
	EnvironmentGenerator();
	~EnvironmentGenerator();

	void Init(EntityManager* anEntityManager);

	void PopulateMapChunk(class MapChunk& aChunk); // GenerateEnviromentObjects?

private:
	EntityManager* m_entityManager;
};

