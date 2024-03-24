#include "Pch.h"
#include "Registration.h"
#include "Systems/SystemManager.h"
#include "Systems/Systems.h"
#include "Scenes/Scenes.h"
#include "Components/Components.h"
#include "Components/ComponentBuilder.h"


namespace Registration
{
	void RegisterComponents() // takes in an factory?
	{
		auto& Factory = EntityManager::GetFactory();

		
		/* - Core Components - */		
		Factory.RegisterComponentBuilder<AnimationComponent>("animation");
		Factory.RegisterComponentBuilder<CameraComponent>("camera");
		Factory.RegisterComponentBuilder<ColliderComponent>("collider");
		Factory.RegisterComponentBuilder<CursorComponent>("cursor");
		Factory.RegisterComponentBuilder<InputComponent>("input");
		Factory.RegisterComponentBuilder<SpriteComponent>("sprite");
		Factory.RegisterComponentBuilder<TransformComponent>("transform");
		Factory.RegisterComponentBuilder<TextComponent>("text");
		Factory.RegisterComponentBuilder<VelocityComponent>("velocity");
		Factory.RegisterComponentBuilder<SubEntitiesComponent>("sub_entities");
		Factory.RegisterComponentBuilder<SceneTransitionComponent>("scene_transition");
		Factory.RegisterComponentBuilder<PlayerControllerComponent>("player_controller");

		/* - AI Components - */
		Factory.RegisterComponentBuilder<BlackboardComponent>("blackboard");
		Factory.RegisterComponentBuilder<SteeringBehaviorComponent>("steering_behavior");
		Factory.RegisterComponentBuilder<WanderBehaviorComponent>("wander_behavior");
		Factory.RegisterComponentBuilder<FlockBehaviorComponent>("flock_behavior");
		Factory.RegisterComponentBuilder<SeekBehaviorComponent>("seek_behavior");
		Factory.RegisterComponentBuilder<FleeBehaviorComponent>("flee_behavior");
		Factory.RegisterComponentBuilder<StateMachineComponent>("state_machine");
		Factory.RegisterComponentBuilder<BehaviorTreeComponent>("behavior_tree");

		/* - Gameplay Components - */
		Factory.RegisterComponentBuilder<HealthComponent>("health");
		Factory.RegisterComponentBuilder<WeaponComponent>("weapon");
		Factory.RegisterComponentBuilder<ToppleComponent>("topple");
		Factory.RegisterComponentBuilder<ShakeComponent>("shake");
		Factory.RegisterComponentBuilder<HarvestableComponent>("harvestable");
		Factory.RegisterComponentBuilder<EquipmentComponent>("equipment");
		Factory.RegisterComponentBuilder<EquippableComponent>("equippable");
		Factory.RegisterComponentBuilder<InventoryComponent>("inventory");
		Factory.RegisterComponentBuilder<CollectableComponent>("collectable");
		Factory.RegisterComponentBuilder<SpawnComponent>("spawner");


		Factory.RegisterComponentBuilder<AttackComponent>("attack"); // RENAME!
		Factory.RegisterComponentBuilder<ProjectileComponent>("projectile");
		Factory.RegisterComponentBuilder<ResourceComponent>("resource");
		Factory.RegisterComponentBuilder<CharacterStateComponent>("character_state");
		Factory.RegisterComponentBuilder<KnockbackComponent>("knockback");


		/* - UI Components - */
		Factory.RegisterComponentBuilder<HUDComponent>("hud");
		Factory.RegisterComponentBuilder<UIComponent>("ui");
		Factory.RegisterComponentBuilder<ButtonComponent>("button");
		Factory.RegisterComponentBuilder<MapChunkComponent>("map_chunk");

		/* - Utility Components - */
		Factory.RegisterComponentBuilder<WorldTimeComponent>("world_time");
		Factory.RegisterComponentBuilder<TimerComponent>("timer");

		//PostMaster::GetInstance().SendMessage({ eMessage::MultipleComponentBuildersCreated, componentBuilders });
	}

	void RegisterBlueprints()
	{
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_Enemy.json");
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_Environment.json");
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_UI.json");
	}

	void RegisterSystems(SystemManager& systemManager)
	{
		/* - Core Systems - */
		systemManager.Register<InputSystem>();
		systemManager.Register<MovementSystem>();
		systemManager.Register<CameraSystem>();

		systemManager.Register<CollisionSystem>();
		systemManager.Register<CombatSystem>();
		systemManager.Register<EnemySpawnSystem>();
		systemManager.Register<EquipmentSystem>();

		systemManager.Register<InventorySystem>();
		systemManager.Register<MeleeCombatSystem>();

		systemManager.Register<PlayerControllerSystem>();
		systemManager.Register<RangedCombatSystem>();

		systemManager.Register<ShakeSystem>();
		systemManager.Register<HUDSystem>();

		systemManager.Register<SpawnSystem>();
		systemManager.Register<SpriteAnimationSystem>();
		systemManager.Register<StatSystem>();
		systemManager.Register<TimeSystem>();

		systemManager.Register<SceneTransitionSystem>();

		/* - Map Systems - */
		systemManager.Register<MapGenerationSystem>();
		systemManager.Register<MapDecorationSystem>();

		/* -  UI Systems - */
		systemManager.Register<UISystem>();

		/* - AI Systems - */
		systemManager.Register<BlackboardSystem>();
		systemManager.Register<BehaviorTreeSystem>();
		systemManager.Register<SteeringBehaviorSystem>();
		systemManager.Register<StateMachineSystem>();

		/* - Render Systems - */
		systemManager.Register<DebugRenderSystem>();
		systemManager.Register<TextRenderSystem>();
		systemManager.Register<UIRenderSystem>();
		systemManager.Register<SpriteRenderSystem>();
		systemManager.Register<MapRenderSystem>();
	}

	void RegisterScenes(SceneManager& sceneManager, SystemManager& systemManager)
	{
		// Register game's scene here as well?
		
		SceneManagerProxy proxy{ sceneManager };

		sceneManager.Register<GameScene>(eScene::Game,			SharedContext{ proxy, systemManager });
		sceneManager.Register<LoadingScene>(eScene::Loading,	SharedContext{ proxy, systemManager });
		sceneManager.Register<MenuScene>(eScene::Menu,			SharedContext{ proxy, systemManager });
		sceneManager.Register<SettingsScene>(eScene::Settings,	SharedContext{ proxy, systemManager });
		sceneManager.Register<TitleScene>(eScene::Title,		SharedContext{ proxy, systemManager });
	}
}
