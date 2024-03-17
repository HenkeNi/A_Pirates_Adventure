#pragma once
#include "../Data/Structs.h"

// REDO... Find better way...??
namespace Hi_Engine::FileSystem
{
	template <typename Parser, typename Data>
	Data ParseJson(const std::string& path)
	{
		std::ifstream ifs{ path };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		assert(!document.Parse(content.c_str()).HasParseError() && "Failed to Parse");

		Parser parser;
		return parser.Parse(document); 
	}

	// Todo: write to json?

	// Otherways to read/write to files?
}

