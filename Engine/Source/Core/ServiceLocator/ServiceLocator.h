#pragma once

namespace Hi_Engine
{
	class Window;
	//class AudioController;
	class Window;
	
	class ServiceLocator
	{
	public:
	// static std::weak_ptr<AudioController> GetAudioController(); // Pass back a wrapper to AudioController?

	// static void Register(std::weak_ptr<AudioController> controller);

	// static Renderer* GetRenderer(); returns interface to renderer...

		static void Register(std::weak_ptr<Window> window);

		static std::weak_ptr<Window> GetWindow();

	private:
		//static std::weak_ptr<AudioController> s_audioController;
		inline static std::weak_ptr<Window> s_window;
	};
}
