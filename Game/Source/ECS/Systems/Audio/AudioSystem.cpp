#include "Pch.h"
#include "AudioSystem.h"
#include "Components/Core/CoreComponents.h"
#include "ECS.h"


AudioSystem::AudioSystem()
{
	// Audio trigger component instead?? 
	PostMaster::GetInstance().Subscribe(eMessage::EntityAttacked, this);
	PostMaster::GetInstance().Subscribe(eMessage::EntityDestroyed, this); // TODO if contain a looping sound => stop it
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
	assert(m_ecs && "[AudioSystem - ERROR]: ECS is not initialized!");

	auto type = message.GetMessageType();
	auto entity = std::any_cast<Entity>(message.GetData());

	if (auto* audioComponent = m_ecs->GetComponent<AudioComponent>(entity))
	{
		if (audioComponent->SoundTriggers.contains(type))
		{
			const auto& audioName = audioComponent->SoundTriggers.at(type);
			Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>(audioName.c_str());
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
