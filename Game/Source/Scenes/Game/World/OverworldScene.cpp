#include "Pch.h"
#include "OverworldScene.h"


OverworldScene::OverworldScene(SharedContext aContext)
	: Scene{ aContext }
{
}

OverworldScene::~OverworldScene()
{
}

void OverworldScene::Update(float aDeltaTime)
{
	m_systemManager.Update(aDeltaTime);
}

void OverworldScene::LateUpdate(float aDeltaTime)
{
	m_systemManager.LateUpdate(aDeltaTime);
}

void OverworldScene::Draw() const
{
	m_systemManager.Draw();
}

#include "Core/Resources/ResourceHolder.hpp"
#include "../GameObject/Components/Core/Transform/C_Transform.h"
#include "../GameObject/Components/Rendering/Camera/C_Camera.h"
#include "../GameObject/Components/Rendering/Sprite/C_Sprite.h"
#include "../GameObject/Components/Controllers/C_PlayerController.h"
#include "../GameObject/Components/Physics/Movement/C_Movement.h"
#include "../GameObject/Components/AI/SteeringBehavior/C_Behavior.h"
//#include "../Gameplay/SteeringBehaviors/WanderSeekBehavior.h"
//#include "../Gameplay/SteeringBehaviors/FlockBehavior.h"
#include "../GameObject/Components/AI/BehaviorTree/C_BehaviorTree.h"

#include "../GameObject/Components/Physics/Colliders/C_BoxCollider.h"

#include "../AI/BehaviorTree/SelectorNode.h"
#include "../AI/BehaviorTree/SequenceNode.h"
#include "../AI/BehaviorTree/ActionNodes.h"
#include "../AI/BehaviorTree/ConditionNodes.h"

#include "Entity.h"
#include "Core/CoreComponents.h"
#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"
#include "Physics/PhysicsComponents.h"
#include "Rendering/RenderComponents.h"
#include "Controllers/ControllerComponents.h"
#include <Core/Resources/ResourceHolder.hpp>
#include "Rendering/Sprite/SpriteRenderSystem.h"
#include "SystemManager.h"
#include "Rendering/Camera/CameraSystem.h"
#include "Rendering/Map/MapRenderSystem.h"
#include "Input/InputSystem.h"
#include "Controllers/PlayerControllerSystem.h"
#include "Physics/MovementSystem.h"

void OverworldScene::OnCreated()
{




}

void OverworldScene::OnEnter()
{


	m_map.GenerateMap();
	m_systemManager.Init(&m_entityManager);

	m_entityManager.LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");

	auto player = m_entityManager.Create("Player");

	CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.3f, (float)Random::InRange(2, 62) };

	player->GetComponent<TransformComponent>()->m_currentPos = position;
	auto sprite = player->GetComponent<SpriteComponent>();
	sprite->m_material = {
		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("pirate_idle"),
		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };





	auto palm = m_entityManager.Create("PalmTree");

	palm->AddComponent(new TransformComponent);
	palm->AddComponent(new SpriteComponent);
	palm->GetComponent<TransformComponent>()->m_currentPos = position;
	auto treesprite = palm->GetComponent<SpriteComponent>();
	treesprite->m_material = {
		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("palm_01"),
		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };







	auto inputSystem = std::make_unique<InputSystem>();
	inputSystem->Init(&m_entityManager);

	auto playerControllerSystem = std::make_unique<PlayerControllerSystem>();
	playerControllerSystem->Init(&m_entityManager);

	auto movementSystem = std::make_unique<MovementSystem>();
	movementSystem->Init(&m_entityManager);

	auto cameraSystem = std::make_unique<CameraSystem>();
	cameraSystem->Init(&m_entityManager);

	auto mapRenderSystem = std::make_unique<MapRenderSystem>();
	// dont need entityManager??

	auto spriteRenderSystem = std::make_unique<SpriteRenderSystem>();
	spriteRenderSystem->Init(&m_entityManager);

	m_systemManager.Register(std::move(inputSystem));
	m_systemManager.Register(std::move(playerControllerSystem));
	m_systemManager.Register(std::move(movementSystem));
	m_systemManager.Register(std::move(cameraSystem));
	m_systemManager.Register(std::move(mapRenderSystem));
	m_systemManager.Register(std::move(spriteRenderSystem));



	/*Entity player;
	player.AddComponent(new TransformComponent);
	player.AddComponent(new SpriteComponent);
	player.AddComponent(new InputComponent);
	player.AddComponent(new PlayerControllerComponent);
	player.AddComponent(new VelocityComponent);

	CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.3f, (float)Random::InRange(2, 62) };

	player.GetComponent<TransformComponent>()->m_currentPos = position;
	auto sprite = player.GetComponent<SpriteComponent>();
	sprite->m_material = {
		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("pirate_idle"),
		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };
	m_entityManager.Add(std::move(player));*/




	// Create a CameraSystem?
	Entity camera;
	camera.AddComponent(new CameraComponent);
	camera.AddComponent(new TransformComponent);
	camera.GetComponent<TransformComponent>()->m_currentPos = { 0.f, 0.f, 2.f };
	camera.GetComponent<CameraComponent>()->m_targetOffset = { 0.f, 0.f, 2.f };
	camera.GetComponent<CameraComponent>()->m_target = *m_entityManager.FindAllWithComponents<TransformComponent>().begin();
	m_entityManager.Add(std::move(camera));

}

void OverworldScene::OnExit()
{
}
