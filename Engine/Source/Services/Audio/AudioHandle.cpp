#include "Pch.h"
#include "AudioHandle.h"
#include "AudioClip.h"
#include <irrKlang.h>
#include "AudioHandle.h"

namespace Hi_Engine
{
	AudioHandle::AudioHandle(irrklang::ISound* sound)
		: m_sound{ sound }
	{
	}

	AudioHandle::~AudioHandle()
	{
		if (m_sound && !m_sound->isFinished())
			m_sound->stop();
	}

	void AudioHandle::Pause()
	{
		if (m_sound)
		{
			m_sound->setIsPaused(true);
		}
	}

	void AudioHandle::Resume()
	{
		if (m_sound)
		{
			m_sound->setIsPaused(false);
		}
	}

	void AudioHandle::Stop()
	{
		if (m_sound)
		{
			m_sound->stop();
		}
	}

	void AudioHandle::SetVolume(float vol)
	{
		if (m_sound)
			m_sound->setVolume(vol);
	}

	void AudioHandle::SetLooping(bool shouldLoop)
	{
		if (m_sound)
			m_sound->setIsLooped(shouldLoop);
	}

	bool AudioHandle::IsFinished() const
	{
		return m_sound && m_sound->isFinished();
	}

	bool AudioHandle::IsPlaying() const
	{
		return !IsFinished() && !IsPaused();
	}

	bool AudioHandle::IsPaused() const
	{
		return m_sound && m_sound->getIsPaused();
	}

	bool AudioHandle::IsLooping() const
	{
		return m_sound && m_sound->isLooped();
	}

	float AudioHandle::GetVolume() const
	{
		return m_sound ? m_sound->getVolume() : 0.f;
	}
}