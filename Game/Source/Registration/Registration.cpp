#include "Pch.h"
#include "Registration.h"
#include "Scenes/Scenes.h"

//#include "Systems/Systems.h"
//#include <SceneTypes.h>
//#include "Components/Components.h"
//#include <../Scene/SceneManager.h>

#include "Systems/Systems.h"

#include "../Components/GameplayComponents.h"

namespace Registration
{
	void RegisterComponents()
	{

	//	/* - Core Components - */
	//	ecs.RegisterComponent<AnimationComponent>("Animation");
	//	ecs.RegisterComponent<BoundingBoxComponent>("BoundingBox");
	//	ecs.RegisterComponent<CameraComponent>("Camera");
	//	ecs.RegisterComponent<PhysicsComponent>("Physics");
	//	ecs.RegisterComponent<ColliderComponent>("Collider");
	//	ecs.RegisterComponent<CursorComponent>("Cursor"); // No need`? set in enigne?
	//	ecs.RegisterComponent<TextComponent>("Text");
	//	ecs.RegisterComponent<SubEntitiesComponent>("SubEntities");
	//	ecs.RegisterComponent<SceneTransitionComponent>("SceneTransition");
	//	ecs.RegisterComponent<PlayerControllerComponent>("PlayerController");

	//	/* - AI Components - */
	//	ecs.RegisterComponent<BlackboardComponent>("Blackboard");
	//	ecs.RegisterComponent<BehaviorTreeComponent>("BehaviorTree");
	//	//ecs.RegisterComponent<SteeringBehaviorComponent>("SteeringBehavior");
	//	//ecs.RegisterComponent<WanderBehaviorComponent>("WanderBehavior");
	//	//ecs.RegisterComponent<FlockBehaviorComponent>("FlockBehavior");
	//	//ecs.RegisterComponent<SeekBehaviorComponent>("SeekBehavior");
	//	//ecs.RegisterComponent<FleeBehaviorComponent>("FleeBehavior");
	//	// ecs.RegisterComponent<StateMachineComponent>("state_machine");
	//	//ecs.RegisterComponent<IdleComponent>("Idle");

	//	/* - Gameplay Components - */
	//	ecs.RegisterComponent<AttributesComponent>("Attribute");
	//	ecs.RegisterComponent<PersonalityComponent>("Personality");
	//	//ecs.RegisterComponent<FriendlyComponent>("Friendly");
	//	//ecs.RegisterComponent<HostileComponent>("Hostile");
	//	//ecs.RegisterComponent<CrewComponent>("Crew");
	//	ecs.RegisterComponent<HealthComponent>("Health");
	//	ecs.RegisterComponent<WeaponComponent>("Weapon");
	//	// ecs.RegisterComponent<ToppleComponent>("Topple");
	//	ecs.RegisterComponent<ShakeComponent>("Shake");
	//	ecs.RegisterComponent<HarvestableComponent>("Harvestable");
	//	ecs.RegisterComponent<EquipmentComponent>("Equipment");
	//	ecs.RegisterComponent<EquippableComponent>("Equippable");
	//	ecs.RegisterComponent<InventoryComponent>("Inventory");
	//	ecs.RegisterComponent<CollectableComponent>("Collectable");
	//	ecs.RegisterComponent<SpawnComponent>("Spawner");
	//	ecs.RegisterComponent<EnvironmentComponent>("Environment");

	//	ecs.RegisterComponent<AttackComponent>("Attack");
	//	ecs.RegisterComponent<AttackCooldownComponent>("AttackCooldown");
	//	ecs.RegisterComponent<ProjectileComponent>("Projectile");
	//	ecs.RegisterComponent<ResourceComponent>("Resource");
	//	ecs.RegisterComponent<StateComponent>("CharacterState");
	//	ecs.RegisterComponent<KnockbackComponent>("Knockback"); // remove?

	//	/* - UI Components - */
	//	ecs.RegisterComponent<HUDComponent>("HUD");
	//	ecs.RegisterComponent<UIComponent>("UI");
	//	ecs.RegisterComponent<ButtonComponent>("Button");
	//	ecs.RegisterComponent<MapChunkComponent>("MapChunk");
	//	ecs.RegisterComponent<GridComponent>("Grid");

	//	/* - Utility Components - */
	//	ecs.RegisterComponent<WorldTimeComponent>("WorldTime");

		/* - Core Components - */
		//ecs.RegisterComponent<TagComponent>("Tag");
		//ecs.RegisterComponent<AnimationComponent>("Animation");
		//ecs.RegisterComponent<BoundingBoxComponent>("BoundingBox");
		//ecs.RegisterComponent<CameraComponent>("Camera");
		//ecs.RegisterComponent<PhysicsComponent>("Physics");
		//ecs.RegisterComponent<ColliderComponent>("Collider");
		//ecs.RegisterComponent<CursorComponent>("Cursor"); // No need`? set in enigne?
		//ecs.RegisterComponent<InputComponent>("Input");
		//ecs.RegisterComponent<SpriteComponent>("Sprite");
		//ecs.RegisterComponent<TextComponent>("Text");
		//ecs.RegisterComponent<SubEntitiesComponent>("SubEntities");
		//ecs.RegisterComponent<SceneTransitionComponent>("SceneTransition");
		//ecs.RegisterComponent<PlayerControllerComponent>("PlayerController");

		/* - AI Components - */
		//ecs.RegisterComponent<BlackboardComponent>("Blackboard");
		//ecs.RegisterComponent<BehaviorTreeComponent>("BehaviorTree");
		//ecs.RegisterComponent<SteeringBehaviorComponent>("SteeringBehavior");
		//ecs.RegisterComponent<WanderBehaviorComponent>("WanderBehavior");
		//ecs.RegisterComponent<FlockBehaviorComponent>("FlockBehavior");
		//ecs.RegisterComponent<SeekBehaviorComponent>("SeekBehavior");
		//ecs.RegisterComponent<FleeBehaviorComponent>("FleeBehavior");
		// ecs.RegisterComponent<StateMachineComponent>("state_machine");
		//ecs.RegisterComponent<IdleComponent>("Idle");

		/* - Gameplay Components - */
		//ecs.RegisterComponent<CommandQueueComponent>("Commands");
		//ecs.RegisterComponent<AttributesComponent>("Attribute");
		//ecs.RegisterComponent<PersonalityComponent>("Personality");
		//ecs.RegisterComponent<FriendlyComponent>("Friendly");
		//ecs.RegisterComponent<HostileComponent>("Hostile");
		////ecs.RegisterComponent<CrewComponent>("Crew");
		//ecs.RegisterComponent<HealthComponent>("Health");
		//ecs.RegisterComponent<WeaponComponent>("Weapon");
		//// ecs.RegisterComponent<ToppleComponent>("Topple");
		//ecs.RegisterComponent<ShakeComponent>("Shake");
		//ecs.RegisterComponent<HarvestableComponent>("Harvestable");
		//ecs.RegisterComponent<EquipmentComponent>("Equipment");
		//ecs.RegisterComponent<EquippableComponent>("Equippable");
		//ecs.RegisterComponent<InventoryComponent>("Inventory");
		//ecs.RegisterComponent<CollectableComponent>("Collectable");
		//ecs.RegisterComponent<SpawnComponent>("Spawner");
		//ecs.RegisterComponent<EnvironmentComponent>("Environment");

		//ecs.RegisterComponent<AttackComponent>("Attack");
		//ecs.RegisterComponent<AttackCooldownComponent>("AttackCooldown");
		//ecs.RegisterComponent<ProjectileComponent>("Projectile");
		//ecs.RegisterComponent<ResourceComponent>("Resource");
		//ecs.RegisterComponent<StateComponent>("CharacterState");
		//ecs.RegisterComponent<KnockbackComponent>("Knockback"); // remove?

		///* - UI Components - */
		//ecs.RegisterComponent<HUDComponent>("HUD");
		//ecs.RegisterComponent<UIComponent>("UI");
		//ecs.RegisterComponent<ButtonComponent>("Button");
		//ecs.RegisterComponent<MapChunkComponent>("MapChunk");
		//ecs.RegisterComponent<GridComponent>("Grid");

		///* - Utility Components - */
		//ecs.RegisterComponent<WorldTimeComponent>("WorldTime");
		//ecs.RegisterComponent<TimerComponent>("Timer");
	}

//	void RegisterSystems(SceneManager& sceneManager)
//	{
//		Hi_Engine::EngineFacade::RegisterSystem<SceneTransitionSystem>("SceneTransitionSystem", sceneManager);
//
//		/* - Core Systems - */
////		ecs.RegisterSystem<CameraSystem>("CameraSystem");
////		ecs.RegisterSystem<CollisionSystem>("CollisionSystem");
////		ecs.RegisterSystem<PhysicsSystem>("PhysicsSystem");
////		ecs.RegisterSystem<AnimationSystem>("AnimationSystem");

////		ecs.RegisterSystem<TransformSystem>("TransformSystem");
////		ecs.RegisterSystem<PlayerControllerSystem>("PlayerControllerSystem");
////
////
////		/* - Gameplay Systems - */
////		ecs.RegisterSystem<CombatSystem>("CombatSystem");
////		ecs.RegisterSystem<EquipmentSystem>("EquipmentSystem");
////		ecs.RegisterSystem<InventorySystem>("InventorySystem");
// 
////		//ecs.RegisterSystem<EnemySpawnSystem>("EnemySpawnSystem");
////		ecs.RegisterSystem<ProjectileSystem>("ProjectileSystem");
////		ecs.RegisterSystem<ShakeSystem>("ShakeSystem");
////		ecs.RegisterSystem<TimeSystem>("TimeSystem");
////		ecs.RegisterSystem<SpawnSystem>("SpawnSystem");
////		ecs.RegisterSystem<CommandSystem>("CommandSystem");
////		//ecs.RegisterSystem<StatSystem>("StatSystem");
////
////		/* - Map Systems - */
////		ecs.RegisterSystem<MapSystem>("MapGenerationSystem");
////		ecs.RegisterSystem<MapDecorationSystem>("MapDecorationSystem");
////
////		/* -  UI Systems - */
////		ecs.RegisterSystem<UISystem>("UISystem");
////		ecs.RegisterSystem<HUDSystem>("HUDSystem");
////
////		/* - AI Systems - */
////		//ecs.RegisterSystem<BlackboardSystem>("BlackboardSystem");
////		//ecs.RegisterSystem<BehaviorTreeSystem>("BehaviorTreeSystem");
////		//ecs.RegisterSystem<SteeringBehaviorSystem>("SteeringBehaviorSystem");
////		//ecs.RegisterSystem<StateTransitionSystem>("StateTransitionSystem");
////	}

