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
	m_sharedContext.SystemManager.Update(aDeltaTime);
}

void OverworldScene::LateUpdate(float aDeltaTime)
{
	m_sharedContext.SystemManager.LateUpdate(aDeltaTime);
}

void OverworldScene::Draw() const
{
	m_sharedContext.SystemManager.Draw();
}

#include "Core/Resources/ResourceHolder.hpp"
#include "../AI/BehaviorTree/Composite/CompositeNodes.h"
#include "../AI/BehaviorTree/Action/ActionNodes.h"
#include "../AI/BehaviorTree/Condition/ConditionNodes.h"

#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"
#include "Components/AI/AIComponents.h"
#include "Components/Gameplay/GameplayComponents.h"

#include <Core/Resources/ResourceHolder.hpp>


#include "../Gameplay/SkillTree.h"

void OverworldScene::OnCreated()
{
}

void OverworldScene::OnEnter()
{
	auto& systemManager = m_sharedContext.SystemManager;
	systemManager.Init(&m_entityManager);

	// Send event??
	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");


	//auto* sky = m_entityManager.Create("sky_background");
	//auto* transformComponent = background->GetComponent<TransformComponent>();
	//transformComponent->Scale *= 1.5f;
	//transformComponent->CurrentPos.y = 0.5f;

	//SkillTree skillTree;
	//skillTree.RegisterSkill("Base", "A-Base");
	//skillTree.RegisterSkill("Base", "B-Base");
	//skillTree.RegisterSkill("Base", "C-Base");

	//skillTree.RegisterSkill("A-Base",   "A-Tier1-01");
	//skillTree.RegisterSkill("A-Base", "A-Tier1-02");
	//skillTree.RegisterSkill("A-Base", "A-Tier1-03");

	//skillTree.RegisterSkill("A-Tier1-01", "A-Tier2-01");
	//skillTree.RegisterSkill("A-Tier1-01", "A-Tier2-02");
	//skillTree.RegisterSkill("A-Tier1-01", "A-Tier2-03");

	//skillTree.RegisterSkill("B-Base", "B-Tier1-01");
	//skillTree.RegisterSkill("B-Base", "B-Tier1-02");
	//skillTree.RegisterSkill("B-Base", "B-Tier1-03");

	//skillTree.RegisterSkill("C-Base", "C-Tier1-01");
	//skillTree.RegisterSkill("C-Base", "C-Tier1-02");
	//skillTree.RegisterSkill("C-Base", "C-Tier1-03");


	//skillTree.RegisterSkill("A-Tier1-01", "A-Tier2-04");
	//skillTree.RegisterSkill("A-Tier1-01", "A-Tier2-05");
	//skillTree.RegisterSkill("A-Tier1-01", "A-Tier2-06");



	////skillTree.PrintLevelOrder(skillTree.GetRoot());

	//for (auto* node : skillTree.GetNextUnlockableNodes())
	//	std::cout << node->Identifier << ' ';












	// m_mapSystem.Init(&m_entityManager);

	// Player
	auto player = m_entityManager.Create("Player");
	//CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.42f, (float)Random::InRange(2, 62) };
	CU::Vector3<float> position = { 27.f, 0.42f, 25.f };
	player->GetComponent<TransformComponent>()->CurrentPos = position;

	auto time = m_entityManager.Create("WorldTime");


	for (int i = 0; i < 10; ++i)
	{
		float x = 0.1 * i;
		auto* fish = m_entityManager.Create("Fish");
		fish->GetComponent<TransformComponent>()->CurrentPos = { 10.f + x, 0.42f, 12.f };
	}


	auto crab = m_entityManager.Create("Crab");
	crab->GetComponent<TransformComponent>()->CurrentPos = { 30.f, 0.42f, 30.f };

	auto raft = m_entityManager.Create("Raft");
	raft->GetComponent<TransformComponent>()->CurrentPos = { 10.f, 0.42f, 10.f };

	auto hut = m_entityManager.Create("Hut");
	hut->GetComponent<TransformComponent>()->CurrentPos = { 20.f, 0.85f, 30.f };

	auto npc = m_entityManager.Create("Castaway");
	npc->GetComponent<TransformComponent>()->CurrentPos = { 15.f, 0.42f, 30.f };

	// Camera => do in camera system??
	auto camera = m_entityManager.Create("Camera");
	camera->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 0.f, 2.f };
	//camera->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 0.f, 2.f };
	camera->GetComponent<CameraComponent>()->TargetOffset = { 0.f, 0.f, 2.f };	
	//camera->GetComponent<CameraComponent>()->TargetOffset = { 0.f, 3.f, 4.f };
	camera->GetComponent<CameraComponent>()->TargetID = (* m_entityManager.FindAll<PlayerControllerComponent>().begin())->GetID();
	//camera->GetComponent<CameraComponent>()->m_target = *m_entityManager.FindAll<PlayerControllerComponent>().begin();

	PostMaster::GetInstance().SendMessage({ eMessage::GameStarted, true }); 	// FIX
}

void OverworldScene::OnExit()
{
}
