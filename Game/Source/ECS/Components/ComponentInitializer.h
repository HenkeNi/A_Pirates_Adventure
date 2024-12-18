#pragma once
#include "Components.h"
#include "SceneTypes.h"


class ComponentInitializer
{
public:
	//static void InitializeComponent(void* component, const ComponentProperties& properties);

	//static void InitializeComponent(AnimationComponent* component, const ComponentProperties& properties);


	//static void InitializeComponent(class Component* component, const ComponentData& data);
	//template <typename T>
	/*static void Init(void* component, const ComponentProperties& properties)
	{
		InitializeComponent(component, properties);
	}*/

	
	// static void InitializeComponent(void* component, const ComponentProperties& properties) {};

	// use void instead???
	template <typename T>
	inline static void InitializeComponent(T* component, const ComponentProperties& properties) // rename Properties to data?
	{	
		int x = 20;
		x += 20;
	}
	
	template <>
	inline static void InitializeComponent(AnimationComponent* component, const ComponentProperties& properties)
	{
		std::string textureID = std::get<std::string>(properties.at("sheet"));

		component->TextureID = textureID;

		AnimationComponent::Animation animation;
		animation.Frames.push_back({ 1, 0, 0.25f });
		animation.Frames.push_back({ 1, 1, 0.25f });
		animation.Frames.push_back({ 1, 2, 0.25f });
		animation.IsLooping = true;

		component->Animations.insert({ eState::Idle, animation });
		//auto texture = Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(textureID);

		//if (texture)
		//{
		//	//component->SpriteSheet = texture;
		//}

		////std::string active = std::get<std::string>(properties.at("active")); // store index to start instead??

		//int startRow = std::get<int>(properties.at("start_row"));
		//component->CurrentRow = startRow;
		//component->CurrentColumn = 0;

		// FIX!!!!!
		





		//for (const auto& )
		//camt have nested objects in json??f

	}

	template <>
	inline static void InitializeComponent(AttackComponent* component, const ComponentProperties& properties)
	{
	//	auto startPos = FVector2{ 0.f, 0.f };
	//	auto colliderSize = 0.2f;								// FIX!
	//
	//	// Do in MovementSystem init?
	//	// aComponent->Offset = { 1.0f, 0.f };
	//	// aComponent->Collider.Init({ startPos.x - colliderSize, startPos.y - colliderSize }, { startPos.x + colliderSize, startPos.y + colliderSize });
	}
		
	template <>
	inline static void InitializeComponent(AttributesComponent* component, const ComponentProperties& properties)
	{
		component->Perception = std::get<int>(properties.at("Perception"));
	}

	template <>
	inline static void InitializeComponent(AudioComponent* component, const ComponentProperties& properties)
	{
		static const std::unordered_map<std::string, eMessage> soundEventsMapping = {
			{ "item_used", eMessage::ItemUsed },
			{ "item_collected",	eMessage::ItemCollected },
			{ "entity_destroyed", eMessage::EntityDestroyed },
			{ "button_activated", eMessage::ButtonActivated }
		};

		std::string name = std::get<std::string>(properties.at("sound_name"));
		std::string trigger = std::get<std::string>(properties.at("trigger"));

		auto it = soundEventsMapping.find(trigger);
		if (it != soundEventsMapping.end())
		{
			eMessage triggerType = it->second;
			component->SoundTriggers.insert({ triggerType, name });
		}
	}

	template <>
	inline static void InitializeComponent(BehaviorTreeComponent* component, const ComponentProperties& properties)
	{
	}

	template <>
	inline static void InitializeComponent(BoundingBoxComponent* component, const ComponentProperties& properties)
	{
		FVector2 size = std::get<FVector2>(properties.at("size"));

		float halfWidth = size.x * 0.5f;
		float halfHeight = size.y * 0.5f;

		component->Bounds.Init({ -halfWidth, -halfHeight }, { halfWidth, halfHeight });


		if (properties.contains("offset"))
		{
			FVector2 offset = std::get<FVector2>(properties.at("offset"));
			component->Offset.XOffset = offset.x;
			component->Offset.YOffset = offset.y;
			component->Offset.IsDirectionallyBound = std::get<bool>(properties.at("is_offset_directionally_bound"));
		}
	}

