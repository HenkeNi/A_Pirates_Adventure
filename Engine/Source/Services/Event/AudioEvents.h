#pragma once
#include "Event.h"

namespace Hi_Engine
{
	class AudioSource;

	class PlaySoundEvent : public Event<PlaySoundEvent>
	{
	public:
		PlaySoundEvent();
		PlaySoundEvent(const char* name, bool shouldLoop);

		//void Dispatch(EventListener& listener) override;
	
		inline const char* GetSoundName() const { return m_soundName; }
	
	private:
		const char* m_soundName;
		bool m_isLooping;
	};


	class StopSoundEvent : public Event<StopSoundEvent>
	{
	public:
		StopSoundEvent();
		StopSoundEvent(const char* name);

		//void Dispatch(EventListener& listener) override;

		inline const char* GetSoundName() const { return m_soundName; }

	private:
		const char* m_soundName;
	};


	class SetVolumeEvent : public Event<SetVolumeEvent>
	{
	public:
		SetVolumeEvent();
		SetVolumeEvent(float volume);

		//void Dispatch(EventListener& listener) override;
		
		float GetVolume() const;

	private:
		float m_volume;
	};
}


