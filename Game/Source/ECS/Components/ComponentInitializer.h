#pragma once
#include "Components.h"
#include <Core/Resources/ResourceHolder.hpp>

#include "../Entities/EntityBlueprint.h" // DON'T?

#include "../Commands/Move/MoveCommand.h"
#include "../Commands/Attack/AttackCommand.h"
#include "../Commands/Sprint/SprintCommand.h"

#include "../AI/SteeringBehaviors/Flock/FlockBehavior.h"
#include "../AI/SteeringBehaviors/Wander/WanderBehavior.h"

#include "../AI/StateMachine/States/Idle/IdleState.h"
#include "../AI/StateMachine/States/Walk/WalkState.h"

#include "../AI/StateMachine/Conditions/Time/TimeConditions.h"


// struct ComponentData;

namespace ECS
{
	using ComponentData = std::unordered_map<std::string, std::any>;
}

class ComponentInitializer
{
public:
	// using ComponentData = std::unordered_map<std::string, std::any>;

	template <typename T>
	static void InitializeComponent(T* aComponent, const ECS::ComponentData& someData)
	{
	}

	template <>
	static void InitializeComponent<AnimationComponent>(AnimationComponent* aComponent, const ECS::ComponentData& someData)
	{
		auto animationData = std::any_cast<std::vector<std::any>>(someData.at("animations"));

		std::unordered_map<std::string, Animation> animations;
		for (const auto& data : animationData)
		{
			auto properties = std::any_cast<std::unordered_map<std::string, std::any>>(data);

			std::string identifier = std::any_cast<std::string>(properties.at("identifier"));

			//Animation animation;
			float frameDuration = std::any_cast<float>(properties.at("frame_duration"));
			bool isLooping = std::any_cast<bool>(properties.at("is_looping"));
			bool isPlaying = std::any_cast<bool>(properties.at("is_playing"));

			//std::vector<std::string> animationFrames;

			std::vector<Hi_Engine::Subtexture2D*> animationFrames;
			for (const auto& sprite : std::any_cast<std::vector<std::any>>(properties.at("sprites")))
			{
				animationFrames.push_back(&Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource(std::any_cast<std::string>(sprite)));
			}
			// animation.Animations
			Animation animation;
			animation.Animations = animationFrames;
			animation.TotalFrames = animationFrames.size();
			animation.CurrentFrame = 0;
			animation.ElapsedFrameTime = 0.f;
			animation.FrameDuration = frameDuration;
			animation.IsLooping = isLooping;
			animation.IsPlaying = isPlaying;

			animations.insert_or_assign(identifier, animation);
		}


		// aComponent->Animations = std::any_cast<std::unordered_map<std::string, Animation>>(someData.at("animationMap"));
		aComponent->Animations = animations;

		std::string active = std::any_cast<std::string>(someData.at("active"));
		aComponent->Active = active;

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
	static void InitializeComponent<AttackComponent>(AttackComponent* aComponent, const ECS::ComponentData& someData)
	{
		auto startPos = CU::Vector3<float>{ 0.f, 0.f, 0.f };
		auto colliderSize = 0.2f;								// FIX!

		// Do in MovementSystem init?
		aComponent->Offset = { 1.0f, 0.f, 0.f };
		aComponent->Collider.Init({ startPos.x - colliderSize, startPos.y - colliderSize }, { startPos.x + colliderSize, startPos.y + colliderSize });
	}

	template <>
	static void InitializeComponent<BehaviorTreeComponent>(BehaviorTreeComponent* aComponent, const ECS::ComponentData& someData)
	{
		// DO IN system instead??
		// aComponent->m_rootNode = new SelectorNode;

		// auto attackSequence = new SequenceNode;
		//attackSequence->AddChild(new TargetInRange)
	}

	template <>
	static void InitializeComponent<CameraComponent>(CameraComponent* aComponent, const ECS::ComponentData& someData)
	{
		int xx = 20;
		xx += 20;
	}
	
	template <>
	static void InitializeComponent<CharacterStateComponent>(CharacterStateComponent* aComponent, const ECS::ComponentData& someData)
	{
		aComponent->IsIdle = true;
		aComponent->IsAlive = true;
		aComponent->IsWalking = false;
		aComponent->IsRunning = false;
		aComponent->IsJumping = false;
		aComponent->IsAttacking = false;
	}

	template <>
	static void InitializeComponent<DebugRectComponent>(DebugRectComponent* aComponent, const ECS::ComponentData& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));

