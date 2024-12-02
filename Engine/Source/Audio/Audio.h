#pragma once

namespace irrklang
{
	class ISound;
	//class ISoundEngine;
}

namespace Hi_Engine
{
	class AudioSource;
	class AudioController;

	class Audio
	{
	public:
		Audio(AudioSource* source = nullptr);

		void Init(AudioSource* source);

		void SetVolume(float volume);
		void SetIsLooping(bool isLooping);
		void SetSound(irrklang::ISound* sound);

		//inline AudioSource* GetSource() { return m_source; }
		// inline irrklang::ISound* GetSound() { return m_sound; }
		bool IsLooping() const;
		
	private:
		friend class AudioController;

		AudioSource*		m_source;
		irrklang::ISound*	m_sound;
	};
}