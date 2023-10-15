#pragma once
#include "Components.h"
#include <Core/Resources/ResourceHolder.hpp>

#include "../Blueprints/EntityBlueprint.h" // DON'T?

#include "../Commands/Move/MoveCommand.h"
#include "../Commands/Attack/AttackCommand.h"
#include "../Commands/Sprint/SprintCommand.h"

#include "../AI/SteeringBehaviors/Flock/FlockBehavior.h"
#include "../AI/SteeringBehaviors/Wander/WanderBehavior.h"

#include "../AI/StateMachine/States/Idle/IdleState.h"
#include "../AI/StateMachine/States/Walk/WalkState.h"

#include "../AI/StateMachine/Conditions/Time/TimeConditions.h"


// struct ComponentData;

class ComponentInitializer
{
public:
	// using ComponentData = std::unordered_map<std::string, std::any>;

	template <typename T>
	static void InitializeComponent(T* aComponent, const ComponentData& someData) 
	{
	}

	template <>
	static void InitializeComponent<AnimationComponent>(AnimationComponent* aComponent, const ComponentData& someData)
	{
		aComponent->Animations = std::any_cast<std::unordered_map<std::string, Animation>>(someData.at("animationMap"));
		aComponent->Active = std::any_cast<std::string>(someData.at("active"));

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
	static void InitializeComponent<AttackComponent>(AttackComponent* aComponent, const ComponentData& someData)
	{
		auto startPos = CU::Vector3<float>{ 0.f, 0.f, 0.f };
		auto colliderSize = 0.2f;								// FIX!

		// Do in MovementSystem init?
		aComponent->Offset = { 1.0f, 0.f, 0.f };
		aComponent->Collider.Init({ startPos.x - colliderSize, startPos.y - colliderSize }, { startPos.x + colliderSize, startPos.y + colliderSize });
	}

	template <>
	static void InitializeComponent<BehaviorTreeComponent>(BehaviorTreeComponent* aComponent, const ComponentData& someData)
	{
		// DO IN system instead??
		// aComponent->m_rootNode = new SelectorNode;

		// auto attackSequence = new SequenceNode;
		//attackSequence->AddChild(new TargetInRange)
	}

	template <>
	static void InitializeComponent<CameraComponent>(CameraComponent* aComponent, const ComponentData& someData)
	{
		int xx = 20;
		xx += 20;
	}
	
	template <>
	static void InitializeComponent<CharacterStateComponent>(CharacterStateComponent* aComponent, const ComponentData& someData)
	{
		aComponent->IsIdle = true;
		aComponent->IsAlive = true;
		aComponent->IsWalking = false;
		aComponent->IsRunning = false;
		aComponent->IsJumping = false;
		aComponent->IsAttacking = false;
	}

	template <>
	static void InitializeComponent<DebugRectComponent>(DebugRectComponent* aComponent, const ComponentData& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));

