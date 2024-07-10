#include "Pch.h"
#include "UtilityFunctions.h"


namespace Hi_Engine
{
	std::wstring ConvertToWideString(const std::string& string)
	{
		std::wstring wString{ string.begin(), string.end() };
		return wString;
	}

	
	/*rapidjson::Document ParseDocument(const std::string& path)
	{
		std::ifstream ifs{ path };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		document.Parse(content.c_str());

		assert(!document.HasParseError() && "ERROR: Failed to parse document");
		return document;
	}*/

	std::any ParseJson(const rapidjson::Value& value)
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

	bool IsBuildDebug()
	{
#ifdef DEBUG

		return true;

#endif // DEBUG

#ifdef NDEBUG

		return false;

#endif // NDEBUG

		return false;
	}

}