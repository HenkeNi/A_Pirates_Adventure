#include "Pch.h"
#include "Utils.h"

namespace Hi_Engine::Utils
{
	std::wstring ConvertToWideString(const std::string& string)
	{
		std::wstring wString{ string.begin(), string.end() };
		return wString;
	}

	std::string ToLowerCase(std::string text)
	{
		for (auto t : text)
			t = std::tolower(t);

		return text;
	}
}