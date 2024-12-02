#include "Pch.h"
#include "Serializer.h"

namespace Hi_Engine
{
	void Serializer::Serialize(const char* path, std::unordered_map<const char*, std::any> data)
	{
		rapidjson::Document document;
		document.SetObject();

		auto& allocator = document.GetAllocator();



	}
}