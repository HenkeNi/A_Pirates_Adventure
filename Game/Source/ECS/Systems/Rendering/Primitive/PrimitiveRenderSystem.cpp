#include "Pch.h"
#include "PrimitiveRenderSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Rendering/RenderComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Combat/CombatComponents.h"


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