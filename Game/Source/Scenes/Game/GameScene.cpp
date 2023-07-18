#include "Pch.h"
#include "GameScene.h"
#include "SystemManager.h"


GameScene::GameScene(SharedContext aContext)
	: Scene{ aContext }
{
}

GameScene::~GameScene()
{
}

void GameScene::Register(ScenePtr_t aScene, eScene aType)
{
	m_sceneManager.Register(std::move(aScene), aType);
}

void GameScene::Update(float aDeltaTime)
{
	m_sceneManager.Update(aDeltaTime);
}

void GameScene::LateUpdate(float aDeltaTime)
{
	m_sceneManager.LateUpdate(aDeltaTime);
}

void GameScene::Draw() const
{
	m_sceneManager.Draw();
}

#include "Core/Resources/ResourceHolder.hpp"
//#include "../Gameplay/SteeringBehaviors/WanderSeekBehavior.h"
//#include "../Gameplay/SteeringBehaviors/FlockBehavior.h"
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
#include "Input/InputSystem.h"
#include "Controllers/PlayerControllerSystem.h"
#include "Physics/MovementSystem.h"
#include "Dungeon/DungeonScene.h"
#include "Overworld/OverworldScene.h"

void GameScene::OnCreated()
{
	m_sceneManager.Register(std::make_unique<OverworldScene>(m_sharedContext),	eScene::Overworld);
	m_sceneManager.Register(std::make_unique<DungeonScene>(m_sharedContext),	eScene::Dungeon);

	m_sceneManager.Init((int)eScene::Overworld);
}

void GameScene::OnEnter()
{
	//m_entityManager.LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");	// TODO; Load the needed blueprints for each scene... (clear when leaving the scene)




	////for (int i = 0; i < 10; ++i)
	////{
	////	GameObject fish;
	////	fish.AddComponent(new C_Transform);
	////	fish.AddComponent(new C_Sprite);
	////	fish.AddComponent(new C_Behavior);
	////	fish.GetComponent<C_Behavior>()->SetBehavior(new FlockBehavior);
	////	fish.GetComponent<C_Sprite>()->SetMaterial({
	////		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("fish"),
	////		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });
	////	fish.GetComponent<C_Transform>()->SetPosition({ (float)Random::InRange(0, 2), 0.45f, (float)Random::InRange(0, 2) });
	////	fish.GetComponent<C_Transform>()->SetScale({ 0.2f, 0.2f, 0.2f });

	////	m_objectManager.AddObject(std::move(fish));
	////}

	//GameObject crab;
	//crab.AddComponent(new C_Sprite);
	//crab.AddComponent(new C_Transform);
	//crab.AddComponent(new C_Movement);
	//crab.AddComponent(new C_Behavior);
	//crab.GetComponent<C_Behavior>()->SetBehavior(new WanderSeekBehavior);
	//crab.GetComponent<C_Sprite>()->SetMaterial({
	//	&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("crab"),
	//	&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });
	//crab.GetComponent<C_Transform>()->SetPosition({ playerPos.x, 0.1f, playerPos.z });
	//crab.GetComponent<C_Transform>()->SetScale({0.4f, 0.4f, 0.4f});
	//crab.GetComponent<C_Movement>()->SetMovementSpeed(0.006f);
	//m_objectManager.AddObject(std::move(crab));


	//GameObject skeleton;
	//skeleton.AddComponent(new C_BehaviorTree);
	//skeleton.GetComponent<C_Transform>()->SetPosition({ playerPos.x, 0.1f, playerPos.z });
	//skeleton.GetComponent<C_Transform>()->SetScale({ 0.4f, 0.4f, 0.4f });
	//skeleton.GetComponent<C_Movement>()->SetMovementSpeed(0.5f);

	//auto root = new SelectorNode;

	//auto attackSequence = new SequenceNode;
	//attackSequence->AddChild(new TargetInRange{ &m_objectManager.GetAllObjects()[1] });
	//attackSequence->AddChild(new AttackTarget{ &m_objectManager.GetAllObjects()[1] });

	//auto alertSequence = new SequenceNode;
	//alertSequence->AddChild(new TargetInView{ &m_objectManager.GetAllObjects()[1] });
	//alertSequence->AddChild(new MoveToTarget{ &m_objectManager.GetAllObjects()[1] });

	//auto idle = new Idle;

	//root->AddChild(attackSequence);
	//root->AddChild(alertSequence);
	//root->AddChild(idle);


	////auto root = new WalkToTarget{ &m_objectManager.GetAllObjects().back() };
	////root->SetTarget(&m_objectManager.GetAllObjects()[1]);

	////auto root = new SelectorNode;

	////auto patrolSequence = new SequenceNode;
	////patrolSequence->AddChild(new ConditionNode);
	////patrolSequence->AddChild(new ActionNode);
	////patrolSequence->AddChild(new ActionNode);

	////auto attackSequence = new SequenceNode;
	////attackSequence->AddChild(new ConditionNode);
	////attackSequence->AddChild(new ActionNode);
	////attackSequence->AddChild(new ActionNode);

	////root->AddChild(patrolSequence);
	////root->AddChild(attackSequence);

	//m_objectManager.GetAllObjects().back().GetComponent<C_BehaviorTree>()->SetRootNode(root);
	//
	////m_objectManager.GetAllObjects().back().GetComponent<C_BehaviorTree>()->SetRootNode(root);



	////GameObject inputListener;
	////inputListener.CreateComponent<C_








	//// load components?

	//for (auto& object : m_objectManager.GetAllObjects())
	//	object.Activate();
}

void GameScene::OnExit()
{
	// set entity manager in system to nullptr...
}