	void RegisterComponents(Hi_Engine::ComponentRegistryService& registry)
	{
		Hi_Engine::RegisterComponent<WorldTimeComponent>(registry, "WorldTimeComponent", 
			[](Hi_Engine::EntityHandle& handle, const Hi_Engine::Properties& properties)
			{
			});
	}

	void RegisterSystems(Hi_Engine::SystemRegistryService& registry)
	{
		Hi_Engine::RegisterSystem<WorldTimeSystem>(registry, "WorldTimeSystem");

		Hi_Engine::RegisterSystem<SceneTransitionSystem>(registry, "SceneTransitionSystem",
			[](Hi_Engine::World& world, Hi_Engine::ServiceRegistry& registry)
			{
				return std::make_unique<SceneTransitionSystem>(world, registry.Get<Hi_Engine::SceneService>(), registry.Get<Hi_Engine::EventService>()/*, registry.Get<Hi_Engine::SceneRegistryService>()*/);
			});

		Hi_Engine::RegisterSystem<MovementSystem>(registry, "MovementSystem");

		Hi_Engine::RegisterSystem<PlayerControllerSystem>(registry, "PlayerControllerSystem");

		Hi_Engine::RegisterSystem<CombatSystem>(registry, "CombatSystem");

		Hi_Engine::RegisterSystem<EquipmentSystem>(registry, "EquipmentSystem");

		Hi_Engine::RegisterSystem<InventorySystem>(registry, "InventorySystem");

		Hi_Engine::RegisterSystem<MapGenerationSystem>(registry, "MapGenerationSystem");
	}

