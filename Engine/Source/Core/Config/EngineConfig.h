#pragma once

namespace Hi_Engine
{
	/*struct SystemDesc
	{
		const char* Type;
		const char* Impl;
		std::unorderd_map<std::string, std::any> Data;
	};

	std::vector<SystemDesc> systems;*/

	struct WindowConfig
	{
		const char* Type = "";
		int Width = 1280;
		int Height = 720;
		bool Fullscreen = false;
		bool VSync = true;
		bool IsResizable = true;
		const char* Title = "My Game";
		const char* IconPath = "";
	};

	struct RendererConfig
	{
		const char* Type = "";
	};

	struct AudioConfig
	{
		const char* Type = "";
		float MasterVolume = 1.0f;
	};

	struct InputConfig 
	{
		const char* Type = "";
		float MouseSensitivity = 1.0f;
	};

	class EngineConfig
	{
	public:
		EngineConfig();
		~EngineConfig();

		void LoadFromFile(const char* path);

		[[nodiscard]] const char* GetWindowType() const;
		[[nodiscard]] int GetWindowWidth() const;
		[[nodiscard]] int GetWindowHeight() const;
		[[nodiscard]] bool IsWindowFullscreen() const;

		[[nodiscard]] const char* GetRendererType() const;

		[[nodiscard]] const char* GetAudioType() const;
		[[nodiscard]] float GetMasterVolume() const;

		[[nodiscard]] const char* GetInputType() const;
		[[nodiscard]] float GetMouseSensitivity() const;

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};
}
