#pragma once
#include "../Base/Event.h"

namespace Hi_Engine
{
	class PlaySoundEvent : public Event<PlaySoundEvent>
	{
	public:
		PlaySoundEvent();

		void Dispatch(EventListener& listener) override;
		void Init(const std::string& sound);
	
		const std::string GetSoundName() const;
		
	private:
		std::string m_soundName;
	};


	class StopSoundEvent : public Event<StopSoundEvent>
	{
	public:
		StopSoundEvent();

		void Dispatch(EventListener& listener) override;
		void Init(const std::string& sound);
		
		const std::string GetSoundName() const;

	private:
		std::string m_soundName;
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


