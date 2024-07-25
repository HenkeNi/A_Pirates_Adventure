#include "Pch.h"
#include "ComponentInitializer.h"
#include "Components.h"
#include "Commands/Commands.h"
#include "BehaviorTree/BehaviorTreeNodes.h"

#include "../AI/SteeringBehaviors/Flock/FlockBehavior.h"
// #include "../AI/SteeringBehaviors/Wander/WanderBehavior.h"

//void ComponentInitializer::InitializeComponent(Component* component, const ComponentData& data)
//{
//}
//
//void ComponentInitializer::InitializeComponent(AnimationComponent* component, const ComponentProperties& properties)
//{
//	// TODO; engine classes Animation2D and Frame?
//
//// store animations in resource holder??
//
//	//std::unordered_map<std::string, Animation> animations;
//
//	//auto animationsData = std::any_cast<std::vector<std::any>>(data.at("animations"));
//	//for (const auto& animationData : animationsData) // rename Animation Frames instead?
//	//{
//	//	auto properties = std::any_cast<std::unordered_map<std::string, std::any>>(animationData);
//
//	//	std::string identifier = std::any_cast<std::string>(properties.at("identifier"));
//	//	std::string textureName = std::any_cast<std::string>(properties.at("texture"));
//	//	float frameDuration = std::any_cast<float>(properties.at("frame_duration"));
//	//	bool isLooping = std::any_cast<bool>(properties.at("is_looping"));
//	//	bool isPlaying = std::any_cast<bool>(properties.at("is_playing"));
//
//	//	//std::vector<std::string> animationFrames;
//
//	//	std::vector<Hi_Engine::Subtexture2D*> animationFrames;
//	//	for (const auto& sprite : std::any_cast<std::vector<std::any>>(properties.at("subtexture_coordinates")))
//	//	{
//	//		auto s = std::any_cast<std::vector<std::any>>(sprite);
//	//		int row = std::any_cast<int>(s[0]);
//	//		int col = std::any_cast<int>(s[1]);
//
//	//		// Have frame class? row and col to subtexture?
//
//	//		//auto coords = std::any_cast<std::vector<int>>(sprite);
//	//		auto* subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ textureName, row, col });
//	//		animationFrames.push_back(subtexture);
//	//	}
//	//	// animation.Animations
//	//	Animation animation;
//	//	animation.Animations = animationFrames;
//	//	animation.TotalFrames = (unsigned)animationFrames.size();
//	//	animation.CurrentFrame = 0;
//	//	animation.ElapsedFrameTime = 0.f;
//	//	animation.FrameDuration = frameDuration;
//	//	animation.IsLooping = isLooping;
//	//	animation.IsPlaying = isPlaying;
//
//	//	animations.insert_or_assign(identifier, animation); // just use insert?
//	//}
//
//
//	//// aComponent->Animations = std::any_cast<std::unordered_map<std::string, Animation>>(someData.at("animationMap"));
//	//component->Animations = animations;
//
//	//std::string active = std::any_cast<std::string>(data.at("active"));
//	//component->Active = active;
//
//	/*std::string identifier				= std::any_cast<std::string>(someData.at("identifier"));
//	std::vector<std::string> animations = std::any_cast<std::vector<std::string>>(someData.at("animations"));
//	int frames							= std::any_cast<int>(someData.at("frames"));
//	int startFrame						= std::any_cast<int>(someData.at("startFrame"));
//	float frameDuration					= std::any_cast<float>(someData.at("frameDuration"));
//	bool isLooping						= std::any_cast<bool>(someData.at("isLooping"));
//	bool isPlaying						= std::any_cast<bool>(someData.at("isPlaying"));
//
//	aComponent->m_identifier			= identifier;
//	aComponent->m_animations			= animations;
//	aComponent->m_totalFrames			= frames;
//	aComponent->m_currentFrame			= startFrame;
//	aComponent->m_frameDuration			= frameDuration;
//	aComponent->m_elapsedFrameTime		= 0.f;
//	aComponent->m_isLooping				= isLooping;
//	aComponent->m_isPlaying				= isPlaying;*/
//}
//
//void ComponentInitializer::InitializeComponent(AttackComponent* component, const ComponentProperties& properties)
//{
//	auto startPos = FVector2{ 0.f, 0.f };
//	auto colliderSize = 0.2f;								// FIX!
//
//	// Do in MovementSystem init?
//	// aComponent->Offset = { 1.0f, 0.f };
//	// aComponent->Collider.Init({ startPos.x - colliderSize, startPos.y - colliderSize }, { startPos.x + colliderSize, startPos.y + colliderSize });
//}
//
//void ComponentInitializer::InitializeComponent(AttributesComponent* component, const ComponentProperties& properties)
//{
//	// auto properties = properties;
//
//	//int perception = std::any_cast<int>(data.at("Perception"));
//
//	//component->Perception = perception;
//}
//
//void ComponentInitializer::InitializeComponent(AudioComponent* component, const ComponentProperties& properties)
//{
//	static const std::unordered_map<std::string, eMessage> soundEventsMapping = {
//		{ "item_used", eMessage::ItemUsed },
//		{ "item_collected",	eMessage::ItemCollected },
//		{ "entity_destroyed", eMessage::EntityDestroyed },
//		{ "button_activated", eMessage::ButtonActivated }
//	};
//
//	/*std::string name = std::any_cast<std::string>(data.at("sound_name"));
//	std::string trigger = std::any_cast<std::string>(data.at("trigger"));
//
//	auto it = soundEventsMapping.find(trigger);
//
//	if (it != soundEventsMapping.end())
//	{
//		eMessage triggerType = it->second;
//		component->SoundTriggers.insert({ triggerType, name });
//	}*/
//}
//
//void ComponentInitializer::InitializeComponent(BehaviorTreeComponent* component, const ComponentProperties& properties)
//{
//	auto* behavior = new SelectorNode;
//
//
//	auto* chaseSequence = new SequenceNode;
//	chaseSequence->AddChild(new IsTargetSetNode);
//	chaseSequence->AddChild(new IsTargetInSightNode);
//	chaseSequence->AddChild(new InverterNode(new IsTargetReachedNode));
//	chaseSequence->AddChild(new ChaseTargetNode);
//
//	auto* setTarget = new SetTargetNode;
//
//	auto* chaseBehavior = new SelectorNode;
//	chaseBehavior->AddChild(chaseSequence);
//	chaseBehavior->AddChild(setTarget);
//
//	auto* wanderSequence = new SequenceNode;
//	wanderSequence->AddChild(new IsDestinationSetNode);
//	wanderSequence->AddChild(new InverterNode(new IsDestinationReachedNode));
//	wanderSequence->AddChild(new MoveToDestinationNode);
//
//	auto* setPosition = new SetWanderPosition;
//
//	behavior->AddChild(chaseBehavior);
//	behavior->AddChild(wanderSequence);
//	behavior->AddChild(setPosition);
//
//	component->RootNode = behavior;
//
//	//auto* wanderBehavior = new SelectorNode;
//
//
//	//wanderSequence->AddChild(new IsIdleNode);
//
//
//
//
//
//
//
//
//	//auto* setPosition 
//
//	// parallell node => in range OR position not set? => set position...
//
//
//
//	//behavior->AddChild(wanderSequence);
//
//	//auto* updateWanderPositionSequence = new SequenceNode;
//
//
//
//	// Idle sequence
//	//behavior->AddChild(new IdleNode);
//
//
//
//
//
//	//rootNode->AddChild(new MoveToNode);
//	//rootNode->AddChild(new IdleNode);
//
//
//
//	// Sequence => PAtrol > idle...
//
//	// Selector; Alert Patrol Idle?
//
//
//
//	// rootNode->AddChild(new IdleNode);
//
//	// rootNode->
//
//	//component->RootNode = new SequenceNode;
//
//	//component->RootNode
//
//	// selector
//
//
//	// Idle Patrol Alert  Chase Flee Attack 
//
//
//
//
//
//
//	// DO IN system instead??
//	// aComponent->m_rootNode = new SelectorNode;
//
//	// auto attackSequence = new SequenceNode;
//	//attackSequence->AddChild(new TargetInRange)
//}
//
//void ComponentInitializer::InitializeComponent(ButtonComponent* component, const ComponentProperties& properties)
//{
//	static const std::unordered_map<std::string, std::function<void()>> actionMappings =
//	{
//		{ "mute",[]() { Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SetVolumeEvent>(0.f); }}
//	};
//
//	/*if (!data.contains("action"))
//		return;
//
//	std::string action = std::any_cast<std::string>(data.at("action"));
//	if (actionMappings.contains(action))
//	{
//		component->OnClick = actionMappings.at(action);
//	}*/
//
//
//	// std::string identifier = std::any_cast<std::string>(data.at("identifier"));
//
//	// TODO; improve! use SceneTransition component instead?
//	/*if (identifier == "play_button")
//	{
//		component->OnClick = []() {
//			PostMaster::GetInstance().SendMessage({ eMessage::PopScene, eScene::Menu });
//			};
//	}*/
//
//
//	// component->Identifier = type;
//}
//
//void ComponentInitializer::InitializeComponent(CameraComponent* component, const ComponentProperties& properties)
//{
//	component->ZoomRange = { 0.5f, 1.f };
//
//	// aComponent->Camera.Init(0, 1400, 0, 800, 0.f, 100.f);
//
//}
//
//void ComponentInitializer::InitializeComponent(CharacterStateComponent* component, const ComponentProperties& properties)
//{
//	component->IsIdle = true;
//	component->IsAlive = true;
//	component->IsWalking = false;
//	component->IsRunning = false;
//	component->IsAttacking = false;
//	component->IsAiming = false;
//}
//
//void ComponentInitializer::InitializeComponent(ColliderComponent* component, const ComponentProperties& properties)
//{
//	/*auto size = std::any_cast<std::vector<std::any>>(data.at("size"));
//	float width = std::any_cast<float>(size[0]);
//	float height = std::any_cast<float>(size[1]);
//
//	float halfWidth = width * 0.5f;
//	float halfHeight = height * 0.5f;
//
//	component->Collider.Init({ -halfWidth, -halfHeight }, { halfWidth, halfHeight });
//
//	std::string type = std::any_cast<std::string>(data.at("type"));
//	if (type == "trigger")
//	{
//		component->Type = eColliderType::Trigger;
//	}
//	else if (type == "dynamic")
//	{
//		component->Type = eColliderType::Dynamic;
//	}
//
//
//	if (data.contains("offset"))
//	{
//		auto offsetData = std::any_cast<std::unordered_map<std::string, std::any>>(data.at("offset"));
//
//		Offset& offset = component->Offset;
//
//		offset.XOffset = std::any_cast<float>(offsetData.at("xOffset"));
//		offset.YOffset = std::any_cast<float>(offsetData.at("yOffset"));
//		offset.IsDirectionallyBound = std::any_cast<bool>(offsetData.at("isDirectionallyBound"));
//	}*/
//
//}
//
//void ComponentInitializer::InitializeComponent(EnvironmentComponent* component, const ComponentProperties& properties)
//{
//	//auto types = std::any_cast<std::vector<std::any>>(data.at("tiles"));
//
//	//for (const auto& type : types)
//	//{
//	//	if (std::any_cast<std::string>(type) == "grass")
//	//	{
//	//		//component->AcceptableTileTypes.push_back(eTile::Grass);
//
//	//	}
//	//	else if (std::any_cast<std::string>(type) == "sand")
//	//	{
//	//		//component->AcceptableTileTypes.push_back(eTile::Sand);
//	//	}
//	//}
//}
//
//void ComponentInitializer::InitializeComponent(GridComponent* component, const ComponentProperties& properties)
//{
//	/*auto dimensions = std::any_cast<std::vector<std::any>>(data.at("dimensions"));
//	component->Dimensions.x = std::any_cast<int>(dimensions[0]);
//	component->Dimensions.y = std::any_cast<int>(dimensions[1]);
//
//	float spaceBetweenCells = std::any_cast<float>(data.at("space_between_cells"));
//	component->SpaceBetweenCells = spaceBetweenCells;*/
//}
//
//void ComponentInitializer::InitializeComponent(HarvestableComponent* component, const ComponentProperties& properties)
//{
//	//std::string resourceType = std::any_cast<std::string>(data.at("resource_type"));
//	//int yield = std::any_cast<int>(data.at("yield"));
//
//	//component->Yield = yield;
//	//component->ResourceType = resourceType;
//}
//
//void ComponentInitializer::InitializeComponent(HealthComponent* component, const ComponentProperties& properties)
//{
//	//int value = std::any_cast<int>(data.at("value"));
//	//component->CurrentValue = value;
//	//component->IsInvincible = false;
//	//// TODO; set health stat?!
//}
//

