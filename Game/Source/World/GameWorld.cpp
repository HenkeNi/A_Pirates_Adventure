#include "Pch.h"
#include "GameWorld.h"
//#include "../Systems/Rendering/SpriteRenderSystem.h"


GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

#include "../Entity/Components/Core/CoreComponents.h"
#include "../Entity/Components/Physics/PhysicsComponents.h"
#include "../Entity/Components/Rendering/RenderComponents.h"
#include <Core/Resources/ResourceHolder.hpp>

void GameWorld::Init()
{
	//auto spriteRenderSystem = std::make_unique<SpriteRenderSystem>();
	//spriteRenderSystem->Init(&m_entityManager);


	//m_systemManager.Register(std::move(spriteRenderSystem));




	//Entity player;
	//player.AddComponent(new TransformComponent);
	//player.AddComponent(new SpriteComponent);
	//player.GetComponent<TransformComponent>()->m_currentPos = { (float)Random::InRange(2, 62), 0.3f, (float)Random::InRange(2, 62) };
	//auto sprite = player.GetComponent<SpriteComponent>();
	//sprite->m_material = {
	//	&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("pirate_idle"),
	//	&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };
	//m_entityManager.Add(std::move(player));

	//Entity camera;
	//camera.AddComponent(new CameraComponent);
	//camera.AddComponent(new TransformComponent);
	//camera.GetComponent<TransformComponent>()->m_currentPos = { 0.f, 0.f, 2.f };
	//camera.GetComponent<CameraComponent>()->m_targetOffset = { 0.f, 0.f, 2.f };
	//camera.GetComponent<CameraComponent>()->m_target = *m_entityManager.FindAllWithComponents<TransformComponent>().begin();
	//m_entityManager.Add(std::move(camera));

}

void GameWorld::Update(float aDeltaTime)
{
	//m_systemManager.Update(aDeltaTime);
}

void GameWorld::LateUpdate(float aDeltaTime)
{
	//m_systemManager.LateUpdate(aDeltaTime);
}

void GameWorld::Draw()
{
	//m_systemManager.Draw();
}