#include "Pch.h"
#include "Registration.h"
#include "ECS.h"
#include "Systems/SystemManager.h"
#include "Systems/Systems.h"
#include "Scenes/Scenes.h"
#include "Components/Components.h"


namespace Registration
{
	void RegisterComponents(ECS& ecs)
	{
		/* - Core Components - */
		ecs.RegisterComponent<TagComponent>("Tag");
		ecs.RegisterComponent<AnimationComponent>("Animation");
		ecs.RegisterComponent<CameraComponent>("Camera");
		ecs.RegisterComponent<ColliderComponent>("Collider");
		ecs.RegisterComponent<CursorComponent>("Cursor");
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
		ecs.RegisterComponent<SteeringBehaviorComponent>("SteeringBehavior");
		ecs.RegisterComponent<WanderBehaviorComponent>("WanderBehavior");
		ecs.RegisterComponent<FlockBehaviorComponent>("FlockBehavior");
		ecs.RegisterComponent<SeekBehaviorComponent>("SeekBehavior");
		ecs.RegisterComponent<FleeBehaviorComponent>("FleeBehavior");
		// ecs.RegisterComponent<StateMachineComponent>("state_machine");
		ecs.RegisterComponent<IdleComponent>("Idle");

		/* - Gameplay Components - */
		ecs.RegisterComponent<AttributesComponent>("Attribute");
		ecs.RegisterComponent<PersonalityComponent>("Personality");
		ecs.RegisterComponent<FriendlyComponent>("Friendly");
		ecs.RegisterComponent<HostileComponent>("Hostile");
		ecs.RegisterComponent<CrewComponent>("Crew");
		ecs.RegisterComponent<HealthComponent>("Health");
		ecs.RegisterComponent<WeaponComponent>("Weapon");
		ecs.RegisterComponent<ToppleComponent>("Topple");
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
		ecs.RegisterComponent<KnockbackComponent>("Knockback");

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

	void RegisterSystems(ECS& ecs)
	{
		/* - Core Systems - */
		ecs.RegisterSystem<InputSystem>("InputSystem");
		ecs.RegisterSystem<MovementSystem>("MovementSystem");
		ecs.RegisterSystem<CameraSystem>("CameraSystem");
		ecs.RegisterSystem<CollisionSystem>("CollisionSystem");
		ecs.RegisterSystem<PhysicsSystem>("PhysicsSystem");
		ecs.RegisterSystem<PlayerControllerSystem>("PlayerControllerSystem");
		ecs.RegisterSystem<SceneTransitionSystem>("SceneTransitionSystem");
		//ecs.RegisterSystem<SpriteAnimationSystem>("SpriteAnimationSystem");

		/* - Gameplay Systems - */
		ecs.RegisterSystem<CombatSystem>("CombatSystem");
		//ecs.RegisterSystem<EnemySpawnSystem>("EnemySpawnSystem");
		ecs.RegisterSystem<EquipmentSystem>("EquipmentSystem");
		ecs.RegisterSystem<InventorySystem>("InventorySystem");
		ecs.RegisterSystem<ProjectileSystem>("ProjectileSystem");
		ecs.RegisterSystem<ShakeSystem>("ShakeSystem");
		ecs.RegisterSystem<TimeSystem>("TimeSystem");
		ecs.RegisterSystem<SpawnSystem>("SpawnSystem");
		//ecs.RegisterSystem<StatSystem>("StatSystem");

		/* - Map Systems - */
		ecs.RegisterSystem<MapGenerationSystem>("MapGenerationSystem");
		ecs.RegisterSystem<MapDecorationSystem>("MapDecorationSystem");

		/* -  UI Systems - */
		ecs.RegisterSystem<UISystem>("UISystem");
		ecs.RegisterSystem<HUDSystem>("HUDSystem");

		/* - AI Systems - */
		//ecs.RegisterSystem<BlackboardSystem>("BlackboardSystem");
		//ecs.RegisterSystem<BehaviorTreeSystem>("BehaviorTreeSystem");
		//ecs.RegisterSystem<SteeringBehaviorSystem>("SteeringBehaviorSystem");
		//ecs.RegisterSystem<StateTransitionSystem>("StateTransitionSystem");

		/* - Audio System - */
		ecs.RegisterSystem<AudioSystem>("AudioSystem");

		/* - Render Systems - */
		ecs.RegisterSystem<RenderSystem>("RenderSystem");
	}

	void RegisterScenes(SceneManager& sceneManager, ECS& ecs)
	{
		// Register game's scene here as well?
	
		sceneManager.Register<GameScene>(eScene::Game, ecs);
		sceneManager.Register<LoadingScene>(eScene::Loading, ecs);
		sceneManager.Register<MenuScene>(eScene::Menu, ecs);
		sceneManager.Register<SettingsScene>(eScene::Settings, ecs);
		sceneManager.Register<TitleScene>(eScene::Title, ecs);
	}
}
