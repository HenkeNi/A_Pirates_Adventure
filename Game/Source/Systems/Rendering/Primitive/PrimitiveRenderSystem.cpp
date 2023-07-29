#include "Pch.h"
#include "PrimitiveRenderSystem.h"
#include "EntityManager.h"
#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"
#include "Combat/CombatComponents.h"


PrimitiveRenderSystem::PrimitiveRenderSystem()
{
}

PrimitiveRenderSystem::~PrimitiveRenderSystem()
{
}

void PrimitiveRenderSystem::Receive(Message& aMsg)
{
}

void PrimitiveRenderSystem::Draw()
{ 
	if (!m_entityManager)
		return;

}