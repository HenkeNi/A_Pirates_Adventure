#include "Pch.h"
#include "AudioService.h"
#include "AudioClip.h"
#include "AudioHandle.h"
#include "Services/Resource/ResourceService.h"
#include "Services/Event/AudioEvents.h"
#include <irrKlang.h>

namespace Hi_Engine
{
	AudioService::AudioService()
		: m_soundEngine{ nullptr }
	{
	}

	AudioService::~AudioService()
	{
	}

	bool AudioService::Initialize()
	{
		m_soundEngine = irrklang::createIrrKlangDevice();

		if (!m_soundEngine)
		{
			Logger::LogError("AudioController::Init - Failed to boot up ISoundEngine!");
			return false;
		}

		return true;
	}

	void AudioService::Shutdown() noexcept
	{
		if (m_soundEngine)
			m_soundEngine->drop();
	}

	//void AudioController::HandleEvent(PlaySoundEvent& event)
	//{
	//	if (auto sound = event.GetSoundName())
	//	{
	//		PlaySound(sound);
	//	}

	//	//PlaySound(event.GetAudio());
	//}

	//void AudioController::HandleEvent(StopSoundEvent& event)
	//{
	//	if (auto sound = event.GetSoundName())
	//	{
	//		StopSound(sound);
	//	}
	//}

	//void AudioController::HandleEvent(SetVolumeEvent& event)
	//{
	//	m_soundEngine->setSoundVolume(event.GetVolume());
	//}

	/*void AudioController::StopSound(const std::string& name)
	{
		m_soundEngine->stopAllSoundsOfSoundSource(sound.m_source);
	}*/

	AudioHandle AudioService::PlaySound(AudioClip* clip, bool shouldLoop)
	{
		if (m_soundEngine)
		{
			auto* sound = m_soundEngine->play2D(clip->GetSource(), shouldLoop);
			return AudioHandle{ sound };
		}

		return AudioHandle{};
	}

	//void AudioService::StopSound(const char* sound)
	//{
	//	//auto audio = ResourceHolder<AudioSource>::GetInstance().GetResource(sound);
	//	//m_soundEngine->stopAllSoundsOfSoundSource(audio->GetSource());
	//	//audio.Stop();
	//}

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