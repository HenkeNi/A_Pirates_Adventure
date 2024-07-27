#include "Pch.h"
#include "AudioSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "ECS.h"


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
	auto entity = std::any_cast<Entity>(message.GetData());

	if (auto* audioComponent = m_ecs->GetComponent<AudioComponent>(entity))
	{
		if (audioComponent->SoundTriggers.contains(type))
		{
			// Todo; fetch Audio and pass the audio file instead..

			const auto& audioName = audioComponent->SoundTriggers.at(type);

			auto& audio = Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource(audioName);
			Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>(&audio);
		}
	}
}

void AudioSystem::Update(float deltaTime)
{
}

void AudioSystem::SetSignature()
{
	//m_signatures.insert({ "Audios", m_ecs->GetSignature<AudioComponent>() });
}
