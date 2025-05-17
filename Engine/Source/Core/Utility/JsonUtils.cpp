#include "Pch.h"
#include "JsonUtils.h"


namespace Hi_Engine
{
	namespace JsonUtils
	{
		rapidjson::Document LoadJsonDocument(const fs::path& path)
		{
			if (!fs::exists(path))
			{
				throw std::runtime_error("Path doesn't exist: " + path.string());
			}

			std::ifstream ifs{ path };
			if (!ifs.is_open())
			{
				throw std::runtime_error("Failed to open file: " + path.string());
			}

			std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

			rapidjson::Document document;
			document.Parse(content.data(), content.size());

			if (document.HasParseError())
				throw std::runtime_error("JSON parse error in file: " + path.string());

			return document;
		}
	}
}