	void RegisterScenes(Hi_Engine::SceneRegistryService& registry)
	{
		Hi_Engine::RegisterScene<TitleScene>(registry, "TitleScene", "../Assets/Scenes/Title.json");
		Hi_Engine::RegisterScene<GameScene>(registry, "GameScene", "../Assets/Scenes/Game.json"); // NOTE; overworld used here!
		Hi_Engine::RegisterScene<OverworldScene>(registry, "Overworld", "../Assets/Scenes/Overworld.json");

		//sceneManager->Register<LoadingScene>();
		//sceneManager->Register<MenuScene>();
		//sceneManager->Register<SettingsScene>();
		//sceneManager->Register<TitleScene>();

		//sceneManager.Init({ sceneManager.GetSceneID<TitleScene>() });
	}

	//static std::unordered_map<eScene, std::string> scenePaths
	//{
	//{ eScene::Inventory,	"../Game/Assets/Json/Scenes/Inventory.json"	},
	//{ eScene::Settings,		"../Game/Assets/Json/Scenes/Settings.json"	},
	//{ eScene::Menu,			"../Game/Assets/Json/Scenes/MainMenu.json"	},
	//{ eScene::Title,		"../Game/Assets/Json/Scenes/Title.json"		},
	//{ eScene::Overworld,	"../Game/Assets/Json/Scenes/Overworld.json"	}
	//};


	//void RegisterCallbacks(Hi_Engine::ECSRegistry& ecs)
	//{
	//	// how to pass scene type? Fetch sceentransition component? or entity?
	//	//Hi_Engine::CallbackRegistry::Callbacks.insert({ "scene_transition", [&](Hi_Engine::Entity entity) { PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, entity }); } }); // or register functio in engine faceade?
	//}
}
