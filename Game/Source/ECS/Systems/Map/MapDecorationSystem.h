#pragma once
#include "../Base/System.h"

class Entity;
// Rename? Foilage Decroratiom, ResourcePoplation?
class MapDecorationSystem : public System, public Subscriber
{
public:
	MapDecorationSystem();
	~MapDecorationSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

private:
	void GenerateResources(Entity* entity);
	void PopulateWithFoilage(const Entity* mapChunk); // PopulateWithFoilage, Decorate?
};