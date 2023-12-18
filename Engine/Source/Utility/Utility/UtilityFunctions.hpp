#pragma once
#include <cassert>
#include <random>
#include <string>

#define PI 3.14159265358979323846 

namespace CommonUtilities
{
	template <typename T>
	T Min(T aValue1, T aValue2)
	{
		return aValue1 < aValue2 ? aValue1 : aValue2;
	}

	template <typename T>
	T Max(T aValue1, T aValue2)
	{
		return aValue1 > aValue2 ? aValue1 : aValue2;
	}

	template <typename T>
	T Abs(T anArg)
	{
		return anArg < 0 ? -anArg : anArg;
	}

	template <typename T>
	T Clamp(T aValue, T aMin, T aMax)
	{
		assert(aMax >= aMin);
		return std::max(aMin, std::min(aMax, aValue));
	}

	template <typename T>
	T Lerp(T a, T b, float c)
	{
		T result = (a + c * (b - a));
		return result;
	}

	template <typename T>
	void Swap(T& aValue1, T& aValue2)
	{
		T temp = aValue1;
		aValue1 = aValue2;
		aValue2 = temp;
	}




	template <typename T>
	T ConvertRadiansToDegrees(T someRadians)
	{
		return (someRadians * (180 / PI));
	}

	template <typename T>
	T ConvertDegreesToRadians(T someDegrees)
	{
		return (someDegrees * (PI / 180));
	}

	template <typename T> // TODO: FIX!!! Make Random.hpp??
	T GetRandomNumber(T aMin, T aMax)
	{
		static std::random_device seed;
		static std::mt19937 randomEngine(seed());

		std::uniform_int_distribution<T> randomDist(aMin, aMax);
		return randomDist(randomEngine);
	}

	inline std::wstring ConvertToWideString(const std::string& aStr) // ??? somewhere else?
	{
		std::wstring wString{ aStr.begin(), aStr.end() };
		return wString;
	}


	/* - RapidJSON - */
	inline rapidjson::Document ParseDocument(const std::string& aPath)
	{
		std::ifstream ifs{ aPath };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		document.Parse(content.c_str());

		assert(!document.HasParseError() && "ERROR: Failed to parse document");
		return document;
	}

	inline std::any ParseJson(const rapidjson::Value& aValue)
	{
		if (aValue.IsArray())
		{
			std::vector<std::any> values;
			for (const auto& value : aValue.GetArray())
			{
				values.push_back(ParseJson(value));
			}

			return values;
		}

		if (aValue.IsObject())
		{
			std::unordered_map<std::string, std::any> values;
			for (const auto& value : aValue.GetObject())
			{
				values.insert_or_assign(value.name.GetString(), ParseJson(value.value));
			}
			return values;
		}

		if (aValue.IsFloat())
			return aValue.GetFloat();

		if (aValue.IsInt())
			return aValue.GetInt();

		if (aValue.IsString())
			return std::string(aValue.GetString());

		if (aValue.IsBool())
			return aValue.GetBool();

		if (aValue.IsDouble())
			return aValue.GetDouble();

		return nullptr;
	}
}