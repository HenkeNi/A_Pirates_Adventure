#include "Pch.h"
#include "EnemySpawnSystem.h"
#include "Entities/EntityManager.h"
#include "Entities/Entity.h"
#include "../AI/BehaviorTree/Composite/CompositeNodes.h"
#include "../AI/BehaviorTree/Action/ActionNodes.h"
#include "../AI/BehaviorTree/Condition/ConditionNodes.h"
#include "Components/Utility/UtilityComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/AI/AIComponents.h"



EnemySpawnSystem::EnemySpawnSystem()
{
}

EnemySpawnSystem::~EnemySpawnSystem()
{
}

void EnemySpawnSystem::Receive(Message& message)
{
}

void EnemySpawnSystem::Update(float deltaTime)
{
	return;

	if (!m_entityManager) // Dont check?
		return;

	// Make a generic spawner system??
	auto spawners = m_entityManager->FindAll<SpawnComponent>();

	for (auto& spawner : spawners)
	{
 		auto* spawnComponent = spawner->GetComponent<SpawnComponent>();	// TODO; fix... spawner(s) seems to be garabage.. 201030302 m_components size....

		spawnComponent->ElapsedTime += deltaTime; // replace with timestap + duration...

		bool isTimeToSpawn = spawnComponent->ElapsedTime >= spawnComponent->Interval;
		bool isSpawnLimitReached = spawnComponent->SpawnedAmount >= spawnComponent->Amount;

		if (isTimeToSpawn && !isSpawnLimitReached)
		{
			spawnComponent->ElapsedTime = 0.f;
			++spawnComponent->Amount;

			SpawnEnemy(spawnComponent->Spawned, spawner->GetComponent<TransformComponent>()->CurrentPos);
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

// DONT DO here:...
void EnemySpawnSystem::SpawnEnemy(const std::string& type, const FVector2& position)
{
	//auto* player = *m_entityManager->FindAll<PlayerControllerComponent>().begin();
	//
	//if (!player)
	//	return;
	//
	//auto entity = m_entityManager->Create(type);

	//auto transform = entity->GetComponent<TransformComponent>();
	//transform->CurrentPos = position;

	//

	//// TODO; assign a pre-built behavior tree suitable for enemy (save type in json) a


	//// Set up behavior tree 
	//auto behaviorTree = entity->GetComponent<BehaviorTreeComponent>();

	//// Maybe not all nodes needs ID??

	//int entityID = entity->GetID();
	//int playerID = player->GetID();

	//// DO in AI system when entity is registered?!
	//auto* root = new SelectorNode{ entityID };

	//auto attackSequence = new SequenceNode{ entityID };
	//attackSequence->AddChild(new TargetInRangeNode{ entityID, playerID });
	//attackSequence->AddChild(new AttackTargetNode{ entityID, playerID });

	//auto alertSequence = new SequenceNode{ entityID };
	//alertSequence->AddChild(new TargetInViewNode{ entityID, playerID });
	//alertSequence->AddChild(new MoveToTargetNode{ entityID, playerID });

	//auto idle = new IdleNode{ entityID };

	//root->AddChild(attackSequence);
	//root->AddChild(alertSequence);
	//root->AddChild(idle);

	//behaviorTree->RootNode = root;

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