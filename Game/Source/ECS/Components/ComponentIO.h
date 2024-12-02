#pragma once


class ComponentIO
{
public:

	static void Serialize(const void* component, const SerializationData& data) {};

	static void Serialize(const struct TransformComponent* component, const SerializationData& data);

	static void Serialize(const struct TagComponent* component);
	
	static void Serialize(const struct AnimationComponent* component);
	
	static void Serialize(const struct BoundingBoxComponent* component);
	
	static void Serialize(const struct CameraComponent* component);
	
	static void Serialize(const struct PhysicsComponent* component);
	
	static void Serialize(const struct ColliderComponent* component);
	
	static void Serialize(const struct CursorComponent* component);

	static void Serialize(const struct InputComponent* component);

	static void Serialize(const struct SpriteComponent* component);

	static void Serialize(const struct TextComponent* component);

	static void Serialize(const struct VelocityComponent* component);

	static void Serialize(const struct SubEntitiesComponent* component);

	static void Serialize(const struct SceneTransitionComponent* component);

	static void Serialize(const struct PlayerControllerComponent* component);

	static void Serialize(const struct AudioComponent* component);

	static void Serialize(const struct BlackboardComponent* component);

	static void Serialize(const struct BehaviorTreeComponent* component);

	static void Serialize(const struct AttributesComponent* component);

	static void Serialize(const struct PersonalityComponent* component);

	static void Serialize(const struct FriendlyComponent* component);

	static void Serialize(const struct HostileComponent* component);


	// Not needed?? creaet entity from json instead??
	//static void Deserialize(struct TransformComponent& component, ComponentProperties& properties); // ?
	//static void Deserialize(struct TransformComponent& component);
};