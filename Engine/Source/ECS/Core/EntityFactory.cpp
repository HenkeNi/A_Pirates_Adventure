#include "Pch.h"
#include "EntityFactory.h"
#include "EntityManager.h"

namespace Hi_Engine
{
	void EntityPrefab::Init(const rapidjson::Value& value)
	{
		for (auto& component : value["components"].GetArray())
		{
			std::string componentType = component["type"].GetString();
			ComponentProperties properties;

			for (const auto& [key, value] : component["properties"].GetObject())
			{
				std::string name = key.GetString();
				auto parsed = ParseProperty(value);

				properties.insert({ name, parsed });
			}

			m_componentProperties.insert({ componentType, properties });
		}
	}

	Property EntityPrefab::ParseProperty(const rapidjson::Value& value)
	{
		if (value.IsDouble())
		{
			return value.GetDouble();
		}
		else if (value.IsInt())
		{
			return value.GetInt();
		}
		else if (value.IsBool())
		{
			return value.GetBool();
		}
		else if (value.IsString())
		{
			return std::string(value.GetString());
		}
		else if (value.IsFloat())
		{
			return value.GetFloat();
		}
		else if (value.IsArray())
		{
			int size = value.Size();

			if (size == 2)
			{
				if (value[0].IsDouble())
				{
					FVector2 property;
					property.x = value[0].GetFloat();
					property.y = value[1].GetFloat();

					return property;
				}
				else if (value[0].IsInt())
				{
					IVector2 property;
					property.x = value[0].GetInt();
					property.y = value[1].GetInt();

					return property;
				}
			}
			else if (size == 3)
			{
				if (value[0].IsDouble())
				{
					FVector3 property;
					property.x = value[0].GetFloat();
					property.y = value[1].GetFloat();
					property.z = value[2].GetFloat();

					return property;
				}
				else if (value[0].IsInt())
				{
					IVector3 property;
					property.x = value[0].GetInt();
					property.y = value[1].GetInt();
					property.z = value[2].GetInt();

					return property;
				}
			}
			else if (size == 4)
			{
				if (value[0].IsDouble())
				{
					FVector4 property;
					property.x = value[0].GetFloat();
					property.y = value[1].GetFloat();
					property.z = value[2].GetFloat();
					property.w = value[3].GetFloat();

					return property;
				}
				else if (value[0].IsInt())
				{
					IVector4 property;
					property.x = value[0].GetInt();
					property.y = value[1].GetInt();
					property.z = value[2].GetInt();
					property.w = value[3].GetInt();

					return property;

				}
			}
			//std::vector<Property> properties;
		}
		else if (value.IsObject())
		{

		}
		else
		{
			throw std::runtime_error("Unsupported property type");
		}
	}







	EntityFactory::EntityFactory(EntityManager& entityManager, ComponentRegistry& componentRegistry)
		: m_entityManager{ entityManager }, m_componentRegistry{ componentRegistry }
	{
	}

	EntityFactory::~EntityFactory()
	{
	}

	void EntityFactory::LoadPrefabs()
	{
		const char* path = "../Game/Assets/Json/Blueprints/blueprint_manifest.json";

		auto document = Hi_Engine::ParseDocument(path);

		for (auto& path : document["blueprints"].GetArray())
		{
			std::string blueprintPath = path.GetString();

			auto document = Hi_Engine::ParseDocument(blueprintPath);

			if (document.IsArray())
			{
				for (const auto& blueprint : document.GetArray())
				{
					ConstructPrefab(blueprint);
				}
			}
			else if (document.IsObject())
			{
				ConstructPrefab(document);
			}
		}
	}

	void EntityFactory::ConstructPrefab(const rapidjson::Value& value)
	{
		EntityPrefab prefab;
		prefab.Init(value);

		std::string id = value["id"].GetString();
		m_prefabs.insert_or_assign(id, std::move(prefab));
	}

	std::optional<Entity> EntityFactory::Create(const char* name)
	{
		std::optional<Entity> entity = m_entityManager.Create();

		if (!entity.has_value())
			return std::nullopt;

		auto prefab = m_prefabs.find(name);

		assert(prefab != m_prefabs.end() && "Prefab not found");

		const auto& componentProperties = prefab->second.GetComponentProperties();
		for (const auto& [component, properties] : componentProperties)
		{
			auto itr = m_componentRegistry.find(component);

			if (itr == m_componentRegistry.end())
				continue;

			itr->second.AddComponent(entity.value());

			if (!properties.empty()) // Todo, also put checks in ComponentInitailizer!
			{
				itr->second.InitializeComponent(entity.value(), properties);
			}
		}

		return entity;
	}

	std::optional<Entity> EntityFactory::CreateFromJson(const rapidjson::Value& value)
	{
		const char* id = value["entity_id"].GetString();
		std::optional<Entity> entity = Create(id); // dont call this? or refactor function?? or fine since json only overrides some values?

		if (!entity.has_value())
			return std::nullopt;

		if (value.HasMember("components_data"))
		{
			for (const auto& component : value["components_data"].GetArray())
			{
				ComponentProperties componentProperties;

				for (const auto& [key, value] : component["properties"].GetObj())
				{
					Property property = EntityPrefab::ParseProperty(value);
					componentProperties.insert({ key.GetString(), property });
				}

				const auto& componentType = component["type"].GetString();
				auto itr = m_componentRegistry.find(componentType);

				if (itr != m_componentRegistry.end())
				{
					itr->second.InitializeComponent(entity.value(), componentProperties);
				}
				else
				{
					std::cerr << "[EntityFactory::CreateFromJson] - couldn't find component type " << componentType << "\n";
				}

			}
		}

		return entity;
	}
}