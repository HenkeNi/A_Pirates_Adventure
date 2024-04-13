#pragma once

namespace irrklang
{
	class ISoundSource;
}

class AudioController;

namespace Hi_Engine
{
	class AudioSource // derive from SOundSource?
	{
	public:
		AudioSource(irrklang::ISoundSource* source = nullptr);
		~AudioSource();

		//void SetSource(irrklang::ISoundSource* source);
		void SetSource(const std::string& path);
		void SetIsLooping(bool isLooping);

		
		inline irrklang::ISoundSource* GetSource() { return m_source; }
		inline const irrklang::ISoundSource* GetSource() const { return m_source; }

	private:
		friend class AudioController;

		irrklang::ISoundSource* m_source;
		bool m_isLooping;	// dont store here??
	};
}