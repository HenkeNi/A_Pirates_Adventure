#include "Pch.h"
#include "Registration.h"
#include "Scenes/Title/TitleScene.h"


//#include "Systems/Systems.h"
#include "Scenes/Scenes.h"
//#include <SceneTypes.h>
//#include "Components/Components.h"

//#include <../Scene/SceneManager.h>

#include "Systems/SceneTransitionSystem.h"
#include "Systems/WorldTimeSystem.h"


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
////		ecs.RegisterSystem<InputSystem>("InputSystem");
////		ecs.RegisterSystem<MovementSystem>("MovementSystem");
////		ecs.RegisterSystem<CameraSystem>("CameraSystem");
////		ecs.RegisterSystem<CollisionSystem>("CollisionSystem");
////		ecs.RegisterSystem<PhysicsSystem>("PhysicsSystem");
////		ecs.RegisterSystem<PlayerControllerSystem>("PlayerControllerSystem");
////		ecs.RegisterSystem<SceneTransitionSystem>("SceneTransitionSystem");
////		ecs.RegisterSystem<AnimationSystem>("AnimationSystem");
////
////		ecs.RegisterSystem<TransformSystem>("TransformSystem");
////
////		/* - Gameplay Systems - */
////		ecs.RegisterSystem<CombatSystem>("CombatSystem");
////		//ecs.RegisterSystem<EnemySpawnSystem>("EnemySpawnSystem");
////		ecs.RegisterSystem<EquipmentSystem>("EquipmentSystem");
////		ecs.RegisterSystem<InventorySystem>("InventorySystem");
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
////#if DEBUG
////
////		ecs.RegisterSystem<EditorSystem>("EditorSystem");
////
////#endif // DEBUG
////
////
////		/* - AI Systems - */
////		//ecs.RegisterSystem<BlackboardSystem>("BlackboardSystem");
////		//ecs.RegisterSystem<BehaviorTreeSystem>("BehaviorTreeSystem");
////		//ecs.RegisterSystem<SteeringBehaviorSystem>("SteeringBehaviorSystem");
////		//ecs.RegisterSystem<StateTransitionSystem>("StateTransitionSystem");
////
////		/* - Audio System - */
////		ecs.RegisterSystem<AudioSystem>("AudioSystem");
////
////		/* - Render Systems - */
////		ecs.RegisterSystem<RenderSystem>("RenderSystem");
//	}

	void RegisterSystems(Hi_Engine::SystemRegistry& registry)
	{
		Hi_Engine::RegisterSystem<WorldTimeSystem>(registry, "WorldTimeSystem");
		Hi_Engine::RegisterSystem<SceneTransitionSystem>(registry, "SceneTransitionSystem",
			[](Hi_Engine::World& world, Hi_Engine::ServiceRegistry& registry)
			{
				return std::make_unique<SceneTransitionSystem>(world, registry.Get<Hi_Engine::SceneManager>());
			});
	}

	void RegisterScenes(Hi_Engine::SceneRegistry& registry)
	{
		Hi_Engine::RegisterScene<TitleScene>(registry, "TitleScene", "../Game/Assets/Json/Scenes/Title.json");
		
		//registry.Register<TitleScene>("TitleScene");

		// sceneManager.Emplace<TitleScene>("TitleScene");
		// Register game's scene here as well?
	
		//sceneManager->Register<GameScene>();
		//sceneManager->Register<LoadingScene>();
		//sceneManager->Register<MenuScene>();
		//sceneManager->Register<SettingsScene>();
		//sceneManager->Register<TitleScene>();

		//sceneManager.Init({ sceneManager.GetSceneID<TitleScene>() });
	}

	//static std::unordered_map<eScene, std::string> scenePaths
//{
//	//{ eScene::Inventory,	"../Game/Assets/Json/Scenes/Inventory.json"	},
//	//{ eScene::Settings,		"../Game/Assets/Json/Scenes/Settings.json"	},
//	//{ eScene::Menu,			"../Game/Assets/Json/Scenes/MainMenu.json"	},
//	//{ eScene::Title,		"../Game/Assets/Json/Scenes/Title.json"		},
//	//{ eScene::Overworld,	"../Game/Assets/Json/Scenes/Overworld.json"	}
//};


	//void RegisterCallbacks(Hi_Engine::ECSRegistry& ecs)
	//{
	//	// how to pass scene type? Fetch sceentransition component? or entity?
	//	//Hi_Engine::CallbackRegistry::Callbacks.insert({ "scene_transition", [&](Hi_Engine::Entity entity) { PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, entity }); } }); // or register functio in engine faceade?
	//}
}