		aComponent->Shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader);
		aComponent->Color = { 1.f, 1.f, 1.f, 1.f }; // TODO; read from json..
	}

	template <>
	static void InitializeComponent<HarvestableComponent>(HarvestableComponent* aComponent, const ECS::ComponentData& someData)
	{
		std::string resourceType = std::any_cast<std::string>(someData.at("resource_type"));
		int yield = std::any_cast<int>(someData.at("yield"));

		aComponent->Yield = yield;
		aComponent->ResourceType = resourceType;
	}

	template <>
	static void InitializeComponent<HealthComponent>(HealthComponent* aComponent, const ECS::ComponentData& someData)
	{
		int value = std::any_cast<int>(someData.at("value"));
		aComponent->CurrentValue = value;

		// TODO; set health stat?!
	}

	template <>
	static void InitializeComponent<HitboxComponent>(HitboxComponent* aComponent, const ECS::ComponentData& someData)
	{
		CU::Vector3<float> position = { 0.f, 0.f, 0.f };
		auto halfSize = std::any_cast<float>(someData.at("half_size"));
		bool isStatic = std::any_cast<bool>(someData.at("is_static"));

		aComponent->Collider.Init({ position.x - halfSize, position.z - halfSize }, { position.x + halfSize, position.y + halfSize });
		aComponent->IsStatic = isStatic;
	}

	template <>
	static void InitializeComponent<InventoryComponent>(InventoryComponent* aComponent, const ECS::ComponentData& someData)
	{
		int xx = 20;
		xx += 20;
	}
	
	template <>
	static void InitializeComponent<MapChunkComponent>(MapChunkComponent* aComponent, const ECS::ComponentData& someData)
	{
		int width = std::any_cast<int>(someData.at("width"));
		int height = std::any_cast<int>(someData.at("height"));

		aComponent->Width = width;
		aComponent->Height = height;
	}

	template <>
	static void InitializeComponent<PlayerControllerComponent>(PlayerControllerComponent* aComponent, const ECS::ComponentData& someData)
	{
		// Temp

		// USe builder/factory?

		// Pass in Entity??
		
		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_W, new MoveCommand{{ 0.f,   -1.f }}));
		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_S, new MoveCommand{{ 0.f,	 1.f } }));
		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_A, new MoveCommand{{ -1.f,	 0.f } }));
		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_D, new MoveCommand{{ 1.f,  0.f } }));

		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_Space, new AttackCommand));
		aComponent->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_LShift, new SprintCommand));
	}

	template <>
	static void InitializeComponent<SpawnComponent>(SpawnComponent* aComponent, const ECS::ComponentData& someData)
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
	static void InitializeComponent<SpriteComponent>(SpriteComponent* aComponent, const ECS::ComponentData& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));
		auto texture = std::any_cast<std::string>(someData.at("texture"));
		//auto color = std::any_cast<std::array<float, 4>>(someData.at("color"));
		auto color = std::any_cast<std::vector<std::any>>(someData.at("color"));

		aComponent->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource(texture);
		aComponent->Color = { std::any_cast<float>(color[0]), std::any_cast<float>(color[1]), std::any_cast<float>(color[2]), std::any_cast<float>(color[3]) };
		//aComponent->m_material = {
		//	&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(texture),
		//	&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader)
		//};

		// aComponent->m_material.SetColor({ color[0], color[1], color[2], color[3] });
	}

	template <>
	static void InitializeComponent<SteeringBehaviorComponent>(SteeringBehaviorComponent* aComponent, const ECS::ComponentData& someData)
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
	static void InitializeComponent<TransformComponent>(TransformComponent* aComponent, const ECS::ComponentData& someData)
	{
		//auto position = std::any_cast<std::array<float, 3>>(someData.at("position"));
		//auto scale = std::any_cast<std::array<float, 3>>(someData.at("scale"));
		
		auto position = std::any_cast<std::vector<std::any>>(someData.at("position"));
		auto scale = std::any_cast<std::vector<std::any>>(someData.at("scale"));
		float rotation = std::any_cast<float>(someData.at("rotation"));

		aComponent->CurrentPos = aComponent->PreviousPos = { std::any_cast<float>(position[0]), std::any_cast<float>(position[1]), std::any_cast<float>(position[2]) };
		aComponent->Scale = { std::any_cast<float>(scale[0]), std::any_cast<float>(scale[1]), std::any_cast<float>(scale[2]) };
		aComponent->Rotation = rotation;
	}

	template <>
	static void InitializeComponent<TriggerComponent>(TriggerComponent* aComponent, const ECS::ComponentData& someData)
	{
		CU::Vector3<float> position = { 0.f, 0.f, 0.f };					// TODO; 
		auto halfSize = std::any_cast<float>(someData.at("half_size"));

		aComponent->Collider.Init({ position.x - halfSize, position.z - halfSize }, { position.x + halfSize, position.y + halfSize });
	}

	template <>
	static void InitializeComponent<TextComponent>(TextComponent* aComponent, const ECS::ComponentData& someData)
	{
		std::string font	= std::any_cast<std::string>(someData.at("font"));
		int size			= std::any_cast<int>(someData.at("size"));
		//auto color			= std::any_cast<std::array<float, 4>>(someData.at("color"));
		auto color = std::any_cast<std::vector<std::any>>(someData.at("color"));

		aComponent->Font = &Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().GetResource(font);
		aComponent->Color = { std::any_cast<float>(color[0]), std::any_cast<float>(color[1]), std::any_cast<float>(color[2]), std::any_cast<float>(color[3]) };
		aComponent->Size = size;
	}

	template <>
	static void InitializeComponent<RectComponent>(RectComponent* aComponent, const ECS::ComponentData& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));

		aComponent->Shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader);
		aComponent->Color = { 1.f, 1.f, 1.f, 1.f }; // TODO; read from json..
	}

	template <>
	static void InitializeComponent<ResourceComponent>(ResourceComponent* aComponent, const ECS::ComponentData& someData)
	{
		std::string resource = std::any_cast<std::string>(someData.at("resource"));
		//int quantity = std::any_cast<int>(someData.at("quantity"));

		//aComponent->m_quantity			= (unsigned)quantity;
		aComponent->ResourceType = resource;
	}
	
	template <>
	static void InitializeComponent<VelocityComponent>(VelocityComponent* aComponent, const ECS::ComponentData& someData)
	{
		float speed = std::any_cast<float>(someData.at("speed"));
		aComponent->Speed = speed;
	}

	template <>
	static void InitializeComponent<WorldTimeComponent>(WorldTimeComponent* aComponent, const ECS::ComponentData& someData)
	{
		float dayDuration = std::any_cast<float>(someData.at("day_duration"));
		aComponent->DayDuration = dayDuration;
	}




	template <>
	static void InitializeComponent<WanderBehaviorComponent>(WanderBehaviorComponent* aComponent, const ECS::ComponentData& someData)
	{
		aComponent->Behavior = new WanderBehavior{}; // Don't new....
	}

	template <>
	static void InitializeComponent<FlockBehaviorComponent>(FlockBehaviorComponent* aComponent, const ECS::ComponentData& someData)
	{
		aComponent->Behavior = new FlockBehavior{};	// Make sure to delete...
	}

	template <>
	static void InitializeComponent<SeekBehaviorComponent>(SeekBehaviorComponent* aComponent, const ECS::ComponentData& someData)
	{
		// aComponent->m_behavior = new SeekBehavior{}; // Don't new....
	}

	template <>
	static void InitializeComponent<FleeBehaviorComponent>(FleeBehaviorComponent* aComponent, const ECS::ComponentData& someData)
	{
		// aComponent->m_behavior = new FleeBehavior{}; // Don't new....

	}

	template <>
	static void InitializeComponent<StateMachineComponent>(StateMachineComponent* aComponent, const ECS::ComponentData& someData)
	{
		auto states = std::any_cast<std::vector<std::any>>(someData.at("states"));

		//std::vector<std::string> states = std::any_cast<std::vector<std::string>>(someData.at("states"));

		// Fetch state machine from factory??
		for (const auto& state : states)
		{
			std::string castedState = std::any_cast<std::string>(state);

			if (castedState == "idle")
			{
				aComponent->States.push_back(new IdleState{});
			}
			else if (castedState == "walk")
			{
				aComponent->States.push_back(new WalkState{});
			}
			else if (castedState == "flee")
			{ }
			else if (castedState == "attack")
			{ }
			else if (castedState == "death")
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