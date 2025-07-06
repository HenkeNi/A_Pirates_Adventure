#include "Pch.h"
#include "AudioSource.h"
#include "AudioService.h"
#include "irrKlang.h"

namespace Hi_Engine
{
	AudioSource::AudioSource(irrklang::ISoundSource* source)
		: m_source{ source }, m_isLooping{ false }
	{
	}

	AudioSource::~AudioSource()
	{
	}

	void AudioSource::Init(const rapidjson::Value& value)
	{
		m_name = value["name"].GetString();
		m_isLooping = value["is_looping"].GetBool();
		
		std::string path = value["filepath"].GetString();

		auto* engine = AudioService::GetEngine();

		m_source = engine->addSoundSourceFromFile(path.c_str());
		if (!m_source)
		{
			std::cerr << "ERROR: loading audio " << m_name << "\n";
			return;
		}
	}

	void AudioSource::SetSource(irrklang::ISoundSource* source)
	{
		m_source = source;
	}

	void AudioSource::SetIsLooping(bool isLooping)
	{
		m_isLooping = isLooping;
	}
}