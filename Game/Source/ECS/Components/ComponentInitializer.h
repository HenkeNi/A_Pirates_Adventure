#pragma once
#include "Components.h"

class ComponentInitializer
{
public:
	//static void InitializeComponent(class Component* component, const ComponentData& data);
	//template <typename T>
	/*static void Init(void* component, const ComponentProperties& properties)
	{
		InitializeComponent(component, properties);
	}*/

	
	// static void InitializeComponent(void* component, const ComponentProperties& properties) {};

	template <typename T>
	inline static void InitializeComponent(T* component, const ComponentProperties& properties)
	{	
		int x = 20;
		x += 20;
	}

	template <>
	inline static void InitializeComponent(TransformComponent* component, const ComponentProperties& properties)
	{
		int x = 20;
		x += 20;
	}

	template <>
	inline static void InitializeComponent(UIComponent* component, const ComponentProperties& properties)
	{
	}



	//static void InitializeComponent(struct AnimationComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct AttackComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct AttributesComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct AudioComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct BehaviorTreeComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct ButtonComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct CameraComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct CharacterStateComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct ColliderComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct EnvironmentComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct GridComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct HarvestableComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct HealthComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct InventoryComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct MapChunkComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct PlayerControllerComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct SpawnComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct SpriteComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct SteeringBehaviorComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct TransformComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct TextComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct ResourceComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct VelocityComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct WeaponComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct WorldTimeComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct WanderBehaviorComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct PersonalityComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct FlockBehaviorComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct SeekBehaviorComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct FleeBehaviorComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct ShakeComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct TagComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct ToppleComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct SceneTransitionComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct TimerComponent* component, const ComponentProperties& properties);

	//static void InitializeComponent(struct UIComponent* component, const ComponentProperties& properties);
};