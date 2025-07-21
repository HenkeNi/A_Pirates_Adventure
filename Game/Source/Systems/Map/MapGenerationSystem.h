#pragma once

namespace Hi_Engine
{
	class EntityFactory;
}

using Hi_Engine::EntityFactory;

class MapGenerationSystem : public Hi_Engine::System, public Subscriber
{
public:
	MapGenerationSystem(Hi_Engine::World& world);
	~MapGenerationSystem();

	void Receive(Message& message) override;
	void OnCreated() override;

	void SetFactory(EntityFactory* factory);

private:
	void GenerateMapChunk(int xCoord, int yCoord);

	EntityFactory* m_entityFactory;
};