	template <>
	inline static void InitializeComponent(CameraComponent* component, const ComponentProperties& properties)
	{
		component->ZoomRange = { 0.5f, 1.f }; // FIX!
	}

	template <>
	inline static void InitializeComponent(StateComponent* component, const ComponentProperties& properties)
	{
		//component->IsIdle = true;
		//component->IsAlive = true;
		//component->IsWalking = false;
		///component->IsRunning = false;
		//component->IsAttacking = false;
		//component->IsAiming = false;
	}

	template <>
	inline static void InitializeComponent(ColliderComponent* component, const ComponentProperties& properties)
	{
		FVector2 size = std::get<FVector2>(properties.at("size"));

		float halfWidth = size.x * 0.5f;
		float halfHeight = size.y * 0.5f;

		component->Collider.Init({ -halfWidth, -halfHeight }, { halfWidth, halfHeight });


		// Store function pointers in map???
		std::string type = std::get<std::string>(properties.at("type"));
		if (type == "Trigger")
		{
			component->Type = eColliderType::Trigger;
		}
		else if (type == "Dynamic")
		{
			component->Type = eColliderType::Dynamic;

			// do in PhysicsSystem instead???
		/*	float xPos = 0.f;
			float yPos = 0.f;
			float width = 25.f;
			float height = 25.f;
			float density = 1.f;
			float friction = 0.3f;*/

		//	Hi_Engine::ServiceLocator::GetPhysics().lock()->CreateDynamicBody({ xPos, yPos, width, height, density, friction });
		}
		else if (type == "Static")
		{
			component->Type = eColliderType::Static;
			///Hi_Engine::ServiceLocator::GetPhysics().lock()->CreateDynamicBody({ xPos, yPos, width, height, density, friction });
		}


		if (properties.contains("offset"))
		{
			FVector2 offset = std::get<FVector2>(properties.at("offset"));
			component->Offset.XOffset = offset.x;
			component->Offset.YOffset = offset.y;
			component->Offset.IsDirectionallyBound = std::get<bool>(properties.at("is_offset_directionally_bound"));
		}



	}

	template <>
	inline static void InitializeComponent(EnvironmentComponent* component, const ComponentProperties& properties)
	{
		//auto types = std::any_cast<std::vector<std::any>>(properties.at("tiles"));
		//for (const auto& type : types)
		//{
		//	if (std::any_cast<std::string>(type) == "grass")
		//	{
		//		//component->AcceptableTileTypes.push_back(eTile::Grass);
		//	}
		//	else if (std::any_cast<std::string>(type) == "sand")
		//	{
		//		//component->AcceptableTileTypes.push_back(eTile::Sand);
		//	}
		//}
	}

	template <>
	inline static void InitializeComponent(GridComponent* component, const ComponentProperties& properties)
	{
		component->Dimensions = std::get<IVector2>(properties.at("dimensions"));
		component->SpaceBetweenCells = (float)std::get<double>(properties.at("space_between_cells"));
	}

	template <>
	inline static void InitializeComponent(HarvestableComponent* component, const ComponentProperties& properties)
	{
		component->ResourceType = std::get<std::string>(properties.at("resource_type"));
		component->Yield = std::get<int>(properties.at("yield"));
	}


	template <>
	inline static void InitializeComponent(HealthComponent* component, const ComponentProperties& properties)
	{
		component->CurrentValue = component->MaxHealth = std::get<int>(properties.at("value"));
		component->IsInvincible = false; // FIX!
	}

	template <>
	inline static void InitializeComponent(InputComponent* component, const ComponentProperties& properties)
	{
		component->InputStates.insert({ Hi_Engine::eKey::Key_W, false });
		component->InputStates.insert({ Hi_Engine::eKey::Key_A, false });
		component->InputStates.insert({ Hi_Engine::eKey::Key_S, false });
		component->InputStates.insert({ Hi_Engine::eKey::Key_D, false });
	}

	template <>
	inline static void InitializeComponent(MapChunkComponent* component, const ComponentProperties& properties)
	{
	}

