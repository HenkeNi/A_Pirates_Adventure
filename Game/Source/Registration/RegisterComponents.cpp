#include "Pch.h"
#include "RegisterComponents.h"
#include "ECS.h"
#include "Components/Components.h"


namespace Registration
{
	void RegisterComponents(ECS& ecs)
	{
		/* - Core Components - */
		ecs.RegisterComponent<TagComponent>("Tag");
		ecs.RegisterComponent<AnimationComponent>("Animation");
		ecs.RegisterComponent<BoundingBoxComponent>("BoundingBox");
		ecs.RegisterComponent<CameraComponent>("Camera");
		ecs.RegisterComponent<PhysicsComponent>("Physics");
		ecs.RegisterComponent<ColliderComponent>("Collider");
		ecs.RegisterComponent<CursorComponent>("Cursor"); // No need`? set in enigne?
		ecs.RegisterComponent<InputComponent>("Input");
		ecs.RegisterComponent<SpriteComponent>("Sprite");
		ecs.RegisterComponent<TransformComponent>("Transform");
		ecs.RegisterComponent<TextComponent>("Text");
		ecs.RegisterComponent<VelocityComponent>("Velocity");
		ecs.RegisterComponent<SubEntitiesComponent>("SubEntities");
		ecs.RegisterComponent<SceneTransitionComponent>("SceneTransition");
		ecs.RegisterComponent<PlayerControllerComponent>("PlayerController");
		ecs.RegisterComponent<AudioComponent>("Audio");

		/* - AI Components - */
		ecs.RegisterComponent<BlackboardComponent>("Blackboard");
		ecs.RegisterComponent<BehaviorTreeComponent>("BehaviorTree");
		//ecs.RegisterComponent<SteeringBehaviorComponent>("SteeringBehavior");
		//ecs.RegisterComponent<WanderBehaviorComponent>("WanderBehavior");
		//ecs.RegisterComponent<FlockBehaviorComponent>("FlockBehavior");
		//ecs.RegisterComponent<SeekBehaviorComponent>("SeekBehavior");
		//ecs.RegisterComponent<FleeBehaviorComponent>("FleeBehavior");
		// ecs.RegisterComponent<StateMachineComponent>("state_machine");
		//ecs.RegisterComponent<IdleComponent>("Idle");

		/* - Gameplay Components - */
		ecs.RegisterComponent<AttributesComponent>("Attribute");
		ecs.RegisterComponent<PersonalityComponent>("Personality");
		ecs.RegisterComponent<FriendlyComponent>("Friendly");
		ecs.RegisterComponent<HostileComponent>("Hostile");
		//ecs.RegisterComponent<CrewComponent>("Crew");
		ecs.RegisterComponent<HealthComponent>("Health");
		ecs.RegisterComponent<WeaponComponent>("Weapon");
		// ecs.RegisterComponent<ToppleComponent>("Topple");
		ecs.RegisterComponent<ShakeComponent>("Shake");
		ecs.RegisterComponent<HarvestableComponent>("Harvestable");
		ecs.RegisterComponent<EquipmentComponent>("Equipment");
		ecs.RegisterComponent<EquippableComponent>("Equippable");
		ecs.RegisterComponent<InventoryComponent>("Inventory");
		ecs.RegisterComponent<CollectableComponent>("Collectable");
		ecs.RegisterComponent<SpawnComponent>("Spawner");
		ecs.RegisterComponent<EnvironmentComponent>("Environment");

		ecs.RegisterComponent<AttackComponent>("Attack");
		ecs.RegisterComponent<AttackCooldownComponent>("AttackCooldown");
		ecs.RegisterComponent<ProjectileComponent>("Projectile");
		ecs.RegisterComponent<ResourceComponent>("Resource");
		ecs.RegisterComponent<CharacterStateComponent>("CharacterState");
		ecs.RegisterComponent<KnockbackComponent>("Knockback"); // remove?

		/* - UI Components - */
		ecs.RegisterComponent<HUDComponent>("HUD");
		ecs.RegisterComponent<UIComponent>("UI");
		ecs.RegisterComponent<ButtonComponent>("Button");
		ecs.RegisterComponent<MapChunkComponent>("MapChunk");
		ecs.RegisterComponent<GridComponent>("Grid");

		/* - Utility Components - */
		ecs.RegisterComponent<WorldTimeComponent>("WorldTime");
		ecs.RegisterComponent<TimerComponent>("Timer");
	}
}
