#include "Pch.h"
#include "AudioEvents.h"
#include "../ECS/Utility/EntityHandle.h"


namespace Hi_Engine
{
	PlaySoundEvent::PlaySoundEvent(EntityHandle* entityHandle)
		: Event{ ePriority::Moderate }, m_entityHandle{ entityHandle } //, m_soundName{ "" }, m_isLooping{ false }
	{
	}

	/*PlaySoundEvent::PlaySoundEvent(const char* name, bool shouldLoop)
		: Event{ ePriority::Moderate }, m_soundName{ name }, m_isLooping{ shouldLoop }
	{
	}*/

	/*void PlaySoundEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}*/

	

	StopSoundEvent::StopSoundEvent()
		: Event{ ePriority::Moderate }, m_soundName{ "" }
	{
	}

	StopSoundEvent::StopSoundEvent(const char* name)
		: Event{ ePriority::Moderate }, m_soundName{ name }
	{
	}

	/*void StopSoundEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}*/



	SetVolumeEvent::SetVolumeEvent()
		: Event{ ePriority::Moderate }, m_volume{ 1.f }
	{
	}

	SetVolumeEvent::SetVolumeEvent(float volume)
		: Event{ ePriority::Moderate }, m_volume{ volume }
	{
	}

	/*void SetVolumeEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}*/

	float SetVolumeEvent::GetVolume() const
	{
		return m_volume;
	}
	
}
