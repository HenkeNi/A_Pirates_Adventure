#pragma once
#include "../Core/Modules/Module.h"

namespace irrklang
{
	class ISoundEngine;
	class ISound;
}

namespace Hi_Engine
{
	class Audio;
	class AudioSource;

	class AudioController : public Module, public EventListener
	{
	public:
		AudioController(int initOrder);
		~AudioController();

		bool Init() override;
		void Shutdown() override;
		void Update();

		void HandleEvent(class PlaySoundEvent& event) override;
		void HandleEvent(class StopSoundEvent& event) override;
		void HandleEvent(class SetVolumeEvent& event) override;
		
		void PlaySound(const char* sound);
		void StopSound(const char* sound);

		static inline irrklang::ISoundEngine* GetEngine() { return m_soundEngine; }

	private:

		std::unordered_map<unsigned, irrklang::ISound*> m_activeSounds;
		static inline irrklang::ISoundEngine* m_soundEngine = nullptr;

		float m_volume;
	};
}