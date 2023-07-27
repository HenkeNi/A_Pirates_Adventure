#pragma once

// Rename??

// Make class?? std::unoreder_map<string, std::function<Component*<aValue>();

//#include "../Blueprints/EntityBlueprint.h"


class ComponentParser
{
public:
	using ComponentData = std::unordered_map<std::string, std::any>;
	using JsonValue = const rapidjson::Value&;

	static ComponentData ParseComponentFromJson(const std::string& aType, JsonValue aValue);

	// Component parsers...
	static ComponentData ParseAnimationComponent(JsonValue aValue);

	static ComponentData ParseAttackComponent(JsonValue aValue);

	static ComponentData ParseBehaviorTreeComponent(JsonValue aValue);
	
	static ComponentData ParseCameraComponent(JsonValue aValue);

	static ComponentData ParseCharacterStateComponent(JsonValue aValue);

	static ComponentData ParseHarvestableComponent(JsonValue aValue);

	static ComponentData ParseHealthComponent(JsonValue aValue);

	static ComponentData ParseHitboxComponent(JsonValue aValue);

	static ComponentData ParseInputComponent(JsonValue aValue);

	static ComponentData ParseInventoryComponent(JsonValue aValue);

	static ComponentData ParseMapChunkComponent(JsonValue aValue);

	static ComponentData ParsePickupComponent(JsonValue aValue);

	static ComponentData ParsePlayerControllerComponent(JsonValue aValue);
	
	static ComponentData ParseRectComponent(JsonValue aValue);

	static ComponentData ParseResourceComponent(JsonValue aValue);

	static ComponentData ParseSpawnComponent(JsonValue aValue);

	static ComponentData ParseSpriteComponent(JsonValue aValue);

	static ComponentData ParseStaminaComponent(JsonValue aValue);

	static ComponentData ParseSteeringBehaviorComponent(JsonValue aValue);

	static ComponentData ParseTimerComponent(JsonValue aValue);

	static ComponentData ParseTransformComponent(JsonValue aValue);
	
	static ComponentData ParseVelocityComponent(JsonValue aValue);

	static ComponentData ParseWeaponComponent(JsonValue aValue);

private:
	static void Initialize();

	static std::unordered_map<std::string, std::function<ComponentData(JsonValue)>> m_parsers;
	static bool m_isInitialized;
};