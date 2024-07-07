#include "Pch.h"
#include "AudioSource.h"
#include "irrKlang.h"
#include "../Audio/AudioController.h"

namespace Hi_Engine
{
	AudioSource::AudioSource(irrklang::ISoundSource* source)
		: m_source{ source }, m_isLooping{ false }
	{
	}

	AudioSource::~AudioSource()
	{
		// m_source->
	}

	void AudioSource::Init(const rapidjson::Value& value)
	{
		std::string name = value["name"].GetString();
		std::string path = value["filepath"].GetString();
		bool isLooping = value["is_looping"].GetBool();

		SetSource(path);
		m_isLooping = isLooping;
		m_name = name;
	}

	void AudioSource::SetSource(const std::string& path)
	{
		auto* engine = AudioController::GetEngine();
		m_source = engine->addSoundSourceFromFile(path.c_str());

		if (!m_source)
			std::cout << "ERROR loading audio";
	}

	void AudioSource::SetIsLooping(bool isLooping)
	{
		m_isLooping = isLooping;
	}
}