#pragma once
#include "../IService.h"

namespace irrklang
{
	class ISoundEngine;
	class ISound;
}

namespace Hi_Engine
{
	class Audio;
	class AudioSource;

	class AudioService : public IService
	{
	public:
		AudioService();
		~AudioService();

		bool Initialize();
		void Shutdown() override;
		void Update();

		void PlaySound(const char* sound); // prefere passing actual audio. Store ResourceService ref in AudioSystem instead..
		void StopSound(const char* sound);

		static inline irrklang::ISoundEngine* GetEngine() { return m_soundEngine; }

	private:

		std::unordered_map<unsigned, irrklang::ISound*> m_activeSounds;
		static inline irrklang::ISoundEngine* m_soundEngine = nullptr;

		float m_volume;
	};
}