	template <>
	inline static void InitializeComponent(PlayerControllerComponent* component, const ComponentProperties& properties)
	{
		component->InputMapping.insert({ Hi_Engine::eKey::Key_W, { eCommandType::Move, MovementData{ { 0.f,  1.f }}} });
		component->InputMapping.insert({ Hi_Engine::eKey::Key_A, { eCommandType::Move, MovementData{ { -1.f, 0.f }}} });
		component->InputMapping.insert({ Hi_Engine::eKey::Key_S, { eCommandType::Move, MovementData{ { 0.f,  -1.f }}} });
		component->InputMapping.insert({ Hi_Engine::eKey::Key_D, { eCommandType::Move, MovementData{ { 1.f,  0.f }}} });

		component->InputMapping.insert({ Hi_Engine::eKey::Key_LShift, { eCommandType::Sprint, SprintData{ 200.f} } });
		component->InputMapping.insert({ Hi_Engine::eKey::Key_Space, { eCommandType::Shoot, SprintData{ 200.f} } });
	}

	template <>
	inline static void InitializeComponent(PersonalityComponent* component, const ComponentProperties& properties)
	{
		// component->IsAggressive = std::get<bool>(properties.at("is_aggressive"));
	}

	template <>
	inline static void InitializeComponent(PhysicsComponent* component, const ComponentProperties& properties)
	{
		FVector2 size = std::get<FVector2>(properties.at("size"));
		component->ColliderSize = size;

		//if (properties.contains("offset"))
		//{
			//component->ColliderOffset = std::get<FVector2>(properties.at("offset"));
		//}

		std::string type = std::get<std::string>(properties.at("type"));
		if (type == "Trigger")
		{
			component->Type = eColliderType::Trigger;
		}
		else if (type == "Dynamic")
		{
			component->Type = eColliderType::Dynamic;

			// do in PhysicsSystem instead???
		/*	float xPos = 0.f;
			float yPos = 0.f;
			float width = 25.f;
			float height = 25.f;
			float density = 1.f;
			float friction = 0.3f;*/

			//	Hi_Engine::ServiceLocator::GetPhysics().lock()->CreateDynamicBody({ xPos, yPos, width, height, density, friction });
		}
		else if (type == "Static")
		{
			component->Type = eColliderType::Static;
			///Hi_Engine::ServiceLocator::GetPhysics().lock()->CreateDynamicBody({ xPos, yPos, width, height, density, friction });
		}
	}

	template <>
	inline static void InitializeComponent(ResourceComponent* component, const ComponentProperties& properties)
	{
		component->ResourceType = std::get<std::string>(properties.at("resource"));
	}

	template <>
	inline static void InitializeComponent(SceneTransitionComponent* component, const ComponentProperties& properties)
	{
		static const std::unordered_map<std::string, eScene> sceneTransitionsMapping = {
			{ "game",		eScene::Game },
			{ "menu",		eScene::Menu },
			{ "title",		eScene::Title },
			{ "settings",	eScene::Settings },
			{ "inventory",	eScene::Inventory },
		};

		std::string sceneType = std::get<std::string>(properties.at("scene"));
		auto itr = sceneTransitionsMapping.find(sceneType);
		if (itr != sceneTransitionsMapping.end())
		{
			component->SceneType = itr->second;
		}
	}

	template <>
	inline static void InitializeComponent(SpawnComponent* component, const ComponentProperties& properties)
	{
		component->Spawned = std::get<std::string>(properties.at("spawned"));
		component->Amount = std::get<int>(properties.at("amount"));
		component->Interval = (float)std::get<double>(properties.at("interval"));
		component->ElapsedTime = 0.f;
		component->SpawnedAmount = 0;
	}

