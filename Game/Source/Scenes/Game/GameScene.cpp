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

void GameScene::Update(float aDeltaTime)
{
	m_sceneManager.Update(aDeltaTime);
	m_systemManager.Update(aDeltaTime); // or pass in all entities and let system update the ones they need...
}

void GameScene::LateUpdate(float aDeltaTime)
{
	m_sceneManager.LateUpdate(aDeltaTime);
	m_systemManager.LateUpdate(aDeltaTime);
}

void GameScene::Draw() const
{
	m_sceneManager.Draw();
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
#include "World/DungeonScene.h"
#include "World/OverworldScene.h"

void GameScene::OnCreated()
{
	m_systemManager.Init(&m_entityManager);

	m_sceneManager.Register(std::make_unique<OverworldScene>(m_sharedContext),	eScene::Overworld);
	m_sceneManager.Register(std::make_unique<DungeonScene>(m_sharedContext),	eScene::Dungeon);

	m_sceneManager.Init((int)eScene::Overworld);
}

void GameScene::OnEnter()
{
	//m_entityManager.LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");	// TODO; Load the needed blueprints for each scene... (clear when leaving the scene)


	





	// TODO; set EntityManager in Systems...
























	//m_map.Init();

	

	


	//GameObject camera;
	//camera.AddComponent(new C_Camera);
	//camera.AddComponent(new C_Transform);
	//camera.GetComponent<C_Transform>()->SetPosition({ 0.f, 0.f, 2.f });
	//m_objectManager.AddObject(std::move(camera));

	//int id = m_objectManager.GetAllObjects().begin()->GetID();

	//GameObject player;
	//player.AddComponent(new C_Sprite);
	//player.AddComponent(new C_Transform);
	//player.AddComponent(new C_Movement);
	//player.AddComponent(new C_PlayerController);
	//player.AddComponent(new C_BoxCollider);

	//CU::Vector3<float> playerPos = { (float)Random::InRange(2, 62), 0.3f, (float)Random::InRange(2, 62) };
	//player.GetComponent<C_Transform>()->SetPosition(playerPos);
	//player.GetComponent<C_Sprite>()->SetMaterial({ 
	//	&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("pirate_idle"), 
	//	&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });
	//m_objectManager.AddObject(std::move(player));

	//id = m_objectManager.GetAllObjects().back().GetID();
	//m_objectManager.GetAllObjects()[0].GetComponent<C_Camera>()->SetTarget(&m_objectManager.GetAllObjects()[1]);



	//for (int i = 0; i < 70; ++i)
	//{
	//	GameObject tree;
	//	tree.AddComponent(new C_Transform);
	//	tree.AddComponent(new C_Sprite);
	//	tree.GetComponent<C_Sprite>()->SetMaterial({ 
	//		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("palm_01"),
	//		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });
	//	tree.GetComponent<C_Transform>()->SetPosition({ (float)Random::InRange(2, 62), 0.45f, (float)Random::InRange(2, 62) });
	//	tree.GetComponent<C_Transform>()->SetScale({ 1.f, 1.35f, 1.f });

	//	m_objectManager.AddObject(std::move(tree));
	//}



	//for (int i = 0; i < 115; ++i)
	//{
	//	GameObject grass;
	//	grass.AddComponent(new C_Transform);
	//	grass.AddComponent(new C_Sprite);
	//	grass.GetComponent<C_Sprite>()->SetMaterial({
	//		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("grass"),
	//		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });

	//	CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.25f, (float)Random::InRange(2, 62) };
	//	grass.GetComponent<C_Transform>()->SetPosition({ position });
	//	grass.GetComponent<C_Transform>()->SetScale({ 0.75f, 0.75f, 0.75f });
	//	m_objectManager.AddObject(std::move(grass));

	//	GameObject smallGrass;
	//	smallGrass.AddComponent(new C_Transform);
	//	smallGrass.AddComponent(new C_Sprite);
	//	smallGrass.GetComponent<C_Sprite>()->SetMaterial({
	//		&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("grass"),
	//		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });
	//	smallGrass.GetComponent<C_Transform>()->SetPosition({ position.x, position.y - 0.1f, position.z + 0.1f });
	//	smallGrass.GetComponent<C_Transform>()->SetScale({ 0.5f, 0.5f, 0.5f });
	//	m_objectManager.AddObject(std::move(smallGrass));
	//}


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
	//skeleton.AddComponent(new C_Sprite);
	//skeleton.AddComponent(new C_Transform);
	//skeleton.AddComponent(new C_Movement);
	//skeleton.AddComponent(new C_BehaviorTree);
	//skeleton.GetComponent<C_Sprite>()->SetMaterial({
	//	&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("skeleton"),
	//	&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") });
	//skeleton.GetComponent<C_Transform>()->SetPosition({ playerPos.x, 0.1f, playerPos.z });
	//skeleton.GetComponent<C_Transform>()->SetScale({ 0.4f, 0.4f, 0.4f });
	//skeleton.GetComponent<C_Movement>()->SetMovementSpeed(0.5f);
	//

	//m_objectManager.AddObject(std::move(skeleton));

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


	///*GameObject background;
	//auto* transform = background.GetComponent<C_Transform>();
	//transform->SetPosition({ 0, 0, 0 });
	//auto* sprite = background.CreateComponent<C_Sprite>();
	//auto& texture = Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("title_screen");
	//sprite->SetTexture(&texture);*/
	////m_objectManager.AddObject(background);






	//// load components?

	//for (auto& object : m_objectManager.GetAllObjects())
	//	object.Activate();
}

void GameScene::OnExit()
{
	// set entity manager in system to nullptr...
}