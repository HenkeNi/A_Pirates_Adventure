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

	class AudioController : public Module
	{
	public:
		AudioController(ModuleManager& manager);
		~AudioController();

		bool Init() override;
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