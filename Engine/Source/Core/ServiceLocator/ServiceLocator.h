#pragma once

namespace Hi_Engine
{
	class AudioController;
	
	class ServiceLocator
	{
	public:
		static AudioController* GetAudioController(); // Pass back a wrapper to AudioController?

		static void Register(AudioController* controller);

		// static Renderer* GetRenderer(); returns interface to renderer...

	private:
		static AudioController* s_audioController;
	};
}
