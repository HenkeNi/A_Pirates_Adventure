#include "Pch.h"
#include "UtilityFunctions.h"
#include <stringbuffer.h>
#include <writer.h>
// 


namespace Hi_Engine
{
	





	std::wstring ConvertToWideString(const std::string& string)
	{
		std::wstring wString{ string.begin(), string.end() };
		return wString;
	}

	
	/*rapidjson::Document LoadJsonDocument(const std::string& path)
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

	std::string ToLowerCase(std::string text)
	{
		for (auto t : text)
			t = std::tolower(t);

		return text;
	}
}