//void ComponentInitializer::InitializeComponent(MapChunkComponent* component, const ComponentProperties& properties)
//{
//	//int width = std::any_cast<int>(data.at("width"));
//	//int height = std::any_cast<int>(data.at("height"));
//
//	// MapChunkComponent::TileCountPerSide = width;
//
//	//aComponent->Width = width;
//	//aComponent->Height = height;
//}
//
//void ComponentInitializer::InitializeComponent(PlayerControllerComponent* component, const ComponentProperties& properties)
//{
//	// Temp
//
//		// USe builder/factory?
//
//		// Pass in Entity??
//
//		// Have an map of keys, one with mouse input and one with controller input??
//
//		// TODO; make sure to delete...
//	component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_W, new MoveCommand{ { 0.f,   1.f } }));
//	component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_S, new MoveCommand{ { 0.f,	-1.f } }));
//	component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_A, new MoveCommand{ { -1.f,	 0.f } }));
//	component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_D, new MoveCommand{ { 1.f,  0.f } }));
//
//	component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_Space, new AttackCommand));
//	component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_LShift, new SprintCommand));
//	component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_Escape, new PauseCommand));
//	component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_I, new OpenInventoryCommand));
//	component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_1, new AimCommand)); // CHANGE To mouse button
//	component->InputMapping.insert(std::make_pair(Hi_Engine::eKey::Key_2, new ShootCommand));
//}
//
//void ComponentInitializer::InitializeComponent(SpawnComponent* component, const ComponentProperties& properties)
//{
//	//std::string spawned = std::any_cast<std::string>(data.at("spawned"));
//	//int amount = std::any_cast<int>(data.at("amount"));
//	//float interval = std::any_cast<float>(data.at("interval"));
//
//	//component->Spawned = spawned;
//	//component->Amount = amount;
//	//component->Interval = interval;
//	//component->ElapsedTime = 0.f;
//	//component->SpawnedAmount = 0;
//}
//
//void ComponentInitializer::InitializeComponent(SpriteComponent* component, const ComponentProperties& properties)
//{
//	/*auto texture = std::any_cast<std::string>(data.at("texture"));
//	auto color = std::any_cast<std::vector<std::any>>(data.at("color"));
//	auto coordinates = std::any_cast<std::vector<std::any>>(data.at("coordinates"));
//
//	component->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ texture, std::any_cast<int>(coordinates[0]), std::any_cast<int>(coordinates[1]) });
//	component->DefaultColor = component->CurrentColor = { std::any_cast<float>(color[0]), std::any_cast<float>(color[1]), std::any_cast<float>(color[2]), std::any_cast<float>(color[3]) };*/
//}
//
//void ComponentInitializer::InitializeComponent(SteeringBehaviorComponent* component, const ComponentProperties& properties)
//{
//	//std::string behaviorType = std::any_cast<std::string>(data.at("behavior"));
//	//std::string layer = std::any_cast<std::string>(data.at("layer"));
//
//	//if (behaviorType == "flock_behavior")
//	//{
//	//	component->ActiveBehavior = new FlockBehavior{};	// FIX! don't new? Make sure to delete...
//	//	component->Layer = layer;
//	//}
//	//if (behaviorType == "wander_behavior")
//	//{
//	//	// component->ActiveBehavior = new WanderBehavior{};
//	//	component->Layer = layer;
//	//}
//}
//
//void ComponentInitializer::InitializeComponent(TransformComponent* component, const ComponentProperties& properties)
//{
//	//auto position = std::any_cast<std::array<float, 3>>(someData.at("position"));
//		//auto scale = std::any_cast<std::array<float, 3>>(someData.at("scale"));
//
//	/*auto position = std::any_cast<std::vector<std::any>>(data.at("position"));
//	auto scale = std::any_cast<std::vector<std::any>>(data.at("scale"));
//	auto pivot = std::any_cast<std::vector<std::any>>(data.at("pivot"));
//	float rotation = std::any_cast<float>(data.at("rotation"));
//
//
//
//	component->CurrentPos = component->PreviousPos = { std::any_cast<float>(position[0]), std::any_cast<float>(position[1]) };
//	component->Scale = { std::any_cast<float>(scale[0]), std::any_cast<float>(scale[1]) };
//	component->Pivot = { std::any_cast<float>(pivot[0]), std::any_cast<float>(pivot[1]) };
//	component->Rotation = rotation;*/
//}
//
//void ComponentInitializer::InitializeComponent(TextComponent* component, const ComponentProperties& properties)
//{
//	static const std::unordered_map<std::string, Hi_Engine::eTextAlginment> textAlignmentsMapping = {
//			{ "center", Hi_Engine::eTextAlginment::Align_Center },
//			{ "left",   Hi_Engine::eTextAlginment::Align_Left   },
//			{ "right",  Hi_Engine::eTextAlginment::Align_Right  },
//	};
//
//	/*std::string text = std::any_cast<std::string>(data.at("text"));
//	std::string font = std::any_cast<std::string>(data.at("font"));
//	auto color = std::any_cast<std::vector<std::any>>(data.at("color"));
//	int size = std::any_cast<int>(data.at("size"));
//
//	std::string alignment = std::any_cast<std::string>(data.at("alignment"));
//
//	component->Font = &Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().GetResource(font);
//	component->Color = { std::any_cast<float>(color[0]), std::any_cast<float>(color[1]), std::any_cast<float>(color[2]), std::any_cast<float>(color[3]) };
//	component->Size = size;
//	component->Text = text;
//
//	auto it = textAlignmentsMapping.find(alignment);
//
//	component->Alignment = (it != textAlignmentsMapping.end()) ? it->second : Hi_Engine::eTextAlginment::Align_Left;*/
//}
//
//void ComponentInitializer::InitializeComponent(ResourceComponent* component, const ComponentProperties& properties)
//{
//	//std::string resource = std::any_cast<std::string>(data.at("resource"));
//	//int quantity = std::any_cast<int>(data.at("quantity"));
//
//	//component->m_quantity			= (unsigned)quantity;
//	//component->ResourceType = resource;
//}
//
//void ComponentInitializer::InitializeComponent(VelocityComponent* component, const ComponentProperties& properties)
//{
//	//float speed = std::any_cast<float>(data.at("speed"));
//	//component->Speed = speed;
//}
//
//void ComponentInitializer::InitializeComponent(WeaponComponent* component, const ComponentProperties& properties)
//{
//	/*int damage = std::any_cast<int>(data.at("damage"));
//	float speed = std::any_cast<float>(data.at("speed"));
//
//	component->DamageDealt = damage;
//	component->AttackSpeed = speed;*/
//}
//
//void ComponentInitializer::InitializeComponent(WorldTimeComponent* component, const ComponentProperties& properties)
//{
//	//float dayDuration = std::any_cast<float>(data.at("day_duration"));
//
//	//// TOOD; fix
//	//component->TimeOfDayRanges.insert(std::make_pair(eTimeOfDay::Dawn, Hi_Engine::Range{ 0.f, 0.1f }));
//	//component->TimeOfDayRanges.insert(std::make_pair(eTimeOfDay::Day, Hi_Engine::Range{ 0.11f, 0.6f }));
//	//component->TimeOfDayRanges.insert(std::make_pair(eTimeOfDay::Dusk, Hi_Engine::Range{ 0.61f, 0.8f }));
//	//component->TimeOfDayRanges.insert(std::make_pair(eTimeOfDay::Night, Hi_Engine::Range{ 0.81f, 1.0f }));
//
//	//component->DayDuration = dayDuration;
//}
//

