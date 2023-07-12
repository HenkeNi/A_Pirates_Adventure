#include "Pch.h"
#include "SpawnSystem.h"
#include "Data/Enumerations.h"


SpawnSystem::SpawnSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityDestroyed, this);
}

SpawnSystem::~SpawnSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityDestroyed, this);
}

void SpawnSystem::Receive(Message& aMsg)
{
	//auto msg = aMsg;

	//auto data = std::any_cast<std::tuple<Entity*, Entity*>>(aMsg.GetData());

	//auto attacker = std::get<0>(data);
	//auto victim = std::get<1>(data);

	//	// TODO; Get weapon component?
	//static int attackDamage = 10;

	//auto healthComponent = victim->GetComponent<HealthComponent>();

	//	healthComponent->m_currentValue -= attackDamage;

	//	if (healthComponent->m_currentValue <= 0)
	//	{
	//		//m_entityManager->Destroy(victim->GetID()); // DO HERE???
	//		m_entitiesToRemove.push_back(victim->GetID());
	//	}
	//}
	//// If spawn component?!

	//// listen to chest open, enemy killed, resource cut down 

	//// either store and do next frame or do directly...

}

void SpawnSystem::Update(float aDeltaTime)
{
	// get entieis with spawn components... (check what should be spawned )
}