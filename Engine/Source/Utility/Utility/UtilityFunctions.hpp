#pragma once
#include <cassert>
#include <random>
#include <string>
#include <any>

#define PI 3.14159265358979323846 

namespace CommonUtilities
{
	template <typename T>
	T Min(T value1, T value2)
	{
		return value1 < value2 ? value1 : value2;
	}

	template <typename T>
	T Max(T value1, T value2)
	{
		return value1 > value2 ? value1 : value2;
	}

	template <typename T>
	T Abs(T value)
	{
		return value < 0 ? -value : value;
	}

	template <typename T>
	T Clamp(T value, T min, T max)
	{
		assert(max >= min);
		return std::max(min, std::min(max, value));
	}

	template <typename T>
	T Lerp(T a, T b, float c)
	{
		T result = (a + c * (b - a));
		return result;
	}

	template <typename T>
	void Swap(T& value1, T& value2)
	{
		T temp = value1;
		value1 = value2;
		value2 = temp;
	}




	template <typename T>
	T ConvertRadiansToDegrees(T radians)
	{
		return (radians * (180 / PI));
	}

	template <typename T>
	T ConvertDegreesToRadians(T degrees)
	{
		return (degrees * (PI / 180));
	}

	template <typename T> // TODO: FIX!!! Make Random.hpp??
	T GetRandomNumber(T min, T max)
	{
		static std::random_device seed;
		static std::mt19937 randomEngine(seed());

		std::uniform_int_distribution<T> randomDist(min, max);
		return randomDist(randomEngine);
	}

	inline float GetRandomFloat(float min, float max)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd()); // Mersenne Twister 19937 generator

		std::uniform_real_distribution<float> dis(min, max); // Range: [0.0, 1.0)

		return dis(gen);
	}

	inline std::wstring ConvertToWideString(const std::string& string) // ??? somewhere else?
	{
		std::wstring wString{ string.begin(), string.end() };
		return wString;
	}


	/* - RapidJSON - */
	inline rapidjson::Document ParseDocument(const std::string& path)
	{
		std::ifstream ifs{ path };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		document.Parse(content.c_str());

		assert(!document.HasParseError() && "ERROR: Failed to parse document");
		return document;
	}

	inline std::any ParseJson(const rapidjson::Value& value)
	{
		if (value.IsArray())
		{
			std::vector<std::any> values;
			for (const auto& value : value.GetArray())
			{
				values.push_back(ParseJson(value));
			}

			return values;
		}

		if (value.IsObject())
		{
			std::unordered_map<std::string, std::any> values;
			for (const auto& [name, value] : value.GetObject())
			{
		

				values.insert_or_assign(name.GetString(), ParseJson(value));
			}
			return values;
		}

		if (value.IsFloat())
			return value.GetFloat();

		if (value.IsInt())
			return value.GetInt();

		if (value.IsString())
			return std::string(value.GetString());

		if (value.IsBool())
			return value.GetBool();

		if (value.IsDouble())
			return value.GetDouble();

		return nullptr;
	}
}