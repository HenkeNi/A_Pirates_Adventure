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
		Factory.RegisterComponentBuilder<AnimationComponent>("Animation");
		Factory.RegisterComponentBuilder<CameraComponent>("Camera");
		Factory.RegisterComponentBuilder<ColliderComponent>("Collider");
		Factory.RegisterComponentBuilder<CursorComponent>("Cursor");
		Factory.RegisterComponentBuilder<InputComponent>("Input");
		Factory.RegisterComponentBuilder<SpriteComponent>("Sprite");
		Factory.RegisterComponentBuilder<TransformComponent>("Transform");
		Factory.RegisterComponentBuilder<TextComponent>("Text");
		Factory.RegisterComponentBuilder<VelocityComponent>("Velocity");
		Factory.RegisterComponentBuilder<SubEntitiesComponent>("SubEntities");
		Factory.RegisterComponentBuilder<SceneTransitionComponent>("SceneTransition");
		Factory.RegisterComponentBuilder<PlayerControllerComponent>("PlayerController");

		/* - AI Components - */
		Factory.RegisterComponentBuilder<BlackboardComponent>("Blackboard");
		Factory.RegisterComponentBuilder<SteeringBehaviorComponent>("SteeringBehavior");
		Factory.RegisterComponentBuilder<WanderBehaviorComponent>("WanderBehavior");
		Factory.RegisterComponentBuilder<FlockBehaviorComponent>("FlockBehavior");
		Factory.RegisterComponentBuilder<SeekBehaviorComponent>("SeekBehavior");
		Factory.RegisterComponentBuilder<FleeBehaviorComponent>("FleeBehavior");
		Factory.RegisterComponentBuilder<StateMachineComponent>("StateMachine");
		Factory.RegisterComponentBuilder<BehaviorTreeComponent>("BehaviorTree");

		/* - Gameplay Components - */
		Factory.RegisterComponentBuilder<HealthComponent>("Health");
		Factory.RegisterComponentBuilder<WeaponComponent>("Weapon");
		Factory.RegisterComponentBuilder<ToppleComponent>("Topple");
		Factory.RegisterComponentBuilder<ShakeComponent>("Shake");
		Factory.RegisterComponentBuilder<HarvestableComponent>("Harvestable");
		Factory.RegisterComponentBuilder<EquipmentComponent>("Equipment");
		Factory.RegisterComponentBuilder<EquippableComponent>("Equippable");
		Factory.RegisterComponentBuilder<InventoryComponent>("Inventory");
		Factory.RegisterComponentBuilder<CollectableComponent>("Collectable");
		Factory.RegisterComponentBuilder<SpawnComponent>("Spawner");


		Factory.RegisterComponentBuilder<AttackComponent>("AttackCollider"); // RENAME!
		Factory.RegisterComponentBuilder<ProjectileComponent>("Projectile");
		Factory.RegisterComponentBuilder<ResourceComponent>("Resource");
		Factory.RegisterComponentBuilder<CharacterStateComponent>("CharacterState");
		Factory.RegisterComponentBuilder<KnockbackComponent>("Knockback");


		/* - UI Components - */
		Factory.RegisterComponentBuilder<HUDComponent>("HUD");
		Factory.RegisterComponentBuilder<UIComponent>("UI");
		Factory.RegisterComponentBuilder<ButtonComponent>("Button");
		Factory.RegisterComponentBuilder<WorldTimeComponent>("WorldTime");
		Factory.RegisterComponentBuilder<MapChunkComponent>("MapChunk");

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

		sceneManager.Register<GameScene>(eScene::Game,		  SharedContext{ proxy, systemManager });
		sceneManager.Register<LoadingScene>(eScene::Loading, SharedContext{ proxy, systemManager });
		sceneManager.Register<MenuScene>(eScene::Menu,		 SharedContext{ proxy, systemManager });
		sceneManager.Register<PauseScene>(eScene::Pause,	 SharedContext{ proxy, systemManager });
		sceneManager.Register<TitleScene>(eScene::Title,	 SharedContext{ proxy, systemManager });
	}
}
