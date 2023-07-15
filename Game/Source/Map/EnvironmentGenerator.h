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
	void GenerateFoilage(const std::string& aType, unsigned anAmount, const CU::Vector2<float> someMinPositions, const CU::Vector2<float> someMaxPositions);

	EntityManager* m_entityManager;
};

