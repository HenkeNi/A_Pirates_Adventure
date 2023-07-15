#include "Pch.h"
#include "EntityManager.h"
#include "Entity.h"
#include "../PostMaster/Message.h"
#include "../PostMaster/PostMaster.h"

#include "../Utility/JsonParser.h"

#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"
#include "Controllers/ControllerComponents.h"
#include "Physics/PhysicsComponents.h"
#include "Combat/CombatComponents.h"
#include <Stats/StatsComponents.h>
#include "Resource/ResourceComponents.h"
#include "Inventory/InventoryComponents.h"

EntityFactory EntityManager::s_entityFactory;

EntityManager::EntityManager()
{
	m_entities.reserve(512);
}

EntityManager::~EntityManager()
{
}

void EntityManager::LoadBlueprints(const std::string& aFilePath)
{
	auto loadBlueprintsFromJson = [](const std::string& aFilePath)
	{
		std::ifstream ifs{ aFilePath };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		document.Parse(content.c_str());

		assert(!document.HasParseError() && "Failed to parse Blueprints");

		std::string identifier = document["name"].GetString();

		EntityBlueprint blueprint;

		for (auto& component : document["components"].GetArray())
		{
			std::unordered_map<std::string, std::any> componentData;
			
			std::string type = component["type"].GetString(); // noT WOKRIG!!! ALSO EXPAND WITH MORE CASES

			if (type == "Transform")
			{
				JsonParser::ParseTransformComponent(component, componentData);			
			}
			else if (type == "Sprite")
			{
				JsonParser::ParseSpriteComponent(component, componentData);
			}
			else if (type == "Input")
			{
				JsonParser::ParseInputComponent(component, componentData);
			}
			else if (type == "Velocity")
			{
				JsonParser::ParseVelocityComponent(component, componentData);
			}
			else if (type == "Hitbox")
			{
				JsonParser::ParseHitboxComponent(component, componentData);
			}
			else if (type == "Health")
			{
				JsonParser::ParseHealthComponent(component, componentData);
			}
			else if (type == "Rect")
			{
				JsonParser::ParseRectComponent(component, componentData);
			}
			else if (type == "Resource")
			{
				JsonParser::ParseResourceComponent(component, componentData);
			}
			else if (type == "BehaviorTree")
			{
				JsonParser::ParseBehaviorTreeComponent(component, componentData);
			}
			else if (type == "SteeringBehavior")
			{
				JsonParser::ParseSteeringBehaviorComponent(component, componentData);
			}
			else if (type == "Camera")
			{
				JsonParser::ParseCameraComponent(component, componentData);
			}
			else if (type == "PlayerController")
			{
				JsonParser::ParsePlayerControllerComponent(component, componentData);
			}
			else if (type == "Pickup")
			{
				JsonParser::ParsePickupComponent(component, componentData);
			}
			else if (type == "Animation")
			{
				JsonParser::ParseAnimationComponent(component, componentData);
			}
			else if (type == "AttackCollider")
			{
				JsonParser::ParseAttackComponent(component, componentData);
			}
			else if (type == "Weapon")
			{
				JsonParser::ParseWeaponComponent(component, componentData);
			}
			else if (type == "Inventory")
			{
				JsonParser::ParseInventoryComponent(component, componentData);
			}
			else if (type == "Stamina")
			{
				JsonParser::ParseStaminaComponent(component, componentData);
			}
			else if (type == "Timer")
			{
				JsonParser::ParseTimerComponent(component, componentData);
			}
			blueprint.AddComponent(type, componentData);
		}

		s_entityFactory.RegisterBlueprint(identifier, blueprint);
	};

	std::ifstream ifs{ aFilePath };
	std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

	rapidjson::Document document;
	document.Parse(content.c_str());

	assert(!document.HasParseError() && "Failed to parse Blueprints");
	
	for (auto& blueprint : document["blueprints"]["player"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}

	for (auto& blueprint : document["blueprints"]["enemies"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}

	for (auto& blueprint : document["blueprints"]["props"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}

	for (auto& blueprint : document["blueprints"]["cameras"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}

	for (auto& blueprint : document["blueprints"]["resources"].GetArray())
	{
		loadBlueprintsFromJson(blueprint.GetString());
	}
}

Entity* EntityManager::Create(const std::string& aType)
{
	auto entity = s_entityFactory.Create(aType);

	m_entities.push_back(std::move(entity));

	auto* created = &m_entities.back();
	PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityCreated, created });

	return created;
}

Entity* EntityManager::Find(unsigned anID)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& anEntity) { return anEntity.GetID() == anID; });

	if (it != m_entities.end())
		return &(*it);

	return nullptr;
}

void EntityManager::Destroy(unsigned anID)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& anEntity) { return anEntity.GetID() == anID; });

	if (it != m_entities.end())
	{
		PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityDestroyed, &(*it) });
		m_entities.erase(it);
	}
}

void EntityManager::DestroyAll()
{
	m_entities.clear();
}