	template <>
	inline static void InitializeComponent(SpriteComponent* component, const ComponentProperties& properties)
	{
		std::string texture = std::get<std::string>(properties.at("texture"));
		IVector2 coordinates = std::get<IVector2>(properties.at("coordinates"));
		int depth = std::get<int>(properties.at("render_depth"));
		
		component->Subtexture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ texture, coordinates.x, coordinates.y });
		component->DefaultColor = component->CurrentColor = std::get<FVector4>(properties.at("color"));
		component->RenderDepth = depth;
	}

	template <>
	inline static void InitializeComponent(TagComponent* component, const ComponentProperties& properties)
	{
		static const std::unordered_map<std::string, TagComponent::eEntityType> tagMap = {
			{ "Player", TagComponent::eEntityType::Player },
			{ "Enemy", TagComponent::eEntityType::Enemy },
			{ "NPC", TagComponent::eEntityType::NPC },
			{ "UI", TagComponent::eEntityType::UI },
			{ "Camera", TagComponent::eEntityType::Camera },
			{ "Environment", TagComponent::eEntityType::Environment },
			{ "Collectable", TagComponent::eEntityType::Collectable }
		};
			
		std::string tagType = std::get<std::string>(properties.at("type"));
		
		auto itr = tagMap.find(tagType);
		if (itr != tagMap.end())
		{
			component->Type = itr->second;
		}
	}

	template <>
	inline static void InitializeComponent(TimerComponent* component, const ComponentProperties& properties)
	{
		component->Duration = (float)std::get<double>(properties.at("duration"));
	}

	template <>
	inline static void InitializeComponent(TextComponent* component, const ComponentProperties& properties)
	{	
		static const std::unordered_map<std::string, Hi_Engine::eTextAlginment> textAlignmentsMapping = {
			{ "center", Hi_Engine::eTextAlginment::Align_Center },	
			{ "left",   Hi_Engine::eTextAlginment::Align_Left   },
			{ "right",  Hi_Engine::eTextAlginment::Align_Right  },
		};

		std::string fontType = std::get<std::string>(properties.at("font"));
		std::string alignment = std::get<std::string>(properties.at("alignment"));

		auto itr = textAlignmentsMapping.find(alignment);
		
		component->Alignment = (itr != textAlignmentsMapping.end()) ? itr->second : Hi_Engine::eTextAlginment::Align_Left;
		component->Font = Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().GetResource(fontType);
		component->Text = std::get<std::string>(properties.at("text"));
		component->Color = std::get<FVector4>(properties.at("color"));
		component->Size = std::get<int>(properties.at("size"));
	}

	template <>
	inline static void InitializeComponent(TransformComponent* component, const ComponentProperties& properties)
	{
		component->CurrentPos = component->PreviousPos = std::get<FVector2>(properties.at("position"));
		component->Scale = std::get<FVector2>(properties.at("scale"));
		component->Pivot = std::get<FVector2>(properties.at("pivot"));
		component->Rotation	= (float)std::get<double>(properties.at("rotation"));
	}

	template <>
	inline static void InitializeComponent(UIComponent* component, const ComponentProperties& properties)
	{
		// component->RenderDepth = std::get<int>(properties.at("render_depth"));
		std::string texture = std::get<std::string>(properties.at("texture"));
		IVector2 coordinates = std::get<IVector2>(properties.at("coordinates"));
		int depth = std::get<int>(properties.at("render_depth"));

		component->Subtexture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ texture, coordinates.x, coordinates.y });
		component->DefaultColor = component->CurrentColor = std::get<FVector4>(properties.at("color"));
		component->RenderDepth = depth;
	}

	template <>
	inline static void InitializeComponent(VelocityComponent* component, const ComponentProperties& properties)
	{
		component->BaseSpeed = component->CurrentSpeed = (float)std::get<double>(properties.at("speed"));
	}

	template <>
	inline static void InitializeComponent(WeaponComponent* component, const ComponentProperties& properties)
	{
		component->DamageDealt = std::get<int>(properties.at("damage"));
		component->AttackSpeed = (float)std::get<double>(properties.at("speed"));
	}

	template <>
	inline static void InitializeComponent(WorldTimeComponent* component, const ComponentProperties& properties)
	{
		component->DayDuration = std::get<double>(properties.at("day_duration"));

		// TOOD; fix
		component->TimeOfDayRanges.insert(std::make_pair(eTimeOfDay::Dawn, Hi_Engine::Range{ 0.f, 0.1f }));
		component->TimeOfDayRanges.insert(std::make_pair(eTimeOfDay::Day, Hi_Engine::Range{ 0.11f, 0.6f }));
		component->TimeOfDayRanges.insert(std::make_pair(eTimeOfDay::Dusk, Hi_Engine::Range{ 0.61f, 0.8f }));
		component->TimeOfDayRanges.insert(std::make_pair(eTimeOfDay::Night, Hi_Engine::Range{ 0.81f, 1.0f }));
	}
};