#include "Pch.h"
#include "AudioController.h"
#include "AudioSource.h"
#include "Audio.h"
#include "Resources/ResourceHolder.hpp"
#include "../Messaging/Events/Audio/AudioEvents.h"
#include <irrKlang.h>

namespace Hi_Engine
{
	AudioController::AudioController()
	// 	: m_soundEngine{ nullptr }
	{
		Dispatcher::GetInstance().Subscribe(this);
	}

	AudioController::~AudioController()
	{
		Dispatcher::GetInstance().Unsubscribe(this);
	}

	bool AudioController::Init()
	{
		m_soundEngine = irrklang::createIrrKlangDevice();
		if (!m_soundEngine)
		{
			std::cout << "Failed to boot up ISoundEngine!\n";
			return false;
		}

		return true;

		//m_activeSounds.insert(std::make_pair(1, m_soundEngine->play2D("../Game/Assets/Sound/test.mp3", true)));
		//auto* sound = m_soundEngine->addSoundSourceFromFile("	../Game/Assets/Sound/test.mp3");
		//m_soundEngine->play2D(sound);

		//auto* sound = m_soundEngine->addSoundSourceFromFile("../Game/Assets/Sound/bloodpixelhero_adventure-theme-5.wav");
		//m_soundEngine->play2D(sound);
	}

	void AudioController::Shutdown()
	{
		if (m_soundEngine)
			m_soundEngine->drop();
	}

	void AudioController::Update()
	{
		if (m_activeSounds.at(1)->isFinished())
			std::cout << "Sounds is finise\n";
			//m_activeSounds.at(1)->stop();
	}

	void AudioController::HandleEvent(PlaySoundEvent& event)
	{
		PlaySound(event.GetSoundName());
	}

	void AudioController::HandleEvent(StopSoundEvent& event)
	{
		StopSound(event.GetSoundName());
	}

	void AudioController::PlaySound(const std::string& name)
	{
		auto& sound = ResourceHolder<AudioSource>::GetInstance().GetResource(name);
		m_soundEngine->play2D(sound.m_source, sound.m_isLooping);
	}

	void AudioController::StopSound(const std::string& name)
	{
		auto& sound = ResourceHolder<AudioSource>::GetInstance().GetResource(name);
		m_soundEngine->stopAllSoundsOfSoundSource(sound.m_source);
	}

	void AudioController::PlaySound(Audio& audio)
	{
		audio.Play(m_soundEngine); // DonT? Instead just get / set the data in audio?

		// add to array of current sounds??
	}

	void AudioController::StopSound(Audio& audio)
	{
		audio.Stop();
	}

	void AudioController::PlaySound(const AudioSource& source)
	{
		m_soundEngine->play2D(source.m_source, source.m_isLooping);
	}

	void AudioController::StopSound(const AudioSource& source)
	{
		m_soundEngine->stopAllSoundsOfSoundSource(source.m_source);
	}






	//void AudioController::PlaySound(const std::string& path)
	//{
	//	m_soundEngine->play2D(path.c_str());
	//}
	//void AudioController::PlaySound(const AudioSource& source)
	//{
	//	std::cout << source.m_source->getName() << "\n";

	//	// m_soundEngine->play2D(source.m_source->getName());
	//	//m_soundEngine->play2D("../Game/Assets/Sound/bloodpixelhero_adventure-theme-5.wav");
	//	//m_soundEngine->play2D(source.m_source);
	//	m_soundEngine->play2D(source.m_source, source.m_isLooping);
	//}
	//void AudioController::PlaySound(const AudioSource& source, irrklang::ISound* sound)
	//{
	//	sound = m_soundEngine->play2D(source.m_source);
	//}


}