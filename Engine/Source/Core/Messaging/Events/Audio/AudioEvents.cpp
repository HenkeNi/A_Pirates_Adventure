#include "Pch.h"
#include "AudioEvents.h"


namespace Hi_Engine
{
	PlaySoundEvent::PlaySoundEvent()
		: Event{ ePriority::Moderate }
	{
	}

	void PlaySoundEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}
	
	void PlaySoundEvent::Init(const std::string& sound)
	{
		m_soundName = sound;
	}

	const std::string PlaySoundEvent::GetSoundName() const
	{
		return m_soundName;
	}


	StopSoundEvent::StopSoundEvent()
		: Event{ ePriority::Moderate }
	{
	}

	void StopSoundEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}
	
	void StopSoundEvent::Init(const std::string& sound)
	{
		m_soundName = sound;
	}

	const std::string StopSoundEvent::GetSoundName() const
	{
		return m_soundName;
	}
}
