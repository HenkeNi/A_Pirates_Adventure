#pragma once
#include "../IService.h"
#include <filesystem>

namespace Hi_Engine
{
	namespace fs = std::filesystem;

	struct WindowConfig
	{
		std::string Type = "GLFWWindow";
		int Width = 1280;
		int Height = 720;
		bool Fullscreen = false;
		bool VSync = true;
		bool IsResizable = true;
		std::string Title = "My Game";
		std::string IconPath = "";
	};

	struct RendererConfig
	{
		std::string Type = "";
	};

	struct AudioConfig
	{
		std::string Type = "";
		float MasterVolume = 1.0f;
	};

	struct InputConfig 
	{
		std::string Type = "";
		float MouseSensitivity = 1.0f;
	};

	struct PhysicsConfig
	{
		std::string Type = "";
	};

	class ConfigService : public IService
	{
	public:
		enum class eLoadResult
		{
			Success,
			FileNotFound,
			ParseError,
			ValidationError
		};

		ConfigService();
		~ConfigService();

		// Rule of 5 ?

		eLoadResult LoadFromFile(const fs::path& configPath);

		bool SaveToFile(const fs::path& configPath) const;

		[[nodiscard]] const WindowConfig& GetWindowConfig() const noexcept;
		[[nodiscard]] const RendererConfig& GetRendererConfig() const noexcept;
		[[nodiscard]] const AudioConfig& GetAudioConfig() const noexcept;
		[[nodiscard]] const InputConfig& GetInputConfig() const noexcept;
		[[nodiscard]] const PhysicsConfig& GetPhysicsConfig() const noexcept;

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};
}
