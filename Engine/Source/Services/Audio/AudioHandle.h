#pragma once

namespace irrklang
{
	class ISound;
}

namespace Hi_Engine
{
	class AudioHandle
	{
	public:
		AudioHandle(irrklang::ISound* sound = nullptr);
		~AudioHandle();

		void Pause();
		
		void Resume();
		
		void Stop();

		void SetVolume(float vol);
		
		void SetLooping(bool shouldLoop);

		[[nodiscard]] bool IsFinished() const;
		
		[[nodiscard]] bool IsPlaying() const;
		
		[[nodiscard]] bool IsPaused() const;
		
		[[nodiscard]] bool IsLooping() const;

		[[nodiscard]] float GetVolume() const;

	private:
		irrklang::ISound* m_sound;
	};
}