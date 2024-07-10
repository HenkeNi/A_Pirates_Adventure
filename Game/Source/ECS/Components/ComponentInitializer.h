#pragma once
#include "Components.h"


// Fix!
namespace
{
	using ComponentData = std::unordered_map<std::string, std::any>;
}

class ComponentInitializer
{
public:
	static void InitializeComponent(Component* component, const ComponentData& data);

	static void InitializeComponent(AnimationComponent* component, const ComponentData& data);

	static void InitializeComponent(AttackComponent* component, const ComponentData& data);

	static void InitializeComponent(AttributesComponent* component, const ComponentData& data);

	static void InitializeComponent(AudioComponent* component, const ComponentData& data);

	static void InitializeComponent(BehaviorTreeComponent* component, const ComponentData& data);

	static void InitializeComponent(ButtonComponent* component, const ComponentData& data);

	static void InitializeComponent(CameraComponent* component, const ComponentData& data);

	static void InitializeComponent(CharacterStateComponent* component, const ComponentData& data);

	static void InitializeComponent(ColliderComponent* component, const ComponentData& data);

	static void InitializeComponent(EnvironmentComponent* component, const ComponentData& data);

	static void InitializeComponent(GridComponent* component, const ComponentData& data);

	static void InitializeComponent(HarvestableComponent* component, const ComponentData& data);

	static void InitializeComponent(HealthComponent* component, const ComponentData& data);

	static void InitializeComponent(InventoryComponent* component, const ComponentData& data);

	static void InitializeComponent(MapChunkComponent* component, const ComponentData& data);

	static void InitializeComponent(PlayerControllerComponent* component, const ComponentData& data);

	static void InitializeComponent(SpawnComponent* component, const ComponentData& data);

	static void InitializeComponent(SpriteComponent* component, const ComponentData& data);

	static void InitializeComponent(SteeringBehaviorComponent* component, const ComponentData& data);

	static void InitializeComponent(TransformComponent* component, const ComponentData& data);

	static void InitializeComponent(TextComponent* component, const ComponentData& data);

	static void InitializeComponent(ResourceComponent* component, const ComponentData& data);

	static void InitializeComponent(VelocityComponent* component, const ComponentData& data);

	static void InitializeComponent(WeaponComponent* component, const ComponentData& data);

	static void InitializeComponent(WorldTimeComponent* component, const ComponentData& data);

	static void InitializeComponent(WanderBehaviorComponent* component, const ComponentData& data);

	static void InitializeComponent(PersonalityComponent* component, const ComponentData& data);

	static void InitializeComponent(FlockBehaviorComponent* component, const ComponentData& data);

	static void InitializeComponent(SeekBehaviorComponent* component, const ComponentData& data);

	static void InitializeComponent(FleeBehaviorComponent* component, const ComponentData& data);

	static void InitializeComponent(ShakeComponent* component, const ComponentData& data);

	static void InitializeComponent(TagComponent* component, const ComponentData& data);

	static void InitializeComponent(ToppleComponent* component, const ComponentData& data);

	static void InitializeComponent(SceneTransitionComponent* component, const ComponentData& data);

	static void InitializeComponent(TimerComponent* component, const ComponentData& data);

	static void InitializeComponent(UIComponent* component, const ComponentData& data);
};