		aComponent->Shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader);
		aComponent->Color = { 1.f, 1.f, 1.f, 1.f }; // TODO; read from json..
	}

	template <>
	static void InitializeComponent<HarvestableComponent>(HarvestableComponent* aComponent, const ComponentData& someData)
	{
		std::string resourceType = std::any_cast<std::string>(someData.at("resource_type"));
		int yield = std::any_cast<int>(someData.at("yield"));

		aComponent->Yield = yield;
		aComponent->ResourceType = resourceType;
	}

	template <>
	static void InitializeComponent<HealthComponent>(HealthComponent* aComponent, const ComponentData& someData)
	{
		int value = std::any_cast<int>(someData.at("value"));
		aComponent->CurrentValue = value;

		// TODO; set health stat?!
	}

	template <>
	static void InitializeComponent<HitboxComponent>(HitboxComponent* aComponent, const ComponentData& someData)
	{
		CU::Vector3<float> position = { 0.f, 0.f, 0.f };
		auto halfSize = std::any_cast<float>(someData.at("halfSize"));
		bool isStatic = std::any_cast<bool>(someData.at("isStatic"));

		aComponent->Collider.Init({ position.x - halfSize, position.z - halfSize }, { position.x + halfSize, position.y + halfSize });
		aComponent->IsStatic = isStatic;
	}

	template <>
	static void InitializeComponent<InventoryComponent>(InventoryComponent* aComponent, const ComponentData& someData)
	{
		int xx = 20;
		xx += 20;
	}
	
	template <>
	static void InitializeComponent<MapChunkComponent>(MapChunkComponent* aComponent, const ComponentData& someData)
	{
		int width = std::any_cast<int>(someData.at("width"));
		int height = std::any_cast<int>(someData.at("height"));

		aComponent->Width = width;
		aComponent->Height = height;
	}

	template <>
	static void InitializeComponent<PlayerControllerComponent>(PlayerControllerComponent* aComponent, const ComponentData& someData)
	{
		// Temp

		// USe builder/factory?

		// Pass in Entity??
		
		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_W, new MoveCommand{{ 0.f,   -1.f }}));
		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_S, new MoveCommand{{ 0.f,	 1.f } }));
		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_A, new MoveCommand{{ -1.f,	 0.f } }));
		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_D, new MoveCommand{{ 1.f,  0.f } }));

		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_Space, new AttackCommand));
		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_Shift, new SprintCommand));
	}

	template <>
	static void InitializeComponent<SpawnComponent>(SpawnComponent* aComponent, const ComponentData& someData)
	{
		std::string spawned	= std::any_cast<std::string>(someData.at("spawned"));
		int amount			= std::any_cast<int>(someData.at("amount"));
		float interval		= std::any_cast<float>(someData.at("interval"));

		aComponent->Spawned	= spawned;
		aComponent->Amount	= amount;
		aComponent->Interval	= interval;
		aComponent->ElapsedTime = 0.f;
		aComponent->SpawnedAmount = 0;
	}

	template <>
	static void InitializeComponent<SpriteComponent>(SpriteComponent* aComponent, const ComponentData& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));
		auto texture = std::any_cast<std::string>(someData.at("texture"));
		auto color = std::any_cast<std::array<float, 4>>(someData.at("color"));

		aComponent->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource(texture);

		//aComponent->m_material = {
		//	&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(texture),
		//	&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader)
		//};

		// aComponent->m_material.SetColor({ color[0], color[1], color[2], color[3] });
	}

	template <>
	static void InitializeComponent<SteeringBehaviorComponent>(SteeringBehaviorComponent* aComponent, const ComponentData& someData)
	{
		std::string behaviorType = std::any_cast<std::string>(someData.at("behavior"));
		std::string layer = std::any_cast<std::string>(someData.at("layer"));

		if (behaviorType == "flock_behavior")
		{
			aComponent->ActiveBehavior = new FlockBehavior{};	// FIX! don't new? Make sure to delete...
			aComponent->Layer = layer;
		}
		if (behaviorType == "wander_behavior")
		{
			aComponent->ActiveBehavior = new WanderBehavior{};
			aComponent->Layer = layer;
		}
	}

	template <>
	static void InitializeComponent<TransformComponent>(TransformComponent* aComponent, const ComponentData& someData)
	{
		auto position = std::any_cast<std::array<float, 3>>(someData.at("position"));
		auto scale = std::any_cast<std::array<float, 3>>(someData.at("scale"));
		float rotation = std::any_cast<float>(someData.at("rotation"));

		aComponent->CurrentPos = aComponent->PreviousPos = { position[0], position[1], position[2] };
		aComponent->Scale = { scale[0], scale[1], scale[2] };
		aComponent->Rotation = rotation;
	}

	template <>
	static void InitializeComponent<TriggerComponent>(TriggerComponent* aComponent, const ComponentData& someData)
	{
		CU::Vector3<float> position = { 0.f, 0.f, 0.f };					// TODO; 
		auto halfSize = std::any_cast<float>(someData.at("halfSize"));

		aComponent->Collider.Init({ position.x - halfSize, position.z - halfSize }, { position.x + halfSize, position.y + halfSize });
	}

	template <>
	static void InitializeComponent<TextComponent>(TextComponent* aComponent, const ComponentData& someData)
	{
		std::string font	= std::any_cast<std::string>(someData.at("font"));
		int size			= std::any_cast<int>(someData.at("size"));
		auto color			= std::any_cast<std::array<float, 4>>(someData.at("color"));

		aComponent->Font = &Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().GetResource(font);
		aComponent->Color = { color[0], color[1], color[2], color[3] };
		aComponent->Size = size;
	}

	template <>
	static void InitializeComponent<RectComponent>(RectComponent* aComponent, const ComponentData& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));

		aComponent->Shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader);
		aComponent->Color = { 1.f, 1.f, 1.f, 1.f }; // TODO; read from json..
	}

	template <>
	static void InitializeComponent<ResourceComponent>(ResourceComponent* aComponent, const ComponentData& someData)
	{
		std::string resource = std::any_cast<std::string>(someData.at("resource"));
		//int quantity = std::any_cast<int>(someData.at("quantity"));

		//aComponent->m_quantity			= (unsigned)quantity;
		aComponent->ResourceType = resource;
	}
	
	template <>
	static void InitializeComponent<VelocityComponent>(VelocityComponent* aComponent, const ComponentData& someData)
	{
		float speed = std::any_cast<float>(someData.at("speed"));
		aComponent->Speed = speed;
	}

	template <>
	static void InitializeComponent<WorldTimeComponent>(WorldTimeComponent* aComponent, const ComponentData& someData)
	{
		float dayDuration = std::any_cast<float>(someData.at("dayDuration"));
		aComponent->DayDuration = dayDuration;
	}




	template <>
	static void InitializeComponent<WanderBehaviorComponent>(WanderBehaviorComponent* aComponent, const ComponentData& someData)
	{
		aComponent->Behavior = new WanderBehavior{}; // Don't new....
	}

	template <>
	static void InitializeComponent<FlockBehaviorComponent>(FlockBehaviorComponent* aComponent, const ComponentData& someData)
	{
		aComponent->Behavior = new FlockBehavior{};	// Make sure to delete...
	}

	template <>
	static void InitializeComponent<SeekBehaviorComponent>(SeekBehaviorComponent* aComponent, const ComponentData& someData)
	{
		// aComponent->m_behavior = new SeekBehavior{}; // Don't new....
	}

	template <>
	static void InitializeComponent<FleeBehaviorComponent>(FleeBehaviorComponent* aComponent, const ComponentData& someData)
	{
		// aComponent->m_behavior = new FleeBehavior{}; // Don't new....

	}

	template <>
	static void InitializeComponent<StateMachineComponent>(StateMachineComponent* aComponent, const ComponentData& someData)
	{
		std::vector<std::string> states = std::any_cast<std::vector<std::string>>(someData.at("states"));

		// Fetch state machine from factory??
		for (const auto& state : states)
		{
			if (state == "idle")
			{
				aComponent->States.push_back(new IdleState{});
			}
			else if (state == "walk")
			{
				aComponent->States.push_back(new WalkState{});
			}
			else if (state == "flee")
			{ }
			else if (state == "attack")
			{ }
			else if (state == "death")
			{ }
		}

		// Temp
		aComponent->ActiveState = aComponent->States[0];

		// TEmp
		// add durtaion condition
		ElapsedTimeCondition* elapsedTime = new ElapsedTimeCondition{ 20.f }; // FIX deletion!
		Transition idleToWalk;
		idleToWalk.SetCondition(elapsedTime);

		aComponent->States[0]->AddTransition(idleToWalk);

		Transition walkToIdle;
		walkToIdle.SetCondition(elapsedTime); // use same condition? => cant delte in desturtor then....
		aComponent->States[1]->AddTransition(walkToIdle); // duraion condition


		// TODO; connect the states
		// set start time in condition	


		
		// add duration condition to idle state.... and duration condition to walk state...



		// unoredred map? string, state?
		// c

	}
};