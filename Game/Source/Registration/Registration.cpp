#include "Pch.h"
#include "Registration.h"
#include "SystemManager.h"
#include "Systems.h"
#include "Scenes.h"
#include "Components.h"


namespace Registration
{
	void RegisterComponents()
	{
		EntityManager::s_entityFactory.RegisterComponentBuilder("Sprite",			new ConcreteComponentBuilder<SpriteComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Transform",		new ConcreteComponentBuilder<TransformComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Input",			new ConcreteComponentBuilder<InputComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Animation",		new ConcreteComponentBuilder<AnimationComponent>());

		EntityManager::s_entityFactory.RegisterComponentBuilder("PlayerController", new ConcreteComponentBuilder<PlayerControllerComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Velocity",			new ConcreteComponentBuilder<VelocityComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Weapon",			new ConcreteComponentBuilder<WeaponComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Health",			new ConcreteComponentBuilder<HealthComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Camera",			new ConcreteComponentBuilder<CameraComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Rect",				new ConcreteComponentBuilder<RectComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("AttackCollider",	new ConcreteComponentBuilder<AttackColliderComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Hitbox",			new ConcreteComponentBuilder<HitboxColliderComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Harvestable",		new ConcreteComponentBuilder<HarvestableComponent>());

		EntityManager::s_entityFactory.RegisterComponentBuilder("Resource",			new ConcreteComponentBuilder<ResourceComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Pickup",			new ConcreteComponentBuilder<PickupColliderComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Inventory",		new ConcreteComponentBuilder<InventoryComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("Spawner",			new ConcreteComponentBuilder<SpawnComponent>());
		EntityManager::s_entityFactory.RegisterComponentBuilder("BehaviorTree",		new ConcreteComponentBuilder<BehaviorTreeComponent>());

		EntityManager::s_entityFactory.RegisterComponentBuilder("MapChunk",			new ConcreteComponentBuilder<MapChunkComponent>());
	}

	void RegisterBlueprints()
	{
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_Enemy.json");
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_Environment.json");
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_UI.json");
	}

	void RegisterSystems(SystemManager& aSystemManager)
	{
		aSystemManager.Register(std::make_unique<BehaviorTreeSystem>());
		aSystemManager.Register(std::make_unique<CameraSystem>());
		aSystemManager.Register(std::make_unique<CollisionSystem>());
		aSystemManager.Register(std::make_unique<CombatSystem>());
		aSystemManager.Register(std::make_unique<EnemySpawnSystem>());
		aSystemManager.Register(std::make_unique<EquipmentSystem>());
		aSystemManager.Register(std::make_unique<InputSystem>());

		aSystemManager.Register(std::make_unique<InventorySystem>());
		aSystemManager.Register(std::make_unique<MeleeCombatSystem>());
		aSystemManager.Register(std::make_unique<MovementSystem>());

		aSystemManager.Register(std::make_unique<PlayerControllerSystem>());
		aSystemManager.Register(std::make_unique<RangedCombatSystem>());
		aSystemManager.Register(std::make_unique<ResourceDropSystem>());

		aSystemManager.Register(std::make_unique<SpawnSystem>());
		aSystemManager.Register(std::make_unique<SpriteAnimationSystem>());
		aSystemManager.Register(std::make_unique<SpriteRenderSystem>());
		aSystemManager.Register(std::make_unique<StatSystem>());
		aSystemManager.Register(std::make_unique<PrimitiveRenderSystem>());

		aSystemManager.Register(std::make_unique<MapRenderSystem>());
		aSystemManager.Register(std::make_unique<MapGenerationSystem>());
		aSystemManager.Register(std::make_unique<MapDecorationSystem>());
	}

	void RegisterScenes(SceneManager& aSceneManager, SystemManager& aSystemManager)
	{
		SceneManagerProxy proxy{ aSceneManager };

		aSceneManager.Register(std::make_unique<GameScene>	 (SharedContext{ proxy, aSystemManager }), eScene::Game);	// Register game's scene here as well?
		aSceneManager.Register(std::make_unique<LoadingScene>(SharedContext{ proxy, aSystemManager }), eScene::Loading);
		aSceneManager.Register(std::make_unique<MenuScene>   (SharedContext{ proxy, aSystemManager }), eScene::Menu);
		aSceneManager.Register(std::make_unique<PauseScene>  (SharedContext{ proxy, aSystemManager }), eScene::Pause);
		aSceneManager.Register(std::make_unique<TitleScene>  (SharedContext{ proxy, aSystemManager }), eScene::Title);
	}
}
