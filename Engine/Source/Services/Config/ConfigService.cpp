#include "Pch.h"
#include "ConfigService.h"

namespace Hi_Engine
{
	void ParseRendererConfig(const rapidjson::Value& obj, RendererConfig& config)
	{
		config.Type = JsonUtils::GetJsonVale<std::string>(obj, "type", "OpenGLRenderer");
	}

	void ParsePhysicsConfig(const rapidjson::Value& obj, PhysicsConfig& config)
	{
		config.Type = JsonUtils::GetJsonVale<std::string>(obj, "type", "Box2DPhysics");
	}
	
	void ParseWindowConfig(const rapidjson::Value& obj, WindowConfig& config)
	{
		config.Type = JsonUtils::GetJsonVale<std::string>(obj, "type", "GLFWWindow");
		config.Title = JsonUtils::GetJsonVale<std::string>(obj, "title", "A Pirate's Adventure!");
		config.Width = JsonUtils::GetJsonVale<int>(obj, "width", 1280);
		config.Height = JsonUtils::GetJsonVale<int>(obj, "height", 720);
		config.Fullscreen = JsonUtils::GetJsonVale<bool>(obj, "fullscreen", false);
	}

	void ParseAudioConfig(const rapidjson::Value& obj, AudioConfig& config)
	{
		config.Type = JsonUtils::GetJsonVale<std::string>(obj, "type", "IrrKlangAudio");
		config.MasterVolume = JsonUtils::GetJsonVale<float>(obj, "volume", 1.f);
	}

	void ParseInputConfig(const rapidjson::Value& obj, InputConfig& config)
	{
		config.Type = JsonUtils::GetJsonVale<std::string>(obj, "type", "GLFWInput");
	}

	struct ConfigService::Impl
	{
		RendererConfig m_rendererConfig;
		PhysicsConfig m_physicsConfig;
		WindowConfig m_windowConfig;
		AudioConfig m_audioConfig;
		InputConfig m_inputConfig;

		eLoadResult LoadFromFile(const fs::path& path)
		{
			if (!fs::exists(path))
			{
				return eLoadResult::FileNotFound;
			}
			
			try
			{
				auto doc = JsonUtils::LoadJsonDocument(path.string());
			
				auto parseSection = [&doc](const char* name, auto& config, auto parser) 
				{
					if (doc.HasMember(name) && doc[name].IsObject()) 
					{
						parser(doc[name].GetObject(), config);
					}
				};

				parseSection("renderer", m_rendererConfig, ParseRendererConfig);				
				parseSection("physics", m_physicsConfig, ParsePhysicsConfig);
				parseSection("window", m_windowConfig, ParseWindowConfig);
				parseSection("audio", m_audioConfig, ParseAudioConfig);
				parseSection("input", m_inputConfig, ParseInputConfig);

				return eLoadResult::Success;
			}
			catch (...)
			{
				return eLoadResult::ParseError;
			}
		}
	};

	ConfigService::ConfigService()
		: m_impl{ std::make_unique<Impl>() }
	{
	}

	ConfigService::~ConfigService()
	{
	}

	ConfigService::eLoadResult ConfigService::LoadFromFile(const fs::path& configPath)
	{
		return m_impl->LoadFromFile(configPath);
	}

	bool ConfigService::SaveToFile(const fs::path& configPath) const
	{
		return false;
	}

	const WindowConfig& ConfigService::GetWindowConfig() const noexcept
	{
		return m_impl->m_windowConfig;
	}

	const RendererConfig& ConfigService::GetRendererConfig() const noexcept
	{
		return m_impl->m_rendererConfig;
	}

	const AudioConfig& ConfigService::GetAudioConfig() const noexcept
	{
		return m_impl->m_audioConfig;
	}

	const InputConfig& ConfigService::GetInputConfig() const noexcept
	{
		return m_impl->m_inputConfig;
	}

	const PhysicsConfig& ConfigService::GetPhysicsConfig() const noexcept
	{
		return m_impl->m_physicsConfig;
	}
}