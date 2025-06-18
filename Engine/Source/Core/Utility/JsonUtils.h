#pragma once
#include "Dependencies/rapidjson/document.h"

// TEMP?
namespace Hi_Engine
{
	// Define elsewhere? PropertyValue.h?
	struct PropertyValue : std::variant<
		std::nullptr_t,
		bool,
		int,
		float,
		std::string,
		std::unordered_map<std::string, PropertyValue>,
		std::vector<PropertyValue>>
	{
		using variant::variant; // inherit constructors
	};

	using Properties = std::unordered_map<std::string, PropertyValue>;

	// put somewhere else??
	template <typename T>
	T GetPropertyValueOrDefault(const std::unordered_map<std::string, PropertyValue>& properties, const std::string& key, const T& defaultValue) // use auto instead of compdata??
	{
		if (auto it = properties.find(key); it != properties.end())
		{
			if (auto* val = std::get_if<T>(&it->second))
			{
				return *val;
			}
		}

		return defaultValue;
	}

	Properties GetProperties(const rapidjson::Value& propertyValue);
}

namespace Hi_Engine::JsonUtils
{
	namespace fs = std::filesystem;

	template <typename T>
	struct TypeHelper;

	template <>
	struct TypeHelper<int>
	{
		static bool Is(const rapidjson::Value& val) { return val.IsInt(); }
		static int Get(const rapidjson::Value& val) { return val.GetInt(); }
	};

	template <>
	struct TypeHelper<bool>
	{
		static bool Is(const rapidjson::Value& val) { return val.IsBool(); }
		static bool Get(const rapidjson::Value& val) { return val.GetBool(); }
	};

	template <>
	struct TypeHelper<float>
	{
		static bool Is(const rapidjson::Value& val) { return val.IsFloat(); }
		static float Get(const rapidjson::Value& val) { return val.GetFloat(); }
	};

	template <>
	struct TypeHelper<double>
	{
		static bool Is(const rapidjson::Value& val) { return val.IsDouble(); }
		static double Get(const rapidjson::Value& val) { return val.GetDouble(); }
	};

	template <>
	struct TypeHelper<std::string>
	{
		static bool Is(const rapidjson::Value& val) { return val.IsString(); }
		static std::string Get(const rapidjson::Value& val) { return val.GetString(); }
	};

	rapidjson::Document LoadJsonDocument(const fs::path& path);

	template <typename T>
	T GetJsonValue(const rapidjson::Value& obj, const char* name)
	{
		if (!obj.HasMember(name))
			throw std::runtime_error(std::string("Missing JSON member: ") + name);

		const auto& val = obj[name];

		if (!TypeHelper<T>::Is(val))
			throw std::runtime_error(std::string("Incorrect type for member: ") + name);

		return TypeHelper<T>::Get(val);
	}

	template <typename T>
	T GetJsonVale(const rapidjson::Value& obj, const char* name, const T& defaultValue)
	{
		if (obj.HasMember(name))
		{
			const auto& val = obj[name];

			if (TypeHelper<T>::Is(val))
			{
				return TypeHelper<T>::Get(val);
			}
		}

		return defaultValue;
	}

	// Consider; Put in separate file (PropertyUtils?)
	PropertyValue GetPropertyValue(const rapidjson::Value& value); // From JSon function instead? store in comp entry?
	
	// FIX?!
	void SerializeJson(const char* path);
}