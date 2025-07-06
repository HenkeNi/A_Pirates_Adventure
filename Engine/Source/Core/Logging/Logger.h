#pragma once
#include <mutex> // needed when Logger is included in header files
#include <fstream>

namespace Hi_Engine
{
	enum class eLogLevel
	{
		Info,
		Warning,
		Error 
	};

	void SetConsoleTextColor(int color);

	// rename LoggingService  or LogService?!
	class Logger
	{
	public:
		static void Initialize(const std::string& logFile);
		
		static void Shutdown();

		template <typename T>
		static void LogInfo(T&& message) { Log(std::forward<T>(message), eLogLevel::Info); }
		
		template <typename T>
		static void LogWarning(T&& message) { Log(std::forward<T>(message), eLogLevel::Warning); }

		template <typename T>
		static void LogError(T&& message) { Log(std::forward<T>(message), eLogLevel::Error); }

	private:
		template <typename T>
		static void Log(T&& message, eLogLevel level);

		static std::string GetLevelString(eLogLevel level);

		static std::string GetTimeStamp();

		static int GetOutputColor(eLogLevel level);

		inline static std::ofstream s_logStream;
		inline static std::mutex s_lockMutex;
	};

#pragma region Templated_Methods

	//template <typename T>
	//inline static void Logger::LogInfo(T&& message)
	//{ 
	//	Log(std::forward<T>(message), eLogLevel::Info); 
	//}

	//template <typename T>
	//inline static void LogWarning(T&& message)
	//{ 
	//	Log(std::forward<T>(message), eLogLevel::Warning); 
	//}

	//template <typename T>
	//inline static void LogError(T&& message)
	//{ 
	//	Log(std::forward<T>(message), eLogLevel::Error); 
	//}

	template <typename T>
	inline static void Logger::Log(T&& message, eLogLevel level)
	{
		std::lock_guard<std::mutex> lock(s_lockMutex);

		std::string logEntry = "[" + GetTimeStamp() + "] [" + GetLevelString(level) + "] " + std::forward<T>(message);

		SetConsoleTextColor(GetOutputColor(level));

		std::cout << logEntry << '\n' << std::endl;

		if (s_logStream.is_open())
		{
			s_logStream << logEntry << std::endl;
			s_logStream.flush();
		}
		else
		{
			std::cerr << "Failed to open log file: " << std::endl;
		}

		SetConsoleTextColor(7);
	}

#pragma endregion Templated_Methods
}