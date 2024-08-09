#include "Pch.h"
#include "EntityBlueprint.h"


Property EntityBlueprint::ParseProperty(const rapidjson::Value& value)
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
	else {
		throw std::runtime_error("Unsupported property type");
	}
}

void EntityBlueprint::Init(const rapidjson::Value& value)
{
	for (auto& component : value["components"].GetArray())
	{
		//const rapidjson::Value& properties = component["properties"];
		//assert(properties.IsObject() && "[EntityFactory - ERROR]: Failed to load component properties for blueprint!");
		std::string componentType = component["type"].GetString();


		ComponentProperties properties;

		for (const auto& [key, value] : component["properties"].GetObject())
		{
			std::string name = key.GetString();
			auto parsed = ParseProperty(value);

			properties.insert({ name, parsed });
		}


		// switch on type? => call on Parser functions...

		// Map parser functions to type (string or type index...)

		// std::unordered_map<std::string, std::any>

		// blueprint.AddProperties({ component["type"].GetString(), ParseComponent(properties) });  // somehow pass in expected structure to ParseComponent? maybe make it templated?? pass in constructor?

		m_componentProperties.insert({ componentType, properties });
		//blueprint.m_componentProperties.insert({ componentType, properties });
	}

}
