#include "Pch.h"
#include "EngineConfig.h"

namespace Hi_Engine
{
	struct EngineConfig::Impl
	{
		AudioConfig m_audioConfig;
		InputConfig m_inputConfig;
		WindowConfig m_windowConfig;
		RendererConfig m_rendererConfig;
		
		void LoadFromFile(const char* path)
		{
			auto doc = ParseDocument(path);

			if (doc.HasMember("window") && doc["window"].IsObject())
				ParseWindowConfig(doc["window"].GetObject());
			
			if (doc.HasMember("renderer") && doc["renderer"].IsObject())
				ParseRendererConfig(doc["renderer"].GetObject());

			if (doc.HasMember("audio") && doc["audio"].IsObject())
				ParseAudioConfig(doc["audio"].GetObject());
			
			if (doc.HasMember("input") && doc["input"].IsObject())
				ParseInputConfig(doc["input"].GetObject());
		}

		void ParseWindowConfig(const rapidjson::Value& obj)
		{
			if (obj.HasMember("width") && obj["width"].IsInt())
				m_windowConfig.Width = obj["width"].GetInt();

			if (obj.HasMember("height") && obj["height"].IsInt())
				m_windowConfig.Height = obj["height"].GetInt();

			if (obj.HasMember("fullscreen") && obj["fullscreen"].IsBool())
				m_windowConfig.Fullscreen = obj["fullscreen"].GetBool();
		}

		void ParseRendererConfig(const rapidjson::Value& obj)
		{
			if (obj.HasMember("type") && obj["type"].IsString())
				m_rendererConfig.Type = obj["type"].GetString();
		}
		
		void ParseAudioConfig(const rapidjson::Value& obj)
		{
			if (obj.HasMember("type") && obj["type"].IsString())
				m_audioConfig.Type = obj["type"].GetString();
			
			if (obj.HasMember("volume") && obj["volume"].IsFloat())
				m_audioConfig.MasterVolume = obj["volume"].GetFloat();
		}

		void ParseInputConfig(const rapidjson::Value& obj)
		{
			if (obj.HasMember("type") && obj["type"].IsString())
				m_inputConfig.Type = obj["type"].GetString();
		}
	};

	EngineConfig::EngineConfig()
		: m_impl{ std::make_unique<Impl>() }
	{
	}

	EngineConfig::~EngineConfig()
	{
	}

	void EngineConfig::LoadFromFile(const char* path)
	{
		m_impl->LoadFromFile(path);
	}

	const char* EngineConfig::GetWindowType() const
	{
		return m_impl->m_windowConfig.Type;
	}

	int EngineConfig::GetWindowWidth() const
	{
		return m_impl->m_windowConfig.Width;
	}

	int EngineConfig::GetWindowHeight() const
	{
		return m_impl->m_windowConfig.Height;
	}

	bool EngineConfig::IsWindowFullscreen() const
	{
		return m_impl->m_windowConfig.Fullscreen;
	}

	const char* EngineConfig::GetRendererType() const
	{
		return m_impl->m_rendererConfig.Type;
	}

	const char* EngineConfig::GetAudioType() const
	{
		return m_impl->m_audioConfig.Type;
	}

	float EngineConfig::GetMasterVolume() const
	{
		return m_impl->m_audioConfig.MasterVolume;
	}

	const char* EngineConfig::GetInputType() const
	{
		return m_impl->m_inputConfig.Type;
	}

	float EngineConfig::GetMouseSensitivity() const
	{
		return m_impl->m_inputConfig.MouseSensitivity;
	}
}