#pragma once

// Rename??
namespace JsonParser
{
	using JsonValue = const rapidjson::Value&;

	// TODO; put helper functions in same file as components??

	/* AI */
	void ParseBehaviorTreeComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);

	void ParseSteeringBehaviorComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);


	/* Character */


	/* Combat */
	void ParseWeaponComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);

	void ParseHitboxComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);

	void ParseAttackComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);
	
	void ParsePickupComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);
	

	/* Controllers */
	void ParsePlayerControllerComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);
	

	/* Core */
	void ParseTransformComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);

	void ParseInputComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);


	/* Equipment */
	

	/* Inventory */
	void ParseInventoryComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);
	

	/* Physics */
	void ParseVelocityComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);


	/* Rendering */
	void ParseSpriteComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);

	void ParseAnimationComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);

	void ParseCameraComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);

	void ParseRectComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);


	/* Resource */
	void ParseResourceComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);


	/* Stats */
	void ParseHealthComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);
	
	void ParseStaminaComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);
	
	
	/* UI */
	
	/* Utility */
	void ParseTimerComponent(JsonValue aValue, std::unordered_map<std::string, std::any>& someComponentData);
}

