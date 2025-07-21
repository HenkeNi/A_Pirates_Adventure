#pragma once

namespace Hi_Engine
{
	enum class eLogLevel
	{
		Info,
		Warning,
		Error 
	};

	// [Consider] make 'Logger' into a Service (LoggingService or LogService)

	class Logger
	{
	public:
		static void Initialize(const std::string& logFile);
		
		static void Shutdown();

		inline static void LogInfo(std::string_view message) { Log(message, eLogLevel::Info); }

		inline static void LogWarning(std::string_view message) { Log(message, eLogLevel::Warning); }

		inline static void LogError(std::string_view message) { Log(message, eLogLevel::Error); }

	private:
		static void Log(std::string_view message, eLogLevel level);

		[[nodiscard]] static std::string GetLevelString(eLogLevel level);

		[[nodiscard]] static std::string GetTimeStamp();

		inline static std::ofstream s_logStream;
		inline static std::mutex s_lockMutex;
	};
}