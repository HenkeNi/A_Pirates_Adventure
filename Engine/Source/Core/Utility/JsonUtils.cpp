#include "Pch.h"
#include "JsonUtils.h"
#include <stringbuffer.h>
#include <writer.h>

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

		PropertyValue GetPropertyValue(const rapidjson::Value& value)
		{
			if (value.IsObject())
			{
				std::unordered_map<std::string, PropertyValue> values;

				for (const auto& v : value.GetObject())
				{
					values.insert({ v.name.GetString(), GetPropertyValue(v.value) });
				}

				return values;
			}
			else if (value.IsArray())
			{
				std::vector<PropertyValue> values;

				for (const auto& v : value.GetArray())
				{
					values.push_back(GetPropertyValue(v));
				}

				return values;
			}
			else if (value.IsInt())
			{
				return value.GetInt();
			}
			else if (value.IsDouble())
			{
				return static_cast<float>(value.GetFloat());
			}
			else if (value.IsString())
			{
				return std::string(value.GetString());
			}
			else if (value.IsBool())
			{
				return value.GetBool();
			}
			else if (value.IsNull())
			{
				return nullptr;
			}

			throw std::runtime_error("Unsupported JSON type in ParseValue()");
		}

		void SerializeJson(const char* path)
		{
			rapidjson::Document document;
			document.SetObject();

			auto& allocator = document.GetAllocator();

			document.AddMember("name", "MainMenu", allocator);
			document.AddMember("entity_id", 1, allocator);

			// Create a position object
			rapidjson::Value position(rapidjson::kObjectType);
			position.AddMember("x", 100, allocator);
			position.AddMember("y", 200, allocator);

			// Emplace position to the document
			document.AddMember("position", position, allocator);

			// 4. Serialize the document to a string
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			document.Accept(writer);

			// 5. Write the serialized JSON string to a file using std::ofstream
			std::ofstream file(path);  // Open file to write
			if (file.is_open()) {
				file << buffer.GetString();  // Write the JSON string to the file
				file.close();  // Close the file

				std::cout << "JSON data has been written to 'output.json'" << std::endl;
			}
			else {
				std::cerr << "Failed to open file for writing." << std::endl;
			}
		}
	}

	Properties GetProperties(const rapidjson::Value& propertyValue)
	{
		Properties properties;

		for (const auto& [name, value] : propertyValue["properties"].GetObject())
		{
			try
			{
				properties.insert({ name.GetString(), JsonUtils::GetPropertyValue(value) });
				//componentData.insert({ name.GetString(), ParseValue(value) });
			}
			catch (...)
			{
				//Logger::LogError("[LoadPrefabs] - " + path.string());
				// return?
			}
		}

		return properties;
	}
}