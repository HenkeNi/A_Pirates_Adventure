#pragma once
#include "../IService.h"

namespace irrklang
{
	class ISoundEngine;
	//class ISound;
}

namespace Hi_Engine
{
	class AudioHandle;
	class AudioClip;

	class AudioService : public IService
	{
	public:
		AudioService();
		~AudioService();

		bool Initialize();
		void Shutdown() noexcept override;

		AudioHandle PlaySound(AudioClip* clip, bool shouldLoop = false);
		//void StopSound(const char* sound);

		void StopAll();
		void SetMasterVolume();

		inline irrklang::ISoundEngine* GetEngine() { return m_soundEngine; } // not static? fetch service instead?? 

	private:

		//std::unordered_map<unsigned, irrklang::ISound*> m_activeSounds;
		irrklang::ISoundEngine* m_soundEngine;

		// store loaded sound sources here?? lazy load (only load when needed)

		float m_volume; // master volume?
	};
}