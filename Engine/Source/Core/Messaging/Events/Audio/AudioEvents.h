#pragma once
#include "../Base/Event.h"

namespace Hi_Engine
{
	class AudioSource;

	class PlaySoundEvent : public Event<PlaySoundEvent>
	{
	public:
		PlaySoundEvent();

		void Dispatch(EventListener& listener) override;
		void Init(const char* name);
	
		inline const char* GetSoundName() const { return m_soundName; }
	
	private:
		const char* m_soundName;
		bool m_isLooping;
	};


	class StopSoundEvent : public Event<StopSoundEvent>
	{
	public:
		StopSoundEvent();

		void Dispatch(EventListener& listener) override;
		void Init(const char* name);

		inline const char* GetSoundName() const { return m_soundName; }

	private:
		const char* m_soundName;
	};


	class SetVolumeEvent : public Event<SetVolumeEvent>
	{
	public:
		SetVolumeEvent();

		void Dispatch(EventListener& listener) override;
		void Init(float volume);
		
		float GetVolume() const;

	private:
		float m_volume;
	};
}


