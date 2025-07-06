#include "Pch.h"
#include "Audio.h"
#include "AudioSource.h"
#include <irrKlang.h>

namespace Hi_Engine
{
	Audio::Audio(AudioSource* source)
		: m_source{ source }, m_sound{ nullptr }
	{
	}

	void Audio::Init(AudioSource* source)
	{
		m_source = source;
		m_sound->setIsLooped(source->GetIsLooping());
	}

	void Audio::SetVolume(float volume)
	{
		m_sound->setVolume(volume);
	}

	void Audio::SetIsLooping(bool isLooping)
	{
		m_sound->setIsLooped(isLooping);
	}

	void Audio::SetSound(irrklang::ISound* sound)
	{
		m_sound = sound;
	}

	bool Audio::IsLooping() const 
	{ 
		return m_source->GetIsLooping(); 
	}

	//bool Audio::Play(irrklang::ISoundEngine* engine)
	//{
	//	if (!m_source)
	//		return false;

	//	m_sound = engine->play2D(m_source->GetSource());
	//	return true;
	//}

	//void Audio::Stop()
	//{
	//	m_sound->stop();
	//}

	//const AudioSource& Audio::GetSource() const
	//{
	//	return m_source;
	//}
}