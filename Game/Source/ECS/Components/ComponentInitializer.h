#pragma once
#include "Components.h"

#include <../Hi_Engine.h> //?

#include "../Entities/EntityBlueprint.h" // DON'T?

#include "../Commands/Move/MoveCommand.h"
#include "../Commands/Attack/AttackCommand.h"
#include "../Commands/Sprint/SprintCommand.h"
#include "../Commands/Pause/PauseCommand.h"
#include "../Commands/Aim/AimCommand.h"
#include "../Commands/Shoot/ShootCommand.h"
#include "../Commands/Inventory/OpenInventoryCommand.h"

#include "../AI/SteeringBehaviors/Flock/FlockBehavior.h"
// #include "../AI/SteeringBehaviors/Wander/WanderBehavior.h"


#include "AI/BehaviorTree/Action/ActionNodes.h"
#include "AI/BehaviorTree/Composite/CompositeNodes.h"
#include "AI/BehaviorTree/Condition/ConditionNodes.h"
#include "AI/BehaviorTree/Decorator/DecoratorNodes.h"
#include "AI/BehaviorTree/Service/ServiceNodes.h"
#include "AI/BehaviorTree/Base/BehaviorTreeNode.h"

namespace
{
	using ComponentData = std::unordered_map<std::string, std::any>;
}

class ComponentInitializer
{
public:
	template <typename T>
	static void InitializeComponent(T* component, const ComponentData& data)
	{
	}

	template <>
	static void InitializeComponent<AnimationComponent>(AnimationComponent* component, const ComponentData& data)
	{
		// TODO; engine classes Animation2D and Frame?

		// store animations in resource holder??

		std::unordered_map<std::string, Animation> animations;

		auto animationsData = std::any_cast<std::vector<std::any>>(data.at("animations"));
		for (const auto& animationData : animationsData) // rename Animation Frames instead?
		{
			auto properties = std::any_cast<std::unordered_map<std::string, std::any>>(animationData);

			std::string identifier = std::any_cast<std::string>(properties.at("identifier"));
			std::string textureName = std::any_cast<std::string>(properties.at("texture"));
			float frameDuration = std::any_cast<float>(properties.at("frame_duration"));
			bool isLooping = std::any_cast<bool>(properties.at("is_looping"));
			bool isPlaying = std::any_cast<bool>(properties.at("is_playing"));

			//std::vector<std::string> animationFrames;

			std::vector<Hi_Engine::Subtexture2D*> animationFrames;
			for (const auto& sprite : std::any_cast<std::vector<std::any>>(properties.at("subtexture_coordinates")))
			{
				auto s = std::any_cast<std::vector<std::any>>(sprite);
				int row = std::any_cast<int>(s[0]);
				int col = std::any_cast<int>(s[1]);
	
				// Have frame class? row and col to subtexture?

				//auto coords = std::any_cast<std::vector<int>>(sprite);
				auto* subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ textureName, row, col });
				animationFrames.push_back(subtexture);
			}
			// animation.Animations
			Animation animation;
			animation.Animations = animationFrames;
			animation.TotalFrames = (unsigned)animationFrames.size();
			animation.CurrentFrame = 0;
			animation.ElapsedFrameTime = 0.f;
			animation.FrameDuration = frameDuration;
			animation.IsLooping = isLooping;
			animation.IsPlaying = isPlaying;

