#include "Pch.h"
#include "ComponentParser.h"
#include "../Data/Structs.h"

using ComponentData = std::unordered_map<std::string, std::any>;
using JsonValue = const rapidjson::Value&;

std::unordered_map<std::string, std::function<ComponentData(JsonValue)>> ComponentParser::m_parsers;
bool ComponentParser::m_isInitialized = false;

ComponentData ComponentParser::ParseComponentFromJson(const std::string& aType, JsonValue aValue)
{ 
	if (!m_isInitialized)
	{
		Initialize();
		m_isInitialized = true;
	}

	return m_parsers.at(aType)(aValue);
}



ComponentData ComponentParser::ParseAnimationComponent(JsonValue aValue)
{
	ComponentData data;

	std::unordered_map<std::string, Animation> animationMap;

	for (const auto& animation : aValue["animations"].GetArray())
	{
		Animation animationSequence;

		std::vector<std::string> sprites;
		for (const auto& sprite : animation["sprites"].GetArray())
			sprites.push_back(sprite.GetString());

		animationSequence.m_sprites				= sprites;
		animationSequence.m_totalFrames			= sprites.size();
		animationSequence.m_currentFrame		= 0;
		animationSequence.m_elapsedFrameTime	= 0.f;
		animationSequence.m_frameDuration		= animation["frame_duration"].GetFloat();
		animationSequence.m_isLooping			=	animation["is_looping"].GetBool();
		animationSequence.m_isPlaying			= animation["is_playing"].GetBool();

		std::string identifier	= animation["identifier"].GetString();
		animationMap.insert_or_assign(identifier, animationSequence);
	}

	std::string active = aValue["active"].GetString();

	data.insert(std::make_pair("animationMap", animationMap));
	data.insert(std::make_pair("active", active));
	/*data.insert(std::make_pair("identifier",	identifier));
	data.insert(std::make_pair("animations",	animations));
	data.insert(std::make_pair("frames",		frames));
	data.insert(std::make_pair("startFrame",	startFrame));
	data.insert(std::make_pair("frameDuration", frameDuration));
	data.insert(std::make_pair("isLooping",		isLooping));
	data.insert(std::make_pair("isPlaying",		isPlaying));*/

	return data;
}

ComponentData ComponentParser::ParseAttackComponent(JsonValue aValue)
{
	return ComponentData();
}

ComponentData ComponentParser::ParseBehaviorTreeComponent(JsonValue aValue)
{
	return ComponentData();
}

ComponentData ComponentParser::ParseCameraComponent(JsonValue aValue)
{
	return ComponentData();
}

ComponentData ComponentParser::ParseCharacterStateComponent(JsonValue aValue)
{
	return ComponentData();
}

ComponentData ComponentParser::ParseDebugRectComponent(JsonValue aValue)
{
	ComponentData data;
	std::string shader = aValue["shader"].GetString();

	data.insert(std::make_pair("shader", shader));

	return data;
}

ComponentData ComponentParser::ParseHarvestableComponent(JsonValue aValue)
{
	ComponentData data;

	int yield = aValue["yield"].GetInt();
	std::string resource = aValue["resource_type"].GetString();

	data.insert(std::make_pair("resource_type", resource));
	data.insert(std::make_pair("yield", yield));

	return data;
}

ComponentData ComponentParser::ParseHealthComponent(JsonValue aValue)
{
	ComponentData data;
	auto value = aValue["value"].GetInt();

	data.insert(std::make_pair("value", value));

	return data;
}

ComponentData ComponentParser::ParseHitboxComponent(JsonValue aValue)
{
	ComponentData data;
	auto halfSize = aValue["half_size"].GetFloat();
	bool isStatic = aValue["is_static"].GetBool();

	data.insert(std::make_pair("halfSize", halfSize));
	data.insert(std::make_pair("isStatic", isStatic));

	return data;
}

ComponentData ComponentParser::ParseInputComponent(JsonValue aValue)
{
	return ComponentData();
}

ComponentData ComponentParser::ParseInventoryComponent(JsonValue aValue)
{
	return ComponentData();
}

ComponentData ComponentParser::ParseMapChunkComponent(JsonValue aValue)
{
	ComponentData data;

	int width = aValue["width"].GetInt();
	int height = aValue["height"].GetInt();

	data.insert(std::make_pair("width", width));
	data.insert(std::make_pair("height", height));

	return data;
}

ComponentData ComponentParser::ParsePickupComponent(JsonValue aValue)
{
	return ComponentData();
}

ComponentData ComponentParser::ParsePlayerControllerComponent(JsonValue aValue)
{
	ComponentData data;
	
	//std::unordered_map<Hi_Engine::eInputType, Hi_Engine::Command*> commands;
	//std::unordered_map<Hi_Engine::eInputType, Hi_Engine::Command*> commands;

	//for (const auto& command : aValue["commands"].GetArray())
	//{
	//	std::string type = command["input"].GetString();
	//	if (type == "MoveCommand")
	//	{
	//		// TODO; how to map key?
	//		commands.insert(std::make_pair<> ) // Todo; use builder?

	//	}

	//}

	//data.insert(std::make_pair("commands", commands));
	
	return data;
}

