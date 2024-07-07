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
		void Init(AudioSource* source);
		//void Init(const std::string& sound);
	
		inline const AudioSource* GetSource() const { return m_source; }
		inline AudioSource* GetSource() { return m_source; }
		//const std::string GetSoundName() const;
		
	private:
		AudioSource* m_source;
		bool m_isLooping;
		//std::string m_soundName;
	};


	class StopSoundEvent : public Event<StopSoundEvent>
	{
	public:
		StopSoundEvent();

		void Dispatch(EventListener& listener) override;
		//void Init(const std::string& sound);
		void Init(AudioSource* audio);
		
		inline const AudioSource* GetSource() const { return m_source; }
		inline AudioSource* GetSource() { return m_source; }

		//const std::string GetSoundName() const;

	private:
		AudioSource* m_source;

		//std::string m_soundName;
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


