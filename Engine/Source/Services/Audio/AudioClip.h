#pragma once

namespace irrklang
{
	class ISoundSource;
}

namespace Hi_Engine
{
	class AudioClip 
	{
	public:
		AudioClip(irrklang::ISoundSource* source, std::string name, bool shouldLoop); 
		~AudioClip();

		void SetSource(irrklang::ISoundSource* source);
		void SetIsLooping(bool isLooping);

		[[nodiscard]] inline const std::string& GetName() const { return m_name; }
		[[nodiscard]] inline bool GetIsLooping() const { return m_isLooping; }

		[[nodiscard]] inline const irrklang::ISoundSource* GetSource() const { return m_source; }
		[[nodiscard]] inline irrklang::ISoundSource* GetSource() { return m_source; }

	private:
		irrklang::ISoundSource* m_source;
		std::string m_name;
		bool m_isLooping;	// dont store here??
	};
}