#include "Pch.h"
#include "JsonParser.h"


namespace JsonParser
{
	void ParseBehaviorTreeComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParseSteeringBehaviorComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParseWeaponComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParseHitboxComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
		auto halfSize = aValue["half_size"].GetFloat();

		someComponentData.insert(std::make_pair("halfSize", halfSize));
	}

	void ParseAttackComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParsePickupComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParsePlayerControllerComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParseTransformComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
		auto position = aValue["position"].GetArray();
		auto scale		= aValue["scale"].GetArray();
		auto rotation = aValue["rotation"].GetFloat();

		someComponentData.insert(std::make_pair("position", std::array<float, 3>{ position[0].GetFloat(), position[1].GetFloat(), position[2].GetFloat()	}));
		someComponentData.insert(std::make_pair("scale", std::array<float, 3>{ scale[0].GetFloat(), scale[1].GetFloat(), scale[2].GetFloat()		}));
		someComponentData.insert(std::make_pair("rotation", rotation));
	}

	void ParseInputComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParseInventoryComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParseVelocityComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParseSpriteComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
		std::string shader		= aValue["shader"].GetString();
		std::string texture		= aValue["texture"].GetString();
		auto color				= aValue["color"].GetArray();

		someComponentData.insert(std::make_pair("shader", shader));
		someComponentData.insert(std::make_pair("texture", texture));
		someComponentData.insert(std::make_pair("color", std::array<float, 4>{ color[0].GetFloat(), color[1].GetFloat(), color[2].GetFloat(), color[3].GetFloat() }));
	}

	void ParseAnimationComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParseCameraComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}
	
	void ParseRectComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
		std::string shader = aValue["shader"].GetString();

		someComponentData.insert(std::make_pair("shader", shader));
	}

	void ParseResourceComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
		auto quantity = aValue["quantity"].GetInt();

		someComponentData.insert(std::make_pair("quantity", quantity));
	}

	void ParseHealthComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
		auto value = aValue["value"].GetInt();

		someComponentData.insert(std::make_pair("value", value));
	}

	void ParseStaminaComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}

	void ParseTimerComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData)
	{
	}
}