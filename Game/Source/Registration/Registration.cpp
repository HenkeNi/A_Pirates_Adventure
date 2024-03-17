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
		Factory.RegisterComponentBuilder("Transform", new ConcreteComponentBuilder<TransformComponent>);
		// componentBuilders.push_back(std::make_pair("Transform",			new ConcreteComponentBuilder<TransformComponent>));

		std::vector<std::pair<std::string, ComponentBuilder*>> componentBuilders;

		/* - AI Components - */
		componentBuilders.push_back(std::make_pair("Blackboard",		new ConcreteComponentBuilder<BlackboardComponent>));
		componentBuilders.push_back(std::make_pair("SteeringBehavior",	new ConcreteComponentBuilder<SteeringBehaviorComponent>));
		componentBuilders.push_back(std::make_pair("WanderBehavior",	new ConcreteComponentBuilder<WanderBehaviorComponent>));
		componentBuilders.push_back(std::make_pair("FlockBehavior",		new ConcreteComponentBuilder<FlockBehaviorComponent>));
		componentBuilders.push_back(std::make_pair("SeekBehavior",		new ConcreteComponentBuilder<SeekBehaviorComponent>));
		componentBuilders.push_back(std::make_pair("FleeBehavior",		new ConcreteComponentBuilder<FleeBehaviorComponent>));
		componentBuilders.push_back(std::make_pair("StateMachine",		new ConcreteComponentBuilder<StateMachineComponent>));
		componentBuilders.push_back(std::make_pair("BehaviorTree",		new ConcreteComponentBuilder<BehaviorTreeComponent>));

		/* - Core Components - */
		componentBuilders.push_back(std::make_pair("Velocity",			new ConcreteComponentBuilder<VelocityComponent>));
		componentBuilders.push_back(std::make_pair("Sprite",			new ConcreteComponentBuilder<SpriteComponent>));
		componentBuilders.push_back(std::make_pair("Camera",			new ConcreteComponentBuilder<CameraComponent>));
		componentBuilders.push_back(std::make_pair("Input",				new ConcreteComponentBuilder<InputComponent>));
		componentBuilders.push_back(std::make_pair("Animation",			new ConcreteComponentBuilder<AnimationComponent>));
		componentBuilders.push_back(std::make_pair("Collider",			new ConcreteComponentBuilder<ColliderComponent>));
		componentBuilders.push_back(std::make_pair("Cursor",			new ConcreteComponentBuilder<CursorComponent>));
		componentBuilders.push_back(std::make_pair("Text",				new ConcreteComponentBuilder<TextComponent>));
		componentBuilders.push_back(std::make_pair("SubEntities",		new ConcreteComponentBuilder<SubEntitiesComponent>));
		componentBuilders.push_back(std::make_pair("SceneTransition",	new ConcreteComponentBuilder<SceneTransitionComponent>));
		componentBuilders.push_back(std::make_pair("PlayerController",	new ConcreteComponentBuilder<PlayerControllerComponent>));

		/* - Gameplay Components - */
		componentBuilders.push_back(std::make_pair("Health",			new ConcreteComponentBuilder<HealthComponent>));
		componentBuilders.push_back(std::make_pair("Weapon",			new ConcreteComponentBuilder<WeaponComponent>));
		componentBuilders.push_back(std::make_pair("Topple",			new ConcreteComponentBuilder<ToppleComponent>));
		componentBuilders.push_back(std::make_pair("Shake",				new ConcreteComponentBuilder<ShakeComponent>)); // Wooble? Shake AND Sway?
		componentBuilders.push_back(std::make_pair("Harvestable",		new ConcreteComponentBuilder<HarvestableComponent>));

		componentBuilders.push_back(std::make_pair("Equipment",			new ConcreteComponentBuilder<EquipmentComponent>));
		componentBuilders.push_back(std::make_pair("Equippable",		new ConcreteComponentBuilder<EquippableComponent>));
		componentBuilders.push_back(std::make_pair("Inventory",			new ConcreteComponentBuilder<InventoryComponent>));
		componentBuilders.push_back(std::make_pair("Collectable",		new ConcreteComponentBuilder<CollectableComponent>));
		componentBuilders.push_back(std::make_pair("Spawner",			new ConcreteComponentBuilder<SpawnComponent>));

		componentBuilders.push_back(std::make_pair("AttackCollider",	new ConcreteComponentBuilder<AttackComponent>));
		componentBuilders.push_back(std::make_pair("Projectile",		new ConcreteComponentBuilder<ProjectileComponent>));
		componentBuilders.push_back(std::make_pair("Resource",			new ConcreteComponentBuilder<ResourceComponent>));
		componentBuilders.push_back(std::make_pair("CharacterState",	new ConcreteComponentBuilder<CharacterStateComponent>));
		componentBuilders.push_back(std::make_pair("Knockback",			new ConcreteComponentBuilder<KnockbackComponent>));


		/* - UI Components - */
		componentBuilders.push_back(std::make_pair("HUD",				new ConcreteComponentBuilder<HUDComponent>));
		componentBuilders.push_back(std::make_pair("UI",				new ConcreteComponentBuilder<UIComponent>));
		componentBuilders.push_back(std::make_pair("Button",			new ConcreteComponentBuilder<ButtonComponent>));


		componentBuilders.push_back(std::make_pair("WorldTime",			new ConcreteComponentBuilder<WorldTimeComponent>));
		componentBuilders.push_back(std::make_pair("MapChunk",			new ConcreteComponentBuilder<MapChunkComponent>));


		PostMaster::GetInstance().SendMessage({ eMessage::MultipleComponentBuildersCreated, componentBuilders });
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
		systemManager.Register(std::make_unique<InputSystem>());
		systemManager.Register(std::make_unique<MovementSystem>());
		systemManager.Register(std::make_unique<CameraSystem>());


		systemManager.Register(std::make_unique<CollisionSystem>());
		systemManager.Register(std::make_unique<CombatSystem>());
		systemManager.Register(std::make_unique<EnemySpawnSystem>());
		systemManager.Register(std::make_unique<EquipmentSystem>());

		systemManager.Register(std::make_unique<InventorySystem>());
		systemManager.Register(std::make_unique<MeleeCombatSystem>());

		systemManager.Register(std::make_unique<PlayerControllerSystem>());
		systemManager.Register(std::make_unique<RangedCombatSystem>());

		systemManager.Register(std::make_unique<ShakeSystem>());
		systemManager.Register(std::make_unique<HUDSystem>());

		systemManager.Register(std::make_unique<SpawnSystem>());
		systemManager.Register(std::make_unique<SpriteAnimationSystem>());
		systemManager.Register(std::make_unique<StatSystem>());
		systemManager.Register(std::make_unique<TimeSystem>());

		systemManager.Register(std::make_unique<SceneTransitionSystem>());

		/* - Map Systems - */
		systemManager.Register(std::make_unique<MapGenerationSystem>());
		systemManager.Register(std::make_unique<MapDecorationSystem>());

		/* -  UI Systems - */
		systemManager.Register(std::make_unique<UISystem>());

		/* - AI Systems - */
		systemManager.Register(std::make_unique<BlackboardSystem>());
		systemManager.Register(std::make_unique<BehaviorTreeSystem>());
		systemManager.Register(std::make_unique<SteeringBehaviorSystem>());
		systemManager.Register(std::make_unique<StateMachineSystem>());

		/* - Render Systems - */
		systemManager.Register(std::make_unique<DebugRenderSystem>());
		systemManager.Register(std::make_unique<TextRenderSystem>());
		systemManager.Register(std::make_unique<UIRenderSystem>());
		systemManager.Register(std::make_unique<SpriteRenderSystem>());
		systemManager.Register(std::make_unique<MapRenderSystem>());
	}

	void RegisterScenes(SceneManager& sceneManager, SystemManager& systemManager)
	{
		SceneManagerProxy proxy{ sceneManager };

		sceneManager.Register(std::make_unique<GameScene>(SharedContext{ proxy, systemManager }), eScene::Game);	// Register game's scene here as well?
		sceneManager.Register(std::make_unique<LoadingScene>(SharedContext{ proxy, systemManager }), eScene::Loading);
		sceneManager.Register(std::make_unique<MenuScene>(SharedContext{ proxy, systemManager }), eScene::Menu);
		sceneManager.Register(std::make_unique<PauseScene>(SharedContext{ proxy, systemManager }), eScene::Pause);
		sceneManager.Register(std::make_unique<TitleScene>(SharedContext{ proxy, systemManager }), eScene::Title);
	}
}