ComponentData ComponentParser::ParseRectComponent(JsonValue aValue)
{
	ComponentData data;
	std::string shader = aValue["shader"].GetString();

	data.insert(std::make_pair("shader", shader));

	return data;
}

ComponentData ComponentParser::ParseResourceComponent(JsonValue aValue)
{
	ComponentData data;
	std::string resource = aValue["resource"].GetString();

	data.insert(std::make_pair("resource", resource));

	return data;


}

ComponentData ComponentParser::ParseSpawnComponent(JsonValue aValue)
{
	ComponentData data;

	std::string spawned = aValue["spawned"].GetString();
	int amount			= aValue["amount"].GetInt();
	float interval		= aValue["interval"].GetFloat();

	data.insert(std::make_pair("spawned",	spawned));
	data.insert(std::make_pair("amount",	amount));
	data.insert(std::make_pair("interval",	interval));
	
	return data;
}

ComponentData ComponentParser::ParseSpriteComponent(JsonValue aValue)
{
	ComponentData data;
	std::string shader = aValue["shader"].GetString();
	std::string texture = aValue["texture"].GetString();
	auto color = aValue["color"].GetArray();

	data.insert(std::make_pair("shader", shader));
	data.insert(std::make_pair("texture", texture));
	data.insert(std::make_pair("color", std::array<float, 4>{ color[0].GetFloat(), color[1].GetFloat(), color[2].GetFloat(), color[3].GetFloat() }));

	return data;
}

ComponentData ComponentParser::ParseStaminaComponent(JsonValue aValue)
{
	return ComponentData();
}

ComponentData ComponentParser::ParseSteeringBehaviorComponent(JsonValue aValue)
{
	return ComponentData();
}

ComponentData ComponentParser::ParseTimerComponent(JsonValue aValue)
{
	return ComponentData();
}

ComponentData ComponentParser::ParseTransformComponent(JsonValue aValue)
{
	ComponentData data;
	auto position = aValue["position"].GetArray();
	auto scale = aValue["scale"].GetArray();
	auto rotation = aValue["rotation"].GetFloat();

	data.insert(std::make_pair("position", std::array<float, 3>{ position[0].GetFloat(), position[1].GetFloat(), position[2].GetFloat()	}));
	data.insert(std::make_pair("scale", std::array<float, 3>{ scale[0].GetFloat(), scale[1].GetFloat(), scale[2].GetFloat()		}));
	data.insert(std::make_pair("rotation", rotation));

	return data;
}

ComponentData ComponentParser::ParseTriggerComponent(JsonValue aValue)
{
	ComponentData data;
	auto halfSize = aValue["half_size"].GetFloat();

	data.insert(std::make_pair("halfSize", halfSize));
	return data;
}

ComponentData ComponentParser::ParseVelocityComponent(JsonValue aValue)
{
	ComponentData data;

	float speed = aValue["speed"].GetFloat();
	data.insert(std::make_pair("speed", speed));
	
	return data;
}

ComponentData ComponentParser::ParseWeaponComponent(JsonValue aValue)
{
	return ComponentData();
}

void ComponentParser::Initialize()
{
	m_parsers.insert(std::make_pair("Animation",		&ParseAnimationComponent));
	m_parsers.insert(std::make_pair("AttackCollider",	&ParseAttackComponent));

	m_parsers.insert(std::make_pair("BehaviorTree",		&ParseBehaviorTreeComponent));
	m_parsers.insert(std::make_pair("Camera",			&ParseCameraComponent));
	m_parsers.insert(std::make_pair("DebugRect",		&ParseDebugRectComponent));
	m_parsers.insert(std::make_pair("Harvestable",		&ParseHarvestableComponent));
	m_parsers.insert(std::make_pair("Health",			&ParseHealthComponent));
	m_parsers.insert(std::make_pair("Hitbox",			&ParseHitboxComponent));

	m_parsers.insert(std::make_pair("Input",			&ParseInputComponent));
	m_parsers.insert(std::make_pair("Inventory",		&ParseInventoryComponent));
	m_parsers.insert(std::make_pair("MapChunk",			&ParseMapChunkComponent));
	m_parsers.insert(std::make_pair("Pickup",			&ParsePickupComponent));

	m_parsers.insert(std::make_pair("PlayerController", &ParsePlayerControllerComponent));
	m_parsers.insert(std::make_pair("Rect",				&ParseRectComponent));

	m_parsers.insert(std::make_pair("Resource",			&ParseResourceComponent));
	m_parsers.insert(std::make_pair("Spawner",			&ParseSpawnComponent));
	m_parsers.insert(std::make_pair("Sprite",			&ParseSpriteComponent));
	m_parsers.insert(std::make_pair("Stamina",			&ParseStaminaComponent));
	m_parsers.insert(std::make_pair("SteeringBehavior", &ParseSteeringBehaviorComponent));

	m_parsers.insert(std::make_pair("Timer",			&ParseTimerComponent));
	m_parsers.insert(std::make_pair("Transform",		&ParseTransformComponent));
	m_parsers.insert(std::make_pair("Trigger",			&ParseTriggerComponent));
	m_parsers.insert(std::make_pair("Velocity",			&ParseVelocityComponent));
	m_parsers.insert(std::make_pair("Weapon",			&ParseWeaponComponent));
	m_parsers.insert(std::make_pair("CharacterState",	&ParseCharacterStateComponent));
}