#include "Pch.h"
#include "AudioClip.h"
#include "AudioService.h"
#include "irrKlang.h"

namespace Hi_Engine
{
	AudioClip::AudioClip(irrklang::ISoundSource* source, std::string name, bool shouldLoop)
		: m_source{ source }, m_name{ std::move(name) }, m_isLooping{ shouldLoop }
	{
	}

	AudioClip::~AudioClip()
	{
	}

	void AudioClip::SetSource(irrklang::ISoundSource* source)
	{
		m_source = source;
	}

	void AudioClip::SetIsLooping(bool isLooping)
	{
		m_isLooping = isLooping;
	}
}