//void ComponentInitializer::InitializeComponent(PersonalityComponent* component, const ComponentProperties& properties)
//{
//	/*bool isAggressive = std::any_cast<bool>(data.at("IsAggressive"));
//
//	component->IsAggressive = isAggressive;*/
//}
//
//void ComponentInitializer::InitializeComponent(FlockBehaviorComponent* component, const ComponentProperties& properties)
//{
//	// component->Behavior = new FlockBehavior{};	// Make sure to delete...
//}
//

//
//void ComponentInitializer::InitializeComponent(TagComponent* component, const ComponentProperties& properties)
//{
//	/*static const std::unordered_map<std::string, TagComponent::eEntityType> TagMap = {
//		{ "player", TagComponent::eEntityType::Player },
//		{ "enemy", TagComponent::eEntityType::Enemy },
//		{ "npc", TagComponent::eEntityType::NPC },
//		{ "ui", TagComponent::eEntityType::UI },
//		{ "camera", TagComponent::eEntityType::Camera },
//		{ "environment", TagComponent::eEntityType::Environment },
//		{ "collectable", TagComponent::eEntityType::Collectable }
//	};
//
//	std::string tagType = std::any_cast<std::string>(data.at("type"));
//
//
//	component->type = TagMap.at(tagType);*/
//}






//void ComponentInitializer::InitializeComponent(SceneTransitionComponent* component, const ComponentProperties& properties)
//{
//	//static const std::unordered_map<std::string, eScene> sceneTransitionsMapping = {
//	//		{ "game",		eScene::Game },
//	//		{ "menu",		eScene::Menu },
//	//		{ "title",		eScene::Title },
//	//		{ "settings",	eScene::Settings },
//	//		{ "inventory",	eScene::Inventory },
//	//};
//
//	//if (!data.contains("scene"))
//	//	return;
//
//	//std::string scene = std::any_cast<std::string>(data.at("scene"));
//
//	////component->ShouldPush = !std::any_cast<bool>(data.at("should_remove"));
//	//auto it = sceneTransitionsMapping.find(scene);
//
//	//component->SceneType = it->second;
//}





//void ComponentInitializer::InitializeComponent(TimerComponent* component, const ComponentProperties& properties)
//{
//	/*float duration = std::any_cast<float>(data.at("duration"));
//	component->Duration = duration;*/
//}
//void ComponentInitializer::InitializeComponent(UIComponent* component, const ComponentProperties& properties)
//{
//	/*if (data.contains("render_depth"))
//		component->RenderDepth = std::any_cast<int>(data.at("render_depth"));*/
//}