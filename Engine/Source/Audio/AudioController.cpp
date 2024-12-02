#include "Pch.h"
#include "AudioController.h"
#include "AudioSource.h"
#include "Audio.h"
#include "Resources/ResourceHolder.h"
#include "../Core/EventSystem/Events/AudioEvents.h"
#include <irrKlang.h>

namespace Hi_Engine
{
	AudioController::AudioController(int initOrder)
		: Module{ initOrder } //, m_soundEngine{ nullptr }
	{
		EventDispatcher::GetInstance().Subscribe(this);
	}

	AudioController::~AudioController()
	{
		EventDispatcher::GetInstance().Unsubscribe(this);
	}

	bool AudioController::Init()
	{
		m_soundEngine = irrklang::createIrrKlangDevice();
		if (!m_soundEngine)
		{
			std::cerr << "Failed to boot up ISoundEngine!\n";
			return false;
		}

		return true;
	}

	void AudioController::Shutdown()
	{
		if (m_soundEngine)
			m_soundEngine->drop();
	}

	void AudioController::Update()
	{
		if (m_activeSounds.at(1)->isFinished())
			std::cout << "Sounds is finise\n"; // send evnet?
			//m_activeSounds.at(1)->stop();
	}

	void AudioController::HandleEvent(PlaySoundEvent& event)
	{
		if (auto sound = event.GetSoundName())
		{
			PlaySound(sound);
		}

		//PlaySound(event.GetAudio());
	}

	void AudioController::HandleEvent(StopSoundEvent& event)
	{
		if (auto sound = event.GetSoundName())
		{
			StopSound(sound);
		}
	}

	void AudioController::HandleEvent(SetVolumeEvent& event)
	{
		m_soundEngine->setSoundVolume(event.GetVolume());
	}

	/*void AudioController::PlaySound(const std::string& name)
	{
		auto& sound = ResourceHolder<AudioSource>::GetInstance().GetResource(name);
		m_soundEngine->play2D(sound.m_source, sound.m_isLooping);
	}

	void AudioController::StopSound(const std::string& name)
	{
		auto& sound = ResourceHolder<AudioSource>::GetInstance().GetResource(name);
		m_soundEngine->stopAllSoundsOfSoundSource(sound.m_source);
	}*/

	void AudioController::PlaySound(const char* sound)
	{
		auto audio = ResourceHolder<AudioSource>::GetInstance().GetResource(sound);
		m_soundEngine->play2D(audio->GetSource(), false);

		//if (auto* audioSource = audio.GetSource())
		//if (auto* audioSource = source.m_source)
		//{
		//	auto* sound = m_soundEngine->play2D(audioSource, false);
		//	//auto* sound = m_soundEngine->play2D(audioSource, audio.IsLooping());
		//	//audio.SetSound(sound);
		//}

		//audio.Play(m_soundEngine); // DonT? Instead just get / set the data in audio?

		// add to array of current sounds??
	}

	void AudioController::StopSound(const char* sound)
	{
		auto audio = ResourceHolder<AudioSource>::GetInstance().GetResource(sound);
		m_soundEngine->stopAllSoundsOfSoundSource(audio->GetSource());


		// audio.m_sound->stop();
		//audio.GetSound()->stop();

		//audio.Stop();
	}

	//void AudioController::PlaySound(const AudioSource& source)
	//{
	//	m_soundEngine->play2D(source.m_source, source.m_isLooping);
	//}

	//void AudioController::StopSound(const AudioSource& source)
	//{
	//	m_soundEngine->stopAllSoundsOfSoundSource(source.m_source);
	//}






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