#include "Pch.h"
#include "Registration.h"
#include "ECS.h"
#include "Systems/SystemManager.h"
#include "Systems/Systems.h"
#include "Scenes/Scenes.h"
//#include "Entities/EntityFactory.h"
#include "Components/Components.h"
#include "Components/ComponentBuilder.h"

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

		ecs.RegisterComponent<AttackComponent>("Attack"); // RENAME!
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
		//systemManager.Register<InputSystem>("InputSystem");
		//systemManager.Register<MovementSystem>("MovementSystem");
		ecs.RegisterSystem<CameraSystem>("CameraSystem");
		//systemManager.Register<CollisionSystem>("CollisionSystem");
		//systemManager.Register<PlayerControllerSystem>("PlayerControllerSystem");
		//systemManager.Register<SceneTransitionSystem>("SceneTransitionSystem");
		//systemManager.Register<SpriteAnimationSystem>("SpriteAnimationSystem");

		///* - Gameplay Systems - */
		//systemManager.Register<CombatSystem>("CombatSystem");
		//systemManager.Register<EnemySpawnSystem>("EnemySpawnSystem");
		//systemManager.Register<EquipmentSystem>("EquipmentSystem");
		//systemManager.Register<InventorySystem>("InventorySystem");
		//systemManager.Register<MeleeCombatSystem>("MeleeCombatSystem");
		//systemManager.Register<RangedCombatSystem>("RangedCombatSystem");
		//systemManager.Register<ShakeSystem>("ShakeSystem");
		//systemManager.Register<TimeSystem>("TimeSystem");
		//systemManager.Register<SpawnSystem>("SpawnSystem");
		//systemManager.Register<StatSystem>("StatSystem");

		///* - Map Systems - */
		//systemManager.Register<MapGenerationSystem>("MapGenerationSystem");
		//systemManager.Register<MapDecorationSystem>("MapDecorationSystem");

		///* -  UI Systems - */
		//systemManager.Register<UISystem>("UISystem");
		//systemManager.Register<HUDSystem>("HUDSystem");

		///* - AI Systems - */
		//systemManager.Register<BlackboardSystem>("BlackboardSystem");
		//systemManager.Register<BehaviorTreeSystem>("BehaviorTreeSystem");
		//systemManager.Register<SteeringBehaviorSystem>("SteeringBehaviorSystem");
		//systemManager.Register<StateTransitionSystem>("StateTransitionSystem");

		///* - Audio System - */
		//systemManager.Register<AudioSystem>("AudioSystem");

		///* - Render Systems - */
		//systemManager.Register<DebugRenderSystem>("DebugRenderSystem");
		//systemManager.Register<TextRenderSystem>("TextRenderSystem");
		ecs.RegisterSystem<UIRenderSystem>("UIRenderSystem");
		//systemManager.Register<SpriteRenderSystem>("SpriteRenderSystem");
		//systemManager.Register<MapRenderSystem>("MapRenderSystem");




//		/* - Core Systems - */
//		systemManager.Register<InputSystem>();
//		systemManager.Register<MovementSystem>();
//		systemManager.Register<CameraSystem>();
//		systemManager.Register<CollisionSystem>();
//		systemManager.Register<PlayerControllerSystem>();
//		systemManager.Register<SceneTransitionSystem>();
//
//		/* - Gameplay Systems - */
//		systemManager.Register<CombatSystem>();
//		systemManager.Register<EnemySpawnSystem>();
//		systemManager.Register<EquipmentSystem>();
//		systemManager.Register<InventorySystem>();
//		systemManager.Register<MeleeCombatSystem>();
//		systemManager.Register<RangedCombatSystem>();
//		systemManager.Register<ShakeSystem>();
//		systemManager.Register<TimeSystem>();
//		systemManager.Register<SpawnSystem>();
//		systemManager.Register<StatSystem>();
//
//		systemManager.Register<SpriteAnimationSystem>();
//
//		/* - Map Systems - */
//		systemManager.Register<MapGenerationSystem>();
//		systemManager.Register<MapDecorationSystem>();
//
//		/* -  UI Systems - */
//		systemManager.Register<UISystem>();
//		systemManager.Register<HUDSystem>();
//
//		/* - AI Systems - */
//		systemManager.Register<BlackboardSystem>();
//		systemManager.Register<BehaviorTreeSystem>();
//		systemManager.Register<SteeringBehaviorSystem>();
//		systemManager.Register<StateTransitionSystem>();
//
//		/* - Audio System - */
//		systemManager.Register<AudioSystem>();
//
//		/* - Render Systems - */
//#ifdef DEBUG
//
//		systemManager.Register<DebugRenderSystem>();
//
//#endif // DEBUG
//
//		systemManager.Register<TextRenderSystem>();
//		systemManager.Register<UIRenderSystem>();
//		systemManager.Register<SpriteRenderSystem>();
//		systemManager.Register<MapRenderSystem>();
	}

	void RegisterBlueprints(ECS& ecs)
	{
		// ecs.GetEntityFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");


		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_Enemy.json");
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_Environment.json");
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_UI.json");
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
