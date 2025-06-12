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
}