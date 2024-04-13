#pragma once

namespace irrklang
{
	class ISound;
	class ISoundEngine;
}

namespace Hi_Engine
{
	class AudioSource;

	class Audio
	{
	public:
		Audio(AudioSource* source = nullptr);

		void Init(AudioSource* source);

		bool Play(irrklang::ISoundEngine* engine);
		void Stop();
		// const AudioSource& GetSource() const;

	private:
		AudioSource*		m_source;
		irrklang::ISound*	m_sound;
	};
}