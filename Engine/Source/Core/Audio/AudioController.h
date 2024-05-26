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

	class AudioController : public Module // audio manager? No need for a controller? let ikrlang ive in engine?
	{
	public:
		AudioController();

		void Init();
		void Shutdown();

		void Update();

		// PlaySoundEffect()?
		
		void PlaySound(Audio& audio);
		void StopSound(Audio& audio);




		//void PlaySound(const std::string& path);

		void PlaySound(const AudioSource& source);
		void StopSound(const AudioSource& source); // Rename stop all sounds of type?

		//void PlaySound(const AudioSource& source, irrklang::ISound* sound);


		static inline irrklang::ISoundEngine* GetEngine() { return m_soundEngine; }

	private:

		std::unordered_map<unsigned, irrklang::ISound*> m_activeSounds;
		static inline irrklang::ISoundEngine* m_soundEngine = nullptr;

		float m_volume;
	};
}