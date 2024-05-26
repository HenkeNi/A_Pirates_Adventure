#pragma once
#include <cassert>
#include <random>
#include <string>
#include <any>

//#define PI 3.14159265358979323846 

namespace Hi_Engine
{
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