#pragma once

//#include <rapidjson.h> // ????
#include <../../../ThirdParty/rapidjson/document.h> //FIX! dont include later...
//#define PI 3.14159265358979323846 

//namespace rapidjson {
//	template <typename Encoding, typename Allocator, typename StackAllocator>
//	class GenericDocument;
//
//	// Common typedef for rapidjson::Document
//	typedef GenericDocument<UTF8<>, MemoryPoolAllocator<>, MemoryPoolAllocator<> > Document;
//}

//namespace rapidjson {
//	class Value;
//}



namespace Hi_Engine
{
	std::wstring ConvertToWideString(const std::string& string);

	/* - RapidJSON - */
	//rapidjson::Document ParseDocument(const std::string& path);

	inline rapidjson::Document ParseDocument(const std::string& path)
	{
		std::ifstream ifs{ path };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		document.Parse(content.c_str());

		assert(!document.HasParseError() && "ERROR: Failed to parse document");
		return document;
	}

	std::any ParseJson(const rapidjson::Value& value);
}