#pragma once

namespace Hi_Engine
{
	enum class eLogLevel
	{
		Info,
		Warning,
		Error 
	};

	class Logger
	{
	public:
		static void Initialize(const std::string& logFile);
		
		static void Shutdown();

		inline static void LogInfo(const std::string& message) { Log(message, eLogLevel::Info); }

		inline static void LogWarning(const std::string& message) { Log(message, eLogLevel::Warning); }
 			 
		inline static void LogError(const std::string& message) { Log(message, eLogLevel::Error); }

	private:
		static void Log(const std::string& message, eLogLevel level);

		static std::string GetLevelString(eLogLevel level);

		static std::string GetTimeStamp();

		static int GetOutputColor(eLogLevel level);

		inline static std::ofstream s_logStream;
		inline static std::mutex s_lockMutex;
	};
}