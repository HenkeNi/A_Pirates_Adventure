#pragma once
#include <any>

namespace Hi_Engine
{
	bool IsBuildDebug(); // put in BuildConfig or something?

	void SerializeJson(const char* path);
	
	std::wstring ConvertToWideString(const std::string& string);

	/* - RapidJSON - */
	//rapidjson::Document LoadJsonDocument(const std::string& path);

	// rename ParseRapidJsonDocument();?

	std::any ParseJson(const rapidjson::Value& value);

	namespace HelperUtils
	{

	}

	//template <typename T, typename Compare = std::less<T>>
	//void SelectionSort(std::vector<T>& sequence, Compare sortFunc)
	//{
	//	for (std::size_t i = 0; i < sequence.size() - 1; ++i)
	//	{
	//		std::size_t bestIndex = i;
	//		for (std::size_t j = i + 1; j < sequence.size(); ++j)
	//		{
	//			if (sortFunc(sequence[j], sequence[bestIndex]))
	//				bestIndex = j;
	//		}

	//		if (bestIndex != i)
	//			std::swap(sequence[bestIndex], sequence[i]);
	//	}

	//}


	// NOTE; passing by value here avoids unnecessary copying
	std::string ToLowerCase(std::string text);
}