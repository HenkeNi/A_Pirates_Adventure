#include "Pch.h"
#include "Logger.h"
#include <windows.h>

#define WHITE_COLOR 7
#define ERROR_COLOR 

namespace Hi_Engine
{
	void SetConsoleTextColor(int color);

	void Logger::Initialize(const std::string& logFile)
	{
		s_logStream.open(logFile, std::ios::out | std::ios::app);

		if (!s_logStream.is_open()) 
		{
			std::cerr << "Failed to open log file: " << logFile << std::endl;
		}
	/*	else
		{
			s_logStream << "Log File";
			s_logStream.flush();
			if (s_logStream.good())
			{
				int xx = 20;
				xx += 20;
			}
		}*/
	}

	void Logger::Shutdown()
	{
		if (s_logStream.is_open())
		{
			s_logStream.close();
		}
	}

	void Logger::Log(const std::string& message, eLogLevel level)
	{
		std::lock_guard<std::mutex> lock(s_lockMutex);

		std::string logEntry = "[" + GetTimeStamp() + "] [" + GetLevelString(level) + "] " + message;

		SetConsoleTextColor(GetOutputColor(level));
		
		std::cout << logEntry << std::endl;

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

	int Logger::GetOutputColor(eLogLevel level)
	{
		switch (level)
		{
		case Hi_Engine::eLogLevel::Info: return 7;
		case Hi_Engine::eLogLevel::Warning: return 6;
		case Hi_Engine::eLogLevel::Error: return 4;
		default: return 7;
		}
	}

	void SetConsoleTextColor(int color)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}
}