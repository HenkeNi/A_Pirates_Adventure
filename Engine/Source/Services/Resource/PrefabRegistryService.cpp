#include "Pch.h"
#include "PrefabRegistryService.h"

namespace Hi_Engine
{
	//PropertyValue ParseValue(const rapidjson::Value& value) // TODO; use JsonUtils GetJsonValue??
	//{
	//	if (value.IsObject())
	//	{
	//		std::unordered_map<std::string, PropertyValue> values;

	//		for (const auto& v : value.GetObject())
	//		{
	//			values.insert({ v.name.GetString(), ParseValue(v.value)});
	//		}

	//		return values;
	//	}
	//	else if (value.IsArray())
	//	{
	//		std::vector<PropertyValue> values;

	//		for (const auto& v : value.GetArray())
	//		{
	//			values.push_back(ParseValue(v));
	//		}

	//		return values;
	//	}
	//	else if (value.IsInt())
	//	{
	//		return value.GetInt();
	//	}
	//	else if (value.IsDouble())
	//	{
	//		return static_cast<float>(value.GetFloat());
	//	}
	//	else if (value.IsString())
	//	{
	//		return std::string(value.GetString());
	//	}
	//	else if (value.IsBool())
	//	{
	//		return value.GetBool();
	//	}
	//	else if (value.IsNull()) 
	//	{
	//		return nullptr;
	//	}
	//
	//	throw std::runtime_error("Unsupported JSON type in ParseValue()");
	//}

	void PrefabRegistryService::LoadPrefabs(const std::filesystem::path& path)
	{
		// try catch...
		auto document = JsonUtils::LoadJsonDocument(path);

		for (const auto& jsonPrefab : document.GetArray())
		{
			Prefab prefab;

			// TODO; create function (global) for getting all properteis...
			for (const auto& component : jsonPrefab["components"].GetArray())
			{
				//Prefab::ComponentData componentData;
				
				auto properties = GetProperties(component);

				//Properties componentProperties;
				//std::unordered_map<std::string, Properties> componentProperties;

				// is it safe to use structured binding here?
				//for (const auto& [name, value] : component["properties"].GetObject())
				//{
				//	try
				//	{
				//		componentProperties.insert({ name.GetString(), JsonUtils::GetPropertyValue(value) });
				//		//componentData.insert({ name.GetString(), ParseValue(value) });
				//	}
				//	catch (...)
				//	{
				//		Logger::LogError("[LoadPrefabs] - " + path.string());
				//		// return?
				//	}

				//	//std::cout << ParseValue(value);
				//}

				prefab.ComponentProperties.insert({ component["type"].GetString(), std::move(properties) });
				//prefab.Data.insert({ component["type"].GetString(), std::move(componentData) });
			}

			//m_prefabs.insert({ jsonPrefab["name"].GetString(), prefab });

			const std::string name = jsonPrefab["name"].GetString();
			m_prefabs.insert({ name, prefab });

			Logger::LogInfo("[Success] - created prefab: '" + name + '\'');
		}
	}

	const Prefab& PrefabRegistryService::GetPrefab(const std::string& name) const
	{
		return m_prefabs.at(name);
		// TODO: insert return statement here
	}

	const Prefab* PrefabRegistryService::TryGetPrefab(const std::string& name) const
	{
		if (auto it = m_prefabs.find(name); it != m_prefabs.end())
			return &it->second;

		return nullptr;
	}
}