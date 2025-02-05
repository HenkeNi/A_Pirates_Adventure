#pragma once

#include "Dependencies/rapidjson/document.h"
#include <any>

namespace Hi_Engine
{
	std::wstring ConvertToWideString(const std::string& string);

	/* - RapidJSON - */
	//rapidjson::Document ParseDocument(const std::string& path);

	inline rapidjson::Document ParseDocument(const std::string& path)
	{
		std::ifstream ifs{ path };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		document.Parse(content.c_str());

		assert(!document.HasParseError() && "ERROR: Failed to parse document");
		return document;
	}

	std::any ParseJson(const rapidjson::Value& value);

	bool IsBuildDebug(); // put in BuildConfig or something?

	void SerializeJson(const char* path);

	template <typename T, typename Compare = std::less<T>>
	void SelectionSort(std::vector<T>& sequence, Compare sortFunc)
	{
		for (std::size_t i = 0; i < sequence.size() - 1; ++i)
		{
			std::size_t bestIndex = i;
			for (std::size_t j = i + 1; j < sequence.size(); ++j)
			{
				if (sortFunc(sequence[j], sequence[bestIndex]))
					bestIndex = j;
			}

			if (bestIndex != i)
				std::swap(sequence[bestIndex], sequence[i]);
		}

	}


	// NOTE; passing by value here avoids unnecessary copying
	std::string ToLowerCase(std::string text);
}