#pragma once

// Fix!
namespace
{
	using ComponentData = std::unordered_map<std::string, std::any>;
}

class ComponentInitializer
{
public:
	static void InitializeComponent(class Component* component, const ComponentData& data);

	static void InitializeComponent(class AnimationComponent* component, const ComponentData& data);

	static void InitializeComponent(class AttackComponent* component, const ComponentData& data);

	static void InitializeComponent(class AttributesComponent* component, const ComponentData& data);

	static void InitializeComponent(class AudioComponent* component, const ComponentData& data);

	static void InitializeComponent(class BehaviorTreeComponent* component, const ComponentData& data);

	static void InitializeComponent(class ButtonComponent* component, const ComponentData& data);

	static void InitializeComponent(class CameraComponent* component, const ComponentData& data);

	static void InitializeComponent(class CharacterStateComponent* component, const ComponentData& data);

	static void InitializeComponent(class ColliderComponent* component, const ComponentData& data);

	static void InitializeComponent(class EnvironmentComponent* component, const ComponentData& data);

	static void InitializeComponent(class GridComponent* component, const ComponentData& data);

	static void InitializeComponent(class HarvestableComponent* component, const ComponentData& data);

	static void InitializeComponent(class HealthComponent* component, const ComponentData& data);

	static void InitializeComponent(class InventoryComponent* component, const ComponentData& data);

	static void InitializeComponent(class MapChunkComponent* component, const ComponentData& data);

	static void InitializeComponent(class PlayerControllerComponent* component, const ComponentData& data);

	static void InitializeComponent(class SpawnComponent* component, const ComponentData& data);

	static void InitializeComponent(class SpriteComponent* component, const ComponentData& data);

	static void InitializeComponent(class SteeringBehaviorComponent* component, const ComponentData& data);

	static void InitializeComponent(class TransformComponent* component, const ComponentData& data);

	static void InitializeComponent(class TextComponent* component, const ComponentData& data);

	static void InitializeComponent(class ResourceComponent* component, const ComponentData& data);

	static void InitializeComponent(class VelocityComponent* component, const ComponentData& data);

	static void InitializeComponent(class WeaponComponent* component, const ComponentData& data);

	static void InitializeComponent(class WorldTimeComponent* component, const ComponentData& data);

	static void InitializeComponent(class WanderBehaviorComponent* component, const ComponentData& data);

	static void InitializeComponent(class PersonalityComponent* component, const ComponentData& data);

	static void InitializeComponent(class FlockBehaviorComponent* component, const ComponentData& data);

	static void InitializeComponent(class SeekBehaviorComponent* component, const ComponentData& data);

	static void InitializeComponent(class FleeBehaviorComponent* component, const ComponentData& data);

	static void InitializeComponent(class ShakeComponent* component, const ComponentData& data);

	static void InitializeComponent(class TagComponent* component, const ComponentData& data);

	static void InitializeComponent(class ToppleComponent* component, const ComponentData& data);

	static void InitializeComponent(class SceneTransitionComponent* component, const ComponentData& data);

	static void InitializeComponent(class TimerComponent* component, const ComponentData& data);

	static void InitializeComponent(class UIComponent* component, const ComponentData& data);
};