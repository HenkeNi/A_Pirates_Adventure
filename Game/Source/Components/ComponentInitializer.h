#pragma once
#include "Components.h"
#include <Core/Resources/ResourceHolder.hpp>

#include "../Blueprints/EntityBlueprint.h" // DON'T?

#include "../Commands/Move/MoveCommand.h"
#include "../Commands/Attack/AttackCommand.h"
#include "../Commands/Sprint/SprintCommand.h"

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
		aComponent->m_animations = std::any_cast<std::unordered_map<std::string, Animation>>(someData.at("animationMap"));
		aComponent->m_active = std::any_cast<std::string>(someData.at("active"));

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
	static void InitializeComponent<AttackColliderComponent>(AttackColliderComponent* aComponent, const ComponentData& someData)
	{
		auto startPos = CU::Vector3<float>{ 0.f, 0.f, 0.f };
		auto colliderSize = 0.2f;								// FIX!

		// Do in MovementSystem init?
		aComponent->m_offset = { 1.0f, 0.f, 0.f };
		aComponent->m_collider.Init({ startPos.x - colliderSize, startPos.y - colliderSize }, { startPos.x + colliderSize, startPos.y + colliderSize });
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
		aComponent->m_isIdle = true;
		aComponent->m_isAlive = true;
		aComponent->m_isWalking = false;
		aComponent->m_isRunning = false;
		aComponent->m_isJumping = false;
		aComponent->m_isAttacking = false;
	}

	template <>
	static void InitializeComponent<DebugRectComponent>(DebugRectComponent* aComponent, const ComponentData& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));

		aComponent->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader);
		aComponent->m_color = { 1.f, 1.f, 1.f, 1.f }; // TODO; read from json..
	}

	template <>
	static void InitializeComponent<HarvestableComponent>(HarvestableComponent* aComponent, const ComponentData& someData)
	{
		std::string resourceType = std::any_cast<std::string>(someData.at("resource_type"));
		int yield = std::any_cast<int>(someData.at("yield"));

		aComponent->m_yield = yield;
		aComponent->m_resourceType = resourceType;
	}

	template <>
	static void InitializeComponent<HealthComponent>(HealthComponent* aComponent, const ComponentData& someData)
	{
		int value = std::any_cast<int>(someData.at("value"));
		aComponent->m_currentValue = value;

		// TODO; set health stat?!
	}

	template <>
	static void InitializeComponent<HitboxColliderComponent>(HitboxColliderComponent* aComponent, const ComponentData& someData)
	{
		CU::Vector3<float> position = { 0.f, 0.f, 0.f };
		auto halfSize = std::any_cast<float>(someData.at("halfSize"));

		aComponent->m_collider.Init({ position.x - halfSize, position.z - halfSize }, { position.x + halfSize, position.y + halfSize });
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

		aComponent->m_width = width;
		aComponent->m_height = height;
	}

	template <>
	static void InitializeComponent<PlayerControllerComponent>(PlayerControllerComponent* aComponent, const ComponentData& someData)
	{
		// Temp

		// USe builder/factory?

		// Pass in Entity??
		
		aComponent->m_inputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_W, new MoveCommand{{ 0.f,   -1.f }}));
		aComponent->m_inputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_S, new MoveCommand{{ 0.f,	 1.f } }));
		aComponent->m_inputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_A, new MoveCommand{{ -1.f,	 0.f } }));
		aComponent->m_inputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_D, new MoveCommand{{ 1.f,  0.f } }));

		aComponent->m_inputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_Space, new AttackCommand));
		aComponent->m_inputMapping.insert(std::make_pair(Hi_Engine::eInputType::Key_Shift, new SprintCommand));
	}

	template <>
	static void InitializeComponent<SpawnComponent>(SpawnComponent* aComponent, const ComponentData& someData)
	{
		std::string spawned	= std::any_cast<std::string>(someData.at("spawned"));
		int amount			= std::any_cast<int>(someData.at("amount"));
		float interval		= std::any_cast<float>(someData.at("interval"));

		aComponent->m_spawned	= spawned;
		aComponent->m_amount	= amount;
		aComponent->m_interval	= interval;		
		aComponent->m_elapsedTime = 0.f;
		aComponent->m_spawnedAmount = 0;
	}

	template <>
	static void InitializeComponent<SpriteComponent>(SpriteComponent* aComponent, const ComponentData& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));
		auto texture = std::any_cast<std::string>(someData.at("texture"));
		auto color = std::any_cast<std::array<float, 4>>(someData.at("color"));

		aComponent->m_material = {
			&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(texture),
			&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader)
		};

		aComponent->m_material.SetColor({ color[0], color[1], color[2], color[3] });
	}

	template <>
	static void InitializeComponent<TransformComponent>(TransformComponent* aComponent, const ComponentData& someData)
	{
		auto position = std::any_cast<std::array<float, 3>>(someData.at("position"));
		auto scale = std::any_cast<std::array<float, 3>>(someData.at("scale"));
		float rotation = std::any_cast<float>(someData.at("rotation"));

		aComponent->m_currentPos = aComponent->m_previousPos = { position[0], position[1], position[2] };
		aComponent->m_scale = { scale[0], scale[1], scale[2] };
		aComponent->m_rotation = rotation;
	}

	template <>
	static void InitializeComponent<RectComponent>(RectComponent* aComponent, const ComponentData& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));

		aComponent->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader);
		aComponent->m_color = { 1.f, 1.f, 1.f, 1.f }; // TODO; read from json..
	}

	template <>
	static void InitializeComponent<ResourceComponent>(ResourceComponent* aComponent, const ComponentData& someData)
	{
		std::string resource = std::any_cast<std::string>(someData.at("resource"));
		//int quantity = std::any_cast<int>(someData.at("quantity"));

		//aComponent->m_quantity			= (unsigned)quantity;
		aComponent->m_resourceType = resource;
	}
	
	template <>
	static void InitializeComponent<VelocityComponent>(VelocityComponent* aComponent, const ComponentData& someData)
	{
		float speed = std::any_cast<float>(someData.at("speed"));
		aComponent->m_speed = speed;
	}
};