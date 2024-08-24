#pragma once
#include "../Base/System.h"

// Rename? Foilage Decroratiom, ResourcePoplation?
class MapDecorationSystem : public System, public Subscriber
{
public:
	MapDecorationSystem();
	~MapDecorationSystem();

	void Receive(Message& message)	override;
	void SetSignature()				override;

private:
	void GenerateResources(Entity entity);
	void PopulateWithFoilage(Entity mapChunk); // PopulateWithFoilage, Decorate?
};