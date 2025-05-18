#pragma once
#include "../Service/IService.h"

namespace irrklang
{
	class ISoundEngine;
	class ISound;
}

namespace Hi_Engine
{
	class Audio;
	class AudioSource;

	class AudioController : public IService
	{
	public:
		AudioController();
		~AudioController();

		bool Initialize();
		void Shutdown() override;
		void Update();

		void PlaySound(const char* sound);
		void StopSound(const char* sound);

		static inline irrklang::ISoundEngine* GetEngine() { return m_soundEngine; }

	private:

		std::unordered_map<unsigned, irrklang::ISound*> m_activeSounds;
		static inline irrklang::ISoundEngine* m_soundEngine = nullptr;

		float m_volume;
	};
}