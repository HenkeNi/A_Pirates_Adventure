#include "Pch.h"
#include "MapGenerationSystem.h"

MapGenerationSystem::MapGenerationSystem(Hi_Engine::World& world)
	: System{ world, Hi_Engine::eUpdatePhase::Update }, m_entityFactory{ nullptr }
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this);
}

MapGenerationSystem::~MapGenerationSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::GameStarted, this);
}

void MapGenerationSystem::Receive(Message& message)
{
	if (message.GetMessageType() != eMessage::GameStarted)
		return;

	GenerateMapChunk(0, 0); // TODO; generate larger area?
}

void MapGenerationSystem::OnCreated()
{
	//std::cout << "MapGenerationSystem code [on created]: " << this << std::endl;
}

void MapGenerationSystem::SetFactory(EntityFactory* factory)
{
	m_entityFactory = factory;
	//std::cout << "MapGenerationSystem code [set facotry]: " << this << std::endl;
}

void MapGenerationSystem::GenerateMapChunk(int xCoord, int yCoord)
{
	// auto mapChunk = m_entity -> can't access entity factory here...
	std::cout << "System: " << this << std::endl;

	//auto t = Test;
	//std::cout << "MapGenerationSystem code{event]: " << this << std::endl;

	if (!m_entityFactory)
	{
		Hi_Engine::Logger::LogWarning("[MapGenerationSystem::GenerateMapChunk] - No valid EntityFactory");
		return;
	}

	auto mapChunk = m_entityFactory->CreateFromPrefab(m_world, "MapChunk");

	int x = 20;

}
