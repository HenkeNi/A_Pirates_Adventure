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
	}

	bool Audio::Play(irrklang::ISoundEngine* engine)
	{
		if (!m_source)
			return false;

		m_sound = engine->play2D(m_source->GetSource());
		return true;
	}

	void Audio::Stop()
	{
		m_sound->stop();
	}

	//const AudioSource& Audio::GetSource() const
	//{
	//	return m_source;
	//}
}