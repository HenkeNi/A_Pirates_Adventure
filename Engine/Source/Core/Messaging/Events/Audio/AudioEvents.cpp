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
	
	//void PlaySoundEvent::Init(const std::string& sound)
	void PlaySoundEvent::Init(AudioSource* source)
	{
		m_source = source;
	}

	//const std::string PlaySoundEvent::GetSoundName() const
	//{
	//	return m_soundName;
	//}


	StopSoundEvent::StopSoundEvent()
		: Event{ ePriority::Moderate }
	{
	}

	void StopSoundEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}

	void StopSoundEvent::Init(AudioSource* source)
	{
		m_source = source;
	}
	
	/*void StopSoundEvent::Init(const std::string& sound)
	{
		m_soundName = sound;
	}

	const std::string StopSoundEvent::GetSoundName() const
	{
		return m_soundName;
	}*/


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
