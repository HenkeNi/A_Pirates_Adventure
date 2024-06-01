#include "Pch.h"
#include "MenuScene.h"
#include "Systems/SystemManager.h"


MenuScene::MenuScene(SharedContext context)
	: Scene{ context }
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Update(float deltaTime)
{
	m_sharedContext.SystemManager.Update(deltaTime);
}

void MenuScene::LateUpdate(float deltaTime)
{
}

void MenuScene::Draw() const
{
	m_sharedContext.SystemManager.Draw();
}

void MenuScene::OnEnter()
{
	auto& systemManager = m_sharedContext.SystemManager;
	systemManager.Init(&m_entityManager);

	m_entityManager.GetFactory().LoadBlueprints("../Game/Assets/Json/Blueprints/blueprint_manifest.json"); // load differnet blueprints depding on scene? OR read scene specific entities

	//auto& sound = Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource("theme_song"); // TODO; read from json...
	//Hi_Engine::ServiceLocator::GetAudioController().lock()->PlaySound(sound);
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::PlaySoundEvent>("theme_song");
}

void MenuScene::OnExit()
{
	m_entityManager.DestroyAll();

	//auto& sound = Hi_Engine::ResourceHolder<Hi_Engine::AudioSource>::GetInstance().GetResource("theme_song");
	//Hi_Engine::ServiceLocator::GetAudioController().lock()->StopSound(sound);

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::StopSoundEvent>("theme_song");
}