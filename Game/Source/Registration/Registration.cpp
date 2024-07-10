#include "Pch.h"
#include "Registration.h"
#include "Systems/SystemManager.h"
#include "Systems/Systems.h"
#include "Scenes/Scenes.h"
#include "Entities/EntityFactory.h"
#include "Components/Components.h"
#include "Components/ComponentBuilder.h"

namespace Registration
{
	void RegisterComponents(EntityFactory& factory) // takes in an factory?
	{
		/* - Core Components - */		
		factory.RegisterComponentBuilder<TagComponent>("tag");
		factory.RegisterComponentBuilder<AnimationComponent>("animation");
		factory.RegisterComponentBuilder<CameraComponent>("camera");
		factory.RegisterComponentBuilder<ColliderComponent>("collider");
		factory.RegisterComponentBuilder<CursorComponent>("cursor");
		factory.RegisterComponentBuilder<InputComponent>("input");
		factory.RegisterComponentBuilder<SpriteComponent>("sprite");
		factory.RegisterComponentBuilder<TransformComponent>("transform");
		factory.RegisterComponentBuilder<TextComponent>("text");
		factory.RegisterComponentBuilder<VelocityComponent>("velocity");
		factory.RegisterComponentBuilder<SubEntitiesComponent>("sub_entities");
		factory.RegisterComponentBuilder<SceneTransitionComponent>("scene_transition");
		factory.RegisterComponentBuilder<PlayerControllerComponent>("player_controller");
		factory.RegisterComponentBuilder<AudioComponent>("audio");

		/* - AI Components - */
		factory.RegisterComponentBuilder<BlackboardComponent>("blackboard");
		factory.RegisterComponentBuilder<BehaviorTreeComponent>("behavior_tree");
		factory.RegisterComponentBuilder<SteeringBehaviorComponent>("steering_behavior");
		factory.RegisterComponentBuilder<WanderBehaviorComponent>("wander_behavior");
		factory.RegisterComponentBuilder<FlockBehaviorComponent>("flock_behavior");
		factory.RegisterComponentBuilder<SeekBehaviorComponent>("seek_behavior");
		factory.RegisterComponentBuilder<FleeBehaviorComponent>("flee_behavior");
		//factory.RegisterComponentBuilder<StateMachineComponent>("state_machine");
		factory.RegisterComponentBuilder<IdleComponent>("idle");


		/* - Gameplay Components - */
		factory.RegisterComponentBuilder<AttributesComponent>("attribute");
		factory.RegisterComponentBuilder<PersonalityComponent>("personality");
		factory.RegisterComponentBuilder<FriendlyComponent>("friendly");
		factory.RegisterComponentBuilder<HostileComponent>("hostile");
		factory.RegisterComponentBuilder<CrewComponent>("crew");
		factory.RegisterComponentBuilder<HealthComponent>("health");
		factory.RegisterComponentBuilder<WeaponComponent>("weapon");
		factory.RegisterComponentBuilder<ToppleComponent>("topple");
		factory.RegisterComponentBuilder<ShakeComponent>("shake");
		factory.RegisterComponentBuilder<HarvestableComponent>("harvestable");
		factory.RegisterComponentBuilder<EquipmentComponent>("equipment");
		factory.RegisterComponentBuilder<EquippableComponent>("equippable");
		factory.RegisterComponentBuilder<InventoryComponent>("inventory");
		factory.RegisterComponentBuilder<CollectableComponent>("collectable");
		factory.RegisterComponentBuilder<SpawnComponent>("spawner");
		factory.RegisterComponentBuilder<EnvironmentComponent>("environment");

		factory.RegisterComponentBuilder<AttackComponent>("attack"); // RENAME!
		factory.RegisterComponentBuilder<ProjectileComponent>("projectile");
		factory.RegisterComponentBuilder<ResourceComponent>("resource");
		factory.RegisterComponentBuilder<CharacterStateComponent>("character_state");
		factory.RegisterComponentBuilder<KnockbackComponent>("knockback");

		/* - UI Components - */
		factory.RegisterComponentBuilder<HUDComponent>("hud");
		factory.RegisterComponentBuilder<UIComponent>("ui");
		factory.RegisterComponentBuilder<ButtonComponent>("button");
		factory.RegisterComponentBuilder<MapChunkComponent>("map_chunk");
		factory.RegisterComponentBuilder<GridComponent>("grid");

		/* - Utility Components - */
		factory.RegisterComponentBuilder<WorldTimeComponent>("world_time");
		factory.RegisterComponentBuilder<TimerComponent>("timer");
	}

	void RegisterSystems(SystemManager& systemManager)
	{
		/* - Core Systems - */
		systemManager.Register<InputSystem>("InputSystem");
		systemManager.Register<MovementSystem>("MovementSystem");
		systemManager.Register<CameraSystem>("CameraSystem");
		systemManager.Register<CollisionSystem>("CollisionSystem");
		systemManager.Register<PlayerControllerSystem>("PlayerControllerSystem");
		systemManager.Register<SceneTransitionSystem>("SceneTransitionSystem");
		systemManager.Register<SpriteAnimationSystem>("SpriteAnimationSystem");

		/* - Gameplay Systems - */
		systemManager.Register<CombatSystem>("CombatSystem");
		systemManager.Register<EnemySpawnSystem>("EnemySpawnSystem");
		systemManager.Register<EquipmentSystem>("EquipmentSystem");
		systemManager.Register<InventorySystem>("InventorySystem");
		systemManager.Register<MeleeCombatSystem>("MeleeCombatSystem");
		systemManager.Register<RangedCombatSystem>("RangedCombatSystem");
		systemManager.Register<ShakeSystem>("ShakeSystem");
		systemManager.Register<TimeSystem>("TimeSystem");
		systemManager.Register<SpawnSystem>("SpawnSystem");
		systemManager.Register<StatSystem>("StatSystem");

		/* - Map Systems - */
		systemManager.Register<MapGenerationSystem>("MapGenerationSystem");
		systemManager.Register<MapDecorationSystem>("MapDecorationSystem");

		/* -  UI Systems - */
		systemManager.Register<UISystem>("UISystem");
		systemManager.Register<HUDSystem>("HUDSystem");

		/* - AI Systems - */
		systemManager.Register<BlackboardSystem>("BlackboardSystem");
		systemManager.Register<BehaviorTreeSystem>("BehaviorTreeSystem");
		systemManager.Register<SteeringBehaviorSystem>("SteeringBehaviorSystem");
		systemManager.Register<StateTransitionSystem>("StateTransitionSystem");

		/* - Audio System - */
		systemManager.Register<AudioSystem>("AudioSystem");

		/* - Render Systems - */
		systemManager.Register<DebugRenderSystem>("DebugRenderSystem");
		systemManager.Register<TextRenderSystem>("TextRenderSystem");
		systemManager.Register<UIRenderSystem>("UIRenderSystem");
		systemManager.Register<SpriteRenderSystem>("SpriteRenderSystem");
		systemManager.Register<MapRenderSystem>("MapRenderSystem");




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

	void RegisterBlueprints()
	{
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
