#pragma once

namespace irrklang
{
	class ISoundSource;
}

namespace Hi_Engine
{
	class AudioController;
	
	class AudioSource
	{
	public:
		AudioSource(irrklang::ISoundSource* source = nullptr);
		~AudioSource();

		void Init(const rapidjson::Value& value);
		void SetSource(irrklang::ISoundSource* source);
		void SetIsLooping(bool isLooping);

		inline const std::string& GetName() const { return m_name; }
		inline const irrklang::ISoundSource* GetSource() const { return m_source; }
		inline irrklang::ISoundSource* GetSource() { return m_source; }
		inline bool GetIsLooping() const { return m_isLooping; }

	private:
		friend class AudioController;

		irrklang::ISoundSource* m_source;
		std::string m_name;
		bool m_isLooping;	// dont store here??
	};
}