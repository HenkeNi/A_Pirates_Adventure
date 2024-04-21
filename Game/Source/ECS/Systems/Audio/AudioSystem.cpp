#include "Pch.h"
#include "AudioSystem.h"
#include "Entities/EntityManager.h"


AudioSystem::AudioSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityAttacked, this);
	PostMaster::GetInstance().Subscribe(eMessage::EntityDestroyed, this);
	PostMaster::GetInstance().Subscribe(eMessage::ItemCollected, this);
	PostMaster::GetInstance().Subscribe(eMessage::ItemUsed, this);
	PostMaster::GetInstance().Subscribe(eMessage::ButtonActivated, this);
	// entity died.. entiy collected?
}

AudioSystem::~AudioSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityAttacked, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityDestroyed, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::ItemCollected, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::ItemUsed, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::ButtonActivated, this);
}

void AudioSystem::Receive(Message& message)
{
	auto type = message.GetMessageType();
	auto* entity = std::any_cast<Entity*>(message.GetData());

	if (!entity)
		return;

	if (auto* audioComponent = entity->GetComponent<AudioComponent>())
	{
		if (audioComponent->AudioTriggers.contains(type))
		{
			auto& audio = audioComponent->AudioTriggers.at(type);
			Hi_Engine::ServiceLocator::GetAudioController()->PlaySound(audio);
		}

		//Hi_Engine::ServiceLocator::GetAudioController()->PlaySound(audioComponent->Audio);
		
		//if (audioComponent->ShouldPlay)
		//{
		//}
	}
}

void AudioSystem::Update(float deltaTime)
{
}
