#include "Pch.h"
#include "EnemySpawnSystem.h"
#include "EntityManager.h"
#include "Entity.h"
#include "../AI/BehaviorTree/Composite/CompositeNodes.h"
#include "../AI/BehaviorTree/Action/ActionNodes.h"
#include "../AI/BehaviorTree/Condition/ConditionNodes.h"



EnemySpawnSystem::EnemySpawnSystem()
{
}

EnemySpawnSystem::~EnemySpawnSystem()
{
}

void EnemySpawnSystem::Receive(Message& aMsg)
{
}

void EnemySpawnSystem::Update(float aDeltaTime)
{
	if (!m_entityManager) // Dont check?
		return;

	// Make a generic spawner system??
	auto spawners = m_entityManager->FindAllWithComponents<SpawnComponent>();

	for (auto& spawner : spawners)
	{
		auto* spawnComponent = spawner->GetComponent<SpawnComponent>();

		spawnComponent->m_elapsedTime += aDeltaTime;

		bool isTimeToSpawn = spawnComponent->m_elapsedTime >= spawnComponent->m_interval;
		bool isSpawnLimitReached = spawnComponent->m_spawnedAmount >= spawnComponent->m_amount;

		if (isTimeToSpawn && !isSpawnLimitReached)
		{
			spawnComponent->m_elapsedTime = 0.f;
			++spawnComponent->m_amount;

			SpawnEnemy(spawnComponent->m_spawned, spawner->GetComponent<TransformComponent>()->m_currentPos);
		}
	}
	//
	//static float currentTime = 0.f;
	//static const float spawnDuration = 5.f;


	//if ((currentTime += aDeltaTime) >= spawnDuration)
	//{
	//	SpawnEnemy();
	//	currentTime = 0.f;
	//}

}

void EnemySpawnSystem::SpawnEnemy(const std::string& aType, const CU::Vector3<float>& aPosition)
{
	auto* player = *m_entityManager->FindAllWithComponents<PlayerControllerComponent>().begin();
	
	if (!player)
		return;
	
	auto entity = m_entityManager->CreateResources(aType);

	auto transform = entity->GetComponent<TransformComponent>();
	transform->m_currentPos = aPosition;

	

	// TODO; assign a pre-built behavior tree suitable for enemy (save type in json) a


	// Set up behavior tree 
	auto behaviorTree = entity->GetComponent<BehaviorTreeComponent>();

	// Maybe not all nodes needs ID??

	int entityID = entity->GetID();
	int playerID = player->GetID();

	auto* root = new SelectorNode{ entityID };

	auto attackSequence = new SequenceNode{ entityID };
	attackSequence->AddChild(new TargetInRangeNode{ entityID, playerID });
	attackSequence->AddChild(new AttackTargetNode{ entityID, playerID });

	auto alertSequence = new SequenceNode{ entityID };
	alertSequence->AddChild(new TargetInViewNode{ entityID, playerID });
	alertSequence->AddChild(new MoveToTargetNode{ entityID, playerID });

	auto idle = new IdleNode{ entityID };

	root->AddChild(attackSequence);
	root->AddChild(alertSequence);
	root->AddChild(idle);

	behaviorTree->m_rootNode = root;

	//auto root = new WalkToTarget{ &m_objectManager.GetAllObjects().back() };
	//root->SetTarget(&m_objectManager.GetAllObjects()[1]);

	//auto root = new SelectorNode;

	//auto patrolSequence = new SequenceNode;
	//patrolSequence->AddChild(new ConditionNode);
	//patrolSequence->AddChild(new ActionNode);
	//patrolSequence->AddChild(new ActionNode);

	//auto attackSequence = new SequenceNode;
	//attackSequence->AddChild(new ConditionNode);
	//attackSequence->AddChild(new ActionNode);
	//attackSequence->AddChild(new ActionNode);

	//root->AddChild(patrolSequence);
	//root->AddChild(attackSequence);

}

bool EnemySpawnSystem::ShouldSpawn() const
{
	return true; // interval? Check amount of nearby enemies??
}