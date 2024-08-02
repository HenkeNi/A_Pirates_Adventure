#include "Pch.h"
#include "AudioEvents.h"


namespace Hi_Engine
{
	PlaySoundEvent::PlaySoundEvent()
		: Event{ ePriority::Moderate }, m_soundName{ "" }, m_isLooping{ false }
	{
	}

	void PlaySoundEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}

	void PlaySoundEvent::Init(const char* name)
	{
		m_soundName = name;
	}
	


	StopSoundEvent::StopSoundEvent()
		: Event{ ePriority::Moderate }, m_soundName{ "" }
	{
	}

	void StopSoundEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}

	void StopSoundEvent::Init(const char* name)
	{
		m_soundName = name;

	}


	SetVolumeEvent::SetVolumeEvent()
		: Event{ ePriority::Moderate }, m_volume{ 1.f }
	{
	}

	void SetVolumeEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}

	void SetVolumeEvent::Init(float volume)
	{
		m_volume = volume;
	}

	float SetVolumeEvent::GetVolume() const
	{
		return m_volume;
	}
}
