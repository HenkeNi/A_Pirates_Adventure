#pragma once
#include <any>

namespace Hi_Engine::Utils
{
	inline constexpr bool IsDebugBuild() // put in BuildConfig or something?
	{
#ifndef NDEBUG
		return true;
#else
		return false;
#endif
	}
	
	std::wstring ConvertToWideString(const std::string& string);

	// NOTE; passing by value here avoids unnecessary copying
	std::string ToLowerCase(std::string text);
}