#include "Pch.h"
#include "PrefabRegistry.h"

namespace Hi_Engine
{
	PropertyValue ParseValue(const rapidjson::Value& value) // TODO; use JsonUtils GetJsonValue??
	{
		if (value.IsObject())
		{
			std::unordered_map<std::string, PropertyValue> values;

			for (const auto& v : value.GetObject())
			{
				values.insert({ v.name.GetString(), ParseValue(v.value)});
			}

			return values;
		}
		else if (value.IsArray())
		{
			std::vector<PropertyValue> values;

			for (const auto& v : value.GetArray())
			{
				values.push_back(ParseValue(v));
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

	void PrefabRegistry::LoadPrefabs(const std::filesystem::path& path)
	{
		auto document = JsonUtils::LoadJsonDocument(path);

		for (const auto& jsonPrefab : document.GetArray())
		{
			Prefab prefab;

			for (const auto& component : jsonPrefab["components"].GetArray())
			{
				Prefab::ComponentData componentData;
				
				// is it safe to use structured binding here?
				for (const auto& [name, value] : component["properties"].GetObject())
				{
					try
					{
						componentData.insert({ name.GetString(), ParseValue(value) });
					}
					catch (...)
					{
						Logger::LogError("[LoadPrefabs] - " + path.string());
						// return?
					}

					//std::cout << ParseValue(value);
				}

				prefab.Data.insert({ component["type"].GetString(), std::move(componentData) });
			}

			m_prefabs.insert({ jsonPrefab["name"].GetString(), prefab });
		}
	}

	const Prefab& PrefabRegistry::GetPrefab(const std::string& name) const
	{
		return m_prefabs.at(name);
		// TODO: insert return statement here
	}

	const Prefab* PrefabRegistry::TryGetPrefab(const std::string& name) const
	{
		if (auto it = m_prefabs.find(name); it != m_prefabs.end())
			return &it->second;

		return nullptr;
	}
}