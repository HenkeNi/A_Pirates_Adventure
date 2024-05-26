#include "Pch.h"
#include "OverworldScene.h"
#include "Systems/SystemManager.h"

OverworldScene::OverworldScene(SharedContext context)
	: Scene{ context }
{
}

OverworldScene::~OverworldScene()
{
}

void OverworldScene::Update(float deltaTime)
{
	m_sharedContext.SystemManager.Update(deltaTime);
}

void OverworldScene::LateUpdate(float deltaTime)
{
	m_sharedContext.SystemManager.LateUpdate(deltaTime);
}

void OverworldScene::Draw() const
{
	m_sharedContext.SystemManager.Draw();
}

void OverworldScene::OnCreated()
{
}

void OverworldScene::OnEnter()
{
	auto& systemManager = m_sharedContext.SystemManager;
	systemManager.Init(&m_entityManager);

	// Send event??
	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json");

	auto& sound = Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource("ocean_ambience"); // TODO; read from json...
	//Hi_Engine::ServiceLocator::GetAudioController().lock()->PlaySound(sound);


	auto* cursor = m_entityManager.Create("mouse_cursor");

	// Player
	auto* player = m_entityManager.Create("player");
	//CU::Vector3<float> position = { (float)Random::InRange(2, 62), 0.42f, (float)Random::InRange(2, 62) };
	FVector2 position = { 0.f, 0.f }; // { 27.f, 25.f };
	player->GetComponent<TransformComponent>()->CurrentPos = position;

	// player->GetComponent<SpriteComponent>()->Pivot = { -0.5f, -0.5f };


	auto* weapon = m_entityManager.Create("rusty_sword");

	auto* time = m_entityManager.Create("world_time");


	auto* skeleton = m_entityManager.Create("skeleton");

	auto* crab = m_entityManager.Create("crab");

	auto* caveEntrance = m_entityManager.Create("cave_entrance");
	caveEntrance->GetComponent<TransformComponent>()->CurrentPos = { 2.f, 2.f };

	//auto healthbar = m_entityManager.Create("Healthbar");
	//healthbar->GetComponent<TransformComponent>()->CurrentPos = { 2.f, 2.f };

	/*for (int i = 0; i < 10; ++i)
	{
		float x = 0.1 * i;
		auto* fish = m_entityManager.Create("Fish");
		fish->GetComponent<TransformComponent>()->CurrentPos = { 10.f + x, 12.f };
	}*/

	// Camera => do in camera system??
	auto camera = m_entityManager.Create("camera");
	camera->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 0.f };
	camera->GetComponent<CameraComponent>()->TargetOffset = { 0.f, 0.f };
	camera->GetComponent<CameraComponent>()->TargetID = m_entityManager.FindFirst<PlayerControllerComponent>()->GetID();

	//camera->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 2.f };
	//camera->GetComponent<TransformComponent>()->CurrentPos = { 0.f, 0.f, 2.f };
	//camera->GetComponent<CameraComponent>()->TargetOffset = { 0.f, 3.f, 4.f };
	//camera->GetComponent<CameraComponent>()->m_target = *m_entityManager.FindAll<PlayerControllerComponent>().begin();

	PostMaster::GetInstance().SendMessage({ eMessage::GameStarted, true }); 	// FIX
}

void OverworldScene::OnExit()
{
	auto& sound = Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource("ocean_ambience"); // TODO; read from json...
	//Hi_Engine::ServiceLocator::GetAudioController().lock()->StopSound(sound);
}
