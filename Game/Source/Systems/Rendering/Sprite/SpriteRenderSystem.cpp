#include "Pch.h"
#include "SpriteRenderSystem.h"
#include "../Entity/EntityManager.h"
#include "../Entity/Components/Rendering/RenderComponents.h"
#include "../Entity/Components/Core/CoreComponents.h"

//#include "../Entity/Entity.h"

//#include "../PostMaster/PostMaster.h"
//#include "../PostMaster/Message.h"



namespace CU = CommonUtilities;


SpriteRenderSystem::SpriteRenderSystem()
	: System{ 0 }
{
}

SpriteRenderSystem::~SpriteRenderSystem()
{
}

void SpriteRenderSystem::Receive(Message& aMsg)
{
}

void SpriteRenderSystem::Draw()
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAllWithComponents<SpriteComponent, TransformComponent>();

	for (const Entity* entity : entities)
	{
		auto material = entity->GetComponent<SpriteComponent>()->m_material;

		auto transform  = entity->GetComponent<TransformComponent>();
		auto position	= transform->m_currentPos;
		auto scale		= transform->m_scale;
		auto rotation	= transform->m_rotation;

		Hi_Engine::BillboardRenderer::GetInstance().Render({ &material, { position.x, position.y, position.z }, { scale.x, scale.y }, rotation });
	}
}