#pragma once
#include "../Modules/Base/Module.h"

namespace irrklang
{
	class ISoundEngine;
	class ISound;
}

namespace Hi_Engine
{
	class Audio;
	class AudioSource;

	class AudioController : public Module, public EventListener // audio manager? No need for a controller? let ikrlang ive in engine?
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
		
		void PlaySound(const std::string& name);
		void PlaySound(const AudioSource& source);
		void PlaySound(Audio& audio);

		void StopSound(const std::string& name);
		
		// PlaySoundEffect()?
		
		void StopSound(Audio& audio);




		//void PlaySound(const std::string& path);

		void StopSound(const AudioSource& source); // Rename stop all sounds of type?

		//void PlaySound(const AudioSource& source, irrklang::ISound* sound);


		static inline irrklang::ISoundEngine* GetEngine() { return m_soundEngine; }

	private:

		std::unordered_map<unsigned, irrklang::ISound*> m_activeSounds;
		static inline irrklang::ISoundEngine* m_soundEngine = nullptr;

		float m_volume;
	};
}