			animations.insert_or_assign(identifier, animation); // just use insert?
		}


		// aComponent->Animations = std::any_cast<std::unordered_map<std::string, Animation>>(someData.at("animationMap"));
		component->Animations = animations;

		std::string active = std::any_cast<std::string>(data.at("active"));
		component->Active = active;

		/*std::string identifier				= std::any_cast<std::string>(someData.at("identifier"));
		std::vector<std::string> animations = std::any_cast<std::vector<std::string>>(someData.at("animations"));
		int frames							= std::any_cast<int>(someData.at("frames"));
		int startFrame						= std::any_cast<int>(someData.at("startFrame"));
		float frameDuration					= std::any_cast<float>(someData.at("frameDuration"));
		bool isLooping						= std::any_cast<bool>(someData.at("isLooping"));
		bool isPlaying						= std::any_cast<bool>(someData.at("isPlaying"));

		aComponent->m_identifier			= identifier;
		aComponent->m_animations			= animations;
		aComponent->m_totalFrames			= frames;
		aComponent->m_currentFrame			= startFrame;
		aComponent->m_frameDuration			= frameDuration;
		aComponent->m_elapsedFrameTime		= 0.f;
		aComponent->m_isLooping				= isLooping;
		aComponent->m_isPlaying				= isPlaying;*/
	}
	
	template <>
	static void InitializeComponent<AttackComponent>(AttackComponent* component, const ComponentData& data)
	{
		auto startPos = FVector2{ 0.f, 0.f };
		auto colliderSize = 0.2f;								// FIX!

		// Do in MovementSystem init?
		// aComponent->Offset = { 1.0f, 0.f };
		// aComponent->Collider.Init({ startPos.x - colliderSize, startPos.y - colliderSize }, { startPos.x + colliderSize, startPos.y + colliderSize });
	}

	template <>
	static void InitializeComponent<AttributesComponent>(AttributesComponent* component, const ComponentData& data)
	{
		int perception = std::any_cast<int>(data.at("perception"));

		component->Perception = perception;
	}

	template <>
	static void InitializeComponent<AudioComponent>(AudioComponent* component, const ComponentData& data)
	{
		std::string soundName = std::any_cast<std::string>(data.at("sound_name"));

		std::string trigger = std::any_cast<std::string>(data.at("trigger"));

		eMessage triggerType;

		if (trigger == "item_used")
		{
			triggerType = eMessage::ItemUsed;
		} 
		else if (trigger == "item_collected")
		{
			triggerType = eMessage::ItemCollected;
		}
		else if (trigger == "entity_destroyed")
		{
			triggerType = eMessage::EntityDestroyed;
		}
		else if (trigger == "button_activated")
		{
			triggerType = eMessage::ButtonActivated;
		}

		auto* audioSource = &Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource(soundName);

		Hi_Engine::Audio audio;
		audio.Init(audioSource);
		component->AudioTriggers.insert({ triggerType, audio });

		//component->Audio.Init(audioSource);
	}


	template <>
	static void InitializeComponent<BehaviorTreeComponent>(BehaviorTreeComponent* component, const ComponentData& data)
	{
		auto* behavior = new SelectorNode;


		auto* chaseSequence = new SequenceNode;
		chaseSequence->AddChild(new IsTargetSetNode);
		chaseSequence->AddChild(new IsTargetInSightNode);
		chaseSequence->AddChild(new InverterNode(new IsTargetReachedNode));
		chaseSequence->AddChild(new ChaseTargetNode);

		auto* setTarget = new SetTargetNode;

		auto* chaseBehavior = new SelectorNode;
		chaseBehavior->AddChild(chaseSequence);
		chaseBehavior->AddChild(setTarget);

		auto* wanderSequence = new SequenceNode;
		wanderSequence->AddChild(new IsDestinationSetNode);
		wanderSequence->AddChild(new InverterNode(new IsDestinationReachedNode));
		wanderSequence->AddChild(new MoveToDestinationNode);

		auto* setPosition = new SetWanderPosition;

		behavior->AddChild(chaseBehavior);
		behavior->AddChild(wanderSequence);
		behavior->AddChild(setPosition);

		component->RootNode = behavior;

		//auto* wanderBehavior = new SelectorNode;


		//wanderSequence->AddChild(new IsIdleNode);








		//auto* setPosition 

		// parallell node => in range OR position not set? => set position...



		//behavior->AddChild(wanderSequence);

		//auto* updateWanderPositionSequence = new SequenceNode;



		// Idle sequence
		//behavior->AddChild(new IdleNode);


		
		
		
		//rootNode->AddChild(new MoveToNode);
		//rootNode->AddChild(new IdleNode);



		// Sequence => PAtrol > idle...

		// Selector; Alert Patrol Idle?



		// rootNode->AddChild(new IdleNode);

		// rootNode->

		//component->RootNode = new SequenceNode;

		//component->RootNode

		// selector


		// Idle Patrol Alert  Chase Flee Attack 






		// DO IN system instead??
		// aComponent->m_rootNode = new SelectorNode;

		// auto attackSequence = new SequenceNode;
		//attackSequence->AddChild(new TargetInRange)
	}

	template <>
	static void InitializeComponent<ButtonComponent>(ButtonComponent* component, const ComponentData& data)
	{
		// std::string identifier = std::any_cast<std::string>(data.at("identifier"));

		// TODO; improve! use SceneTransition component instead?
		/*if (identifier == "play_button")
		{
			component->OnClick = []() {
				PostMaster::GetInstance().SendMessage({ eMessage::PopScene, eScene::Menu });
				};
		}*/


		// component->Identifier = type;
	}

	template <>
	static void InitializeComponent<CameraComponent>(CameraComponent* component, const ComponentData& data)
	{
		component->ZoomRange = { 0.5f, 1.f };

		// aComponent->Camera.Init(0, 1400, 0, 800, 0.f, 100.f);

	}
	
	template <>
	static void InitializeComponent<CharacterStateComponent>(CharacterStateComponent* component, const ComponentData& data)
	{
		component->IsIdle = true;
		component->IsAlive = true;
		component->IsWalking = false;
		component->IsRunning = false;
		component->IsAttacking = false;
		component->IsAiming = false;
	}

	template <>
	static void InitializeComponent<ColliderComponent>(ColliderComponent* component, const ComponentData& data)
	{
		FVector2 position = { 0.f, 0.f };

		auto size = std::any_cast<std::vector<std::any>>(data.at("size"));

		//auto halfSize = std::any_cast<float>(someData.at("half_size"));
		// float halfSize = 0.5f;
		float xSize = std::any_cast<float>(size[0]);
		float ySize = std::any_cast<float>(size[1]);

		component->Collider.Init({ position.x - xSize, position.y - ySize }, { position.x + xSize, position.y + ySize });

		std::string type = std::any_cast<std::string>(data.at("type"));
		if (type == "trigger")
		{
			component->Type = eColliderType::Trigger;
		}
		else if (type == "dynamic")
		{
			component->Type = eColliderType::Dynamic;
		}


		if (data.contains("offset"))
		{
			auto offsetData = std::any_cast<std::unordered_map<std::string, std::any>>(data.at("offset"));

			Offset& offset = component->Offset;

			offset.XOffset = std::any_cast<float>(offsetData.at("xOffset"));
			offset.YOffset = std::any_cast<float>(offsetData.at("yOffset"));
			offset.IsDirectionallyBound = std::any_cast<bool>(offsetData.at("isDirectionallyBound"));
		}

	}

	template <>
	static void InitializeComponent<EnvironmentComponent>(EnvironmentComponent* component, const ComponentData& data)
	{
		auto types = std::any_cast<std::vector<std::any>>(data.at("tiles"));
		
		for (const auto& type : types)
		{
			if (std::any_cast<std::string>(type) == "grass")
			{
				//component->AcceptableTileTypes.push_back(eTile::Grass);

			}
			else if (std::any_cast<std::string>(type) == "sand")
			{
				//component->AcceptableTileTypes.push_back(eTile::Sand);
			}
		}

	}
	
	template <>
	static void InitializeComponent<HarvestableComponent>(HarvestableComponent* component, const ComponentData& data)
	{
		std::string resourceType = std::any_cast<std::string>(data.at("resource_type"));
		int yield = std::any_cast<int>(data.at("yield"));

		component->Yield = yield;
		component->ResourceType = resourceType;
	}

	template <>
	static void InitializeComponent<HealthComponent>(HealthComponent* component, const ComponentData& data)
	{
		int value = std::any_cast<int>(data.at("value"));
		component->CurrentValue = value;
		component->IsInvincible = false;
		// TODO; set health stat?!
	}

	template <>
	static void InitializeComponent<InventoryComponent>(InventoryComponent* component, const ComponentData& data)
	{
		int xx = 20;
		xx += 20;
	}
	
	template <>
	static void InitializeComponent<MapChunkComponent>(MapChunkComponent* component, const ComponentData& data)
	{
		//int width = std::any_cast<int>(data.at("width"));
		//int height = std::any_cast<int>(data.at("height"));

		// MapChunkComponent::TileCountPerSide = width;

		//aComponent->Width = width;
		//aComponent->Height = height;
	}

	template <>
	static void InitializeComponent<PlayerControllerComponent>(PlayerControllerComponent* component, const ComponentData& data)
	{
		// Temp

		// USe builder/factory?

		// Pass in Entity??

		// Have an map of keys, one with mouse input and one with controller input??
		
		// TODO; make sure to delete...
		component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_W, new MoveCommand{{ 0.f,   1.f }}));
		component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_S, new MoveCommand{{ 0.f,	-1.f } }));
		component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_A, new MoveCommand{{ -1.f,	 0.f } }));
		component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_D, new MoveCommand{{ 1.f,  0.f } }));

		component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_Space,	new AttackCommand));
		component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_LShift,	new SprintCommand));
		component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_Escape,	new PauseCommand));
		component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_I,		new OpenInventoryCommand));
		component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_1,		new AimCommand)); // CHANGE To mouse button
		component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_2,		new ShootCommand));
	}

	template <>
	static void InitializeComponent<SpawnComponent>(SpawnComponent* component, const ComponentData& data)
	{
		std::string spawned	= std::any_cast<std::string>(data.at("spawned"));
		int amount			= std::any_cast<int>(data.at("amount"));
		float interval		= std::any_cast<float>(data.at("interval"));

		component->Spawned	= spawned;
		component->Amount	= amount;
		component->Interval	= interval;
		component->ElapsedTime = 0.f;
		component->SpawnedAmount = 0;
	}

	template <>
	static void InitializeComponent<SpriteComponent>(SpriteComponent* component, const ComponentData& data)
	{
		auto shader = std::any_cast<std::string>(data.at("shader"));
		auto texture = std::any_cast<std::string>(data.at("texture"));
		//auto color = std::any_cast<std::array<float, 4>>(data.at("color"));
		auto color = std::any_cast<std::vector<std::any>>(data.at("color"));
		auto coordinates = std::any_cast<std::vector<std::any>>(data.at("coordinates"));

		component->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ texture, std::any_cast<int>(coordinates[0]), std::any_cast<int>(coordinates[1]) });
		component->Color = { std::any_cast<float>(color[0]), std::any_cast<float>(color[1]), std::any_cast<float>(color[2]), std::any_cast<float>(color[3]) };
		//aComponent->m_material = {
		//	&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(texture),
		//	&Hi_Engine::ResourceHolder<Hi_Engine::GLSLShader>::GetInstance().GetResource(shader)
		//};

		// aComponent->m_material.SetColor({ color[0], color[1], color[2], color[3] });
	}

	template <>
	static void InitializeComponent<SteeringBehaviorComponent>(SteeringBehaviorComponent* component, const ComponentData& data)
	{
		std::string behaviorType = std::any_cast<std::string>(data.at("behavior"));
		std::string layer = std::any_cast<std::string>(data.at("layer"));

		if (behaviorType == "flock_behavior")
		{
			component->ActiveBehavior = new FlockBehavior{};	// FIX! don't new? Make sure to delete...
			component->Layer = layer;
		}
		if (behaviorType == "wander_behavior")
		{
			// component->ActiveBehavior = new WanderBehavior{};
			component->Layer = layer;
		}
	}

	template <>
	static void InitializeComponent<TransformComponent>(TransformComponent* component, const ComponentData& data)
	{
		//auto position = std::any_cast<std::array<float, 3>>(someData.at("position"));
		//auto scale = std::any_cast<std::array<float, 3>>(someData.at("scale"));
		
		auto position  = std::any_cast<std::vector<std::any>>(data.at("position"));
		auto scale     = std::any_cast<std::vector<std::any>>(data.at("scale"));
		auto pivot	   = std::any_cast<std::vector<std::any>>(data.at("pivot"));
		float rotation = std::any_cast<float>(data.at("rotation"));



		component->CurrentPos	= component->PreviousPos = { std::any_cast<float>(position[0]), std::any_cast<float>(position[1]) };
		component->Scale		= { std::any_cast<float>(scale[0]), std::any_cast<float>(scale[1]) };
		component->Pivot		= { std::any_cast<float>(pivot[0]), std::any_cast<float>(pivot[1]) };
		component->Rotation	= rotation;
	}

	template <>
	static void InitializeComponent<TextComponent>(TextComponent* component, const ComponentData& data)
	{
		std::string font	= std::any_cast<std::string>(data.at("font"));
		int size			= std::any_cast<int>(data.at("size"));
		//auto color			= std::any_cast<std::array<float, 4>>(data.at("color"));
		auto color = std::any_cast<std::vector<std::any>>(data.at("color"));
		std::string text = std::any_cast<std::string>(data.at("text"));

		std::string alignment = std::any_cast<std::string>(data.at("alignment"));
		
		component->Font = &Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().GetResource(font);
		component->Color = { std::any_cast<float>(color[0]), std::any_cast<float>(color[1]), std::any_cast<float>(color[2]), std::any_cast<float>(color[3]) };
		component->Size = size;
		component->Text = text;

		if (alignment == "center")
		{
			component->Alignment = Hi_Engine::eTextAlginment::Align_Center;
		}
		else if (alignment == "left")
		{
			component->Alignment = Hi_Engine::eTextAlginment::Align_Left;
		}
		else if (alignment == "right")
		{ 
			component->Alignment = Hi_Engine::eTextAlginment::Align_Right;
		}
	}

	template <>
	static void InitializeComponent<ResourceComponent>(ResourceComponent* component, const ComponentData& data)
	{
		std::string resource = std::any_cast<std::string>(data.at("resource"));
		//int quantity = std::any_cast<int>(data.at("quantity"));

		//component->m_quantity			= (unsigned)quantity;
		component->ResourceType = resource;
	}
	
	template <>
	static void InitializeComponent<VelocityComponent>(VelocityComponent* component, const ComponentData& data)
	{
		float speed = std::any_cast<float>(data.at("speed"));
		component->Speed = speed;
	}

	template <>
	static void InitializeComponent<WeaponComponent>(WeaponComponent* component, const ComponentData& data)
	{
		int damage = std::any_cast<int>(data.at("damage"));
		float speed = std::any_cast<float>(data.at("speed"));

		component->DamageDealt = damage;
		component->AttackSpeed = speed;
	}
	
	template <>
	static void InitializeComponent<WorldTimeComponent>(WorldTimeComponent* component, const ComponentData& data)
	{
		float dayDuration = std::any_cast<float>(data.at("day_duration"));

		// TOOD; fix
		component->TimeOfDayDurations.insert(std::make_pair(eTimeOfDay::Dawn,	Hi_Engine::Range{ 0.f, 0.1f }));
		component->TimeOfDayDurations.insert(std::make_pair(eTimeOfDay::Day,	Hi_Engine::Range{ 1.01f, 0.6f }));
		component->TimeOfDayDurations.insert(std::make_pair(eTimeOfDay::Dusk,	Hi_Engine::Range{ 0.61f, 0.8f }));
		component->TimeOfDayDurations.insert(std::make_pair(eTimeOfDay::Night,  Hi_Engine::Range{ 0.81f, 1.0f }));

		component->DayDuration = dayDuration;
	}

	template <>
	static void InitializeComponent<WanderBehaviorComponent>(WanderBehaviorComponent* component, const ComponentData& data)
	{
		// component->Behavior = new WanderBehavior{}; // Don't new....
		//component->Behavior = new WanderBehavior{}; // Don't new....
	}

	template <>
	static void InitializeComponent<PersonalityComponent>(PersonalityComponent* component, const ComponentData& data)
	{
		bool isAggressive = std::any_cast<bool>(data.at("IsAggressive"));

		component->IsAggressive = isAggressive;
	}

	template <>
	static void InitializeComponent<FlockBehaviorComponent>(FlockBehaviorComponent* component, const ComponentData& data)
	{
		component->Behavior = new FlockBehavior{};	// Make sure to delete...
	}

	template <>
	static void InitializeComponent<SeekBehaviorComponent>(SeekBehaviorComponent* component, const ComponentData& data)
	{
		// component->m_behavior = new SeekBehavior{}; // Don't new....
	}

	template <>
	static void InitializeComponent<FleeBehaviorComponent>(FleeBehaviorComponent* component, const ComponentData& data)
	{
		// component->m_behavior = new FleeBehavior{}; // Don't new....

	}

	//template <>
	//static void InitializeComponent<StateMachineComponent>(StateMachineComponent* component, const ECS::ComponentData& data)
	//{
	//	//auto states = std::any_cast<std::vector<std::any>>(someData.at("states"));
	//	//auto states = someData.at("states");

	//	auto states = std::any_cast<std::vector<std::any>>(data.at("states"));

	//	//std::vector<std::string> states = std::any_cast<std::vector<std::string>>(someData.at("states"));

	//	// Fetch state machine from factory??
	//	for (const auto& state : states)
	//	{
	//		std::string type = std::any_cast<std::string>(state);

	//		if (type == "idle")
	//		{
	//			component->States.push_back(new IdleState{});
	//		}
	//		else if (type == "walk")
	//		{
	//			component->States.push_back(new WalkState{});
	//		}
	//		else if (type == "attack")
	//		{
	//			component->States.push_back(new AttackState{});
	//		}
	//		else if (type == "flee")
	//		{ }
	//		else if (type == "death")
	//		{ }
	//	}

	//	// Temp
	//	component->ActiveState = component->States[0];


	//	// std::unorederd_map? string key ? 


	//	// TEmp
	//	// add durtaion condition
	//	Transition idleToWalk;
	//	idleToWalk.SetCondition(new ElapsedTimeCondition{ 5.f });
	//	idleToWalk.SetTargetState(component->States[1]);

	//	Transition walkToIdle;
	//	walkToIdle.SetCondition(new ElapsedTimeCondition{ 5.f }); // use same condition? => cant delte in desturtor then....
	//	walkToIdle.SetTargetState(component->States[0]);

	//	Transition walkToAttack;
	//	walkToAttack.SetCondition(new InRangeCondition{ 20.f });
	//	walkToAttack.SetTargetState(component->States[2]);

	//	Transition attackToIdle;
	//	attackToIdle.SetCondition(new HasAttackedCondition{});
	//	attackToIdle.SetTargetState(component->States[0]);

	//	component->States[0]->AddTransition(idleToWalk);
	//	component->States[1]->AddTransition(walkToIdle); // duraion condition
	//	component->States[1]->AddTransition(walkToAttack);
	//	component->States[2]->AddTransition(attackToIdle);

	//	// TODO; connect the states
	//	// set start time in condition	


	//	
	//	// add duration condition to idle state.... and duration condition to walk state...



	//	// unoredred map? string, state?
	//	// c

	//}

	template <>
	static void InitializeComponent<ShakeComponent>(ShakeComponent* component, const ComponentData& data)
	{
	}
	
	template <>
	static void InitializeComponent<ToppleComponent>(ToppleComponent* component, const ComponentData& data)
	{
	}

	template <>
	static void InitializeComponent<SceneTransitionComponent>(SceneTransitionComponent* component, const ComponentData& data)
	{
		if (!data.contains("scene"))
			return;

		std::string scene = std::any_cast<std::string>(data.at("scene"));

		component->ShouldPush = !std::any_cast<bool>(data.at("should_remove"));

		if (scene == "game")
			component->SceneType = eScene::Game;
		else if (scene == "menu")
			component->SceneType = eScene::Menu;
		else if (scene == "title")
			component->SceneType = eScene::Title;
		else if (scene == "settings")
			component->SceneType = eScene::Settings;
		else if (scene == "inventory")
			component->SceneType = eScene::Inventory;
	}

	template <>
	static void InitializeComponent<TimerComponent>(TimerComponent* component, const ComponentData& data)
	{
		float duration = std::any_cast<float>(data.at("duration"));
		component->Duration = duration;
	}

	template <>
	static void InitializeComponent<UIComponent>(UIComponent* component, const ComponentData& data)
	{
		if (data.contains("render_depth"))
			component->RenderDepth = std::any_cast<int>(data.at("render_depth"));
	}
};