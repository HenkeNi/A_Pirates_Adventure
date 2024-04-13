#include "Pch.h"
#include "AudioController.h"
#include "AudioSource.h"
#include "Audio.h"
#include <irrKlang.h>

namespace Hi_Engine
{
	AudioController::AudioController()
	// 	: m_soundEngine{ nullptr }
	{
	}

	void AudioController::Init()
	{
		m_soundEngine = irrklang::createIrrKlangDevice();
		if (!m_soundEngine)
		{
			std::cout << "Failed to boot up ISoundEngine!\n";
			return;
		}

		//m_activeSounds.insert(std::make_pair(1, m_soundEngine->play2D("../Game/Assets/Sound/test.mp3", true)));
		//auto* sound = m_soundEngine->addSoundSourceFromFile("../Game/Assets/Sound/test.mp3");
		//m_soundEngine->play2D(sound);

		//auto* sound = m_soundEngine->addSoundSourceFromFile("../Game/Assets/Sound/bloodpixelhero_adventure-theme-5.wav");
		//m_soundEngine->play2D(sound);
	}

	void AudioController::Shutdown()
	{
		m_soundEngine->drop();
	}

	void AudioController::Update()
	{
		if (m_activeSounds.at(1)->isFinished())
			std::cout << "Sounds is finise\n";
			//m_activeSounds.at(1)->stop();
	}

	void AudioController::PlaySound(Audio& audio)
	{
		audio.Play(m_soundEngine); // DonT? Instead just get / set the data in audio?
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