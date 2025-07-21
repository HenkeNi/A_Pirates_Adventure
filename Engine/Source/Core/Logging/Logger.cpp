#include "Pch.h"
#include "Logger.h"
#include <windows.h>

#define WHITE_COLOR 7

namespace Hi_Engine
{
	using WORD = unsigned short;

	constexpr WORD COLOR_INFO = 7;		// Light gray (default)
	constexpr WORD COLOR_WARNING = 6;	// Yellow
	constexpr WORD COLOR_ERROR = 4;		// Red

	WORD GetOutputColor(eLogLevel level);

	void SetConsoleTextColor(WORD attributes);

	void Logger::Initialize(const std::string& logFile)
	{
		s_logStream.open(logFile, std::ios::out | std::ios::app);

		if (!s_logStream.is_open()) 
		{
			std::cerr << "Failed to open log file: " << logFile << std::endl;
		}
		else
		{
			s_logStream << "Engine Logs:\n";
		}
	}

	void Logger::Shutdown()
	{
		if (s_logStream.is_open())
		{
			s_logStream.close();
		}
	}

	void Logger::Log(std::string_view message, eLogLevel level)
	{
		std::lock_guard<std::mutex> lock(s_lockMutex);

		std::string logEntry = "[" + GetTimeStamp() + "] [" + GetLevelString(level) + "] " + std::string(message);

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

		// Reset output color
		SetConsoleTextColor(GetOutputColor(eLogLevel::Info));
	}

	std::string Logger::GetLevelString(eLogLevel level)
	{
		switch (level)
		{
			case eLogLevel::Info:	 return "INFO";
			case eLogLevel::Warning: return "WARNING";
			case eLogLevel::Error:	 return "ERROR";
			default:				 return "UNKNOWN";
		}
	}

	std::string Logger::GetTimeStamp()
	{
		std::time_t now = std::time(nullptr);
		char buffer[20];
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
		return buffer;
	}

	void SetConsoleTextColor(WORD attributes)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, attributes);
	}

	WORD GetOutputColor(eLogLevel level)
	{
		switch (level)
		{
		case Hi_Engine::eLogLevel::Info: return COLOR_INFO;
		case Hi_Engine::eLogLevel::Warning: return COLOR_WARNING;
		case Hi_Engine::eLogLevel::Error: return COLOR_ERROR;
		default: return COLOR_INFO;
		}
	}

}
