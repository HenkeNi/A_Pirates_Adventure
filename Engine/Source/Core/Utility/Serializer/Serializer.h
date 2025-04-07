#pragma once

// WindowData WindowParser(rapidjson::Document& aDocument);

namespace Hi_Engine
{
	/*class Serializer
	{
	public:
	};

	class JsonSerializer : public Serializer
	{
	public:

	};*/

	// class ECSSerializer ?? -> make module?

	using JsonValue = std::variant<int, float, std::string, bool, FVector2>;
	using JsonKey = const char*;

	class JsonObject
	{
	public:
		void AddKeyValue(JsonKey key, JsonValue value);
		void AddKeyValue(const std::pair<JsonKey, JsonValue>& value);

	private:
		std::unordered_map<JsonKey, JsonValue> m_values;
	};

	class Serializer
	{
	public:
		void Serialize(const char* path, std::unordered_map<const char*, std::any> data);
	};
}