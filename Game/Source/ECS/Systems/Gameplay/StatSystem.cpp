#include "Pch.h"
#include "StatSystem.h"
#include "Components/Gameplay/GameplayComponents.h"


StatSystem::StatSystem()
{
	// TODO; modifiers, status effects... etc

	PostMaster::GetInstance().Subscribe(eMessage::PlayerLeveledUp, this);
	PostMaster::GetInstance().Subscribe(eMessage::ItemEquipped, this);
	PostMaster::GetInstance().Subscribe(eMessage::ItemUnequipped, this);
}

StatSystem::~StatSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::PlayerLeveledUp, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::ItemEquipped, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::ItemUnequipped, this);
}

void StatSystem::Receive(Message& message)
{
	// Maybe should listen to if something is attacked, get data from attacker AND victim (defense, health, etc) Needs to 

	// TODO; listen for item equiped, unequiped, etc..?


	//auto msg = aMsg;

 //	if (aMsg.GetMessageType() == eMessage::EntityAttacked)	// remove check? since only listening to one message?!
	//{
	//	auto data = std::any_cast<std::tuple<Entity*, Entity*>>(aMsg.GetData());

	//	auto attacker	= std::get<0>(data);
	//	auto victim		= std::get<1>(data);

	//	// TODO; Get weapon component?
	//	static int attackDamage = 10;

	//	auto healthComponent = victim->GetComponent<HealthComponent>();

	//	healthComponent->m_currentValue -= attackDamage;

	//	if (healthComponent->m_currentValue <= 0)
	//	{
	//		//m_entityManager->Destroy(victim->GetID()); // DO HERE???
	//		m_entitiesToRemove.push_back(victim->GetID());
	//	}
	//}
}

void StatSystem::Update(float deltaTime)
{
}