#include "Pch.h"
#include "Game.h"
#include "Scenes/Scenes.h"
#include "Systems/Systems.h"
#include <Core/Resources/ResourceHolder.hpp>


Game::Game()
{
}

Game::~Game()
{
}

void Game::OnUpdate(float aDeltaTime)
{
	m_sceneManager.Update(aDeltaTime);
	m_systemManager.Update(aDeltaTime);
}

void Game::OnLateUpdate(float aDeltaTime)
{
	m_sceneManager.LateUpdate(aDeltaTime);
	m_systemManager.LateUpdate(aDeltaTime);
}
//#include "Data/Structs.h"
//#include "Core/Rendering/Renderers/PrimitiveRenderer/PrimitiveRenderer.h"
void Game::OnDraw()
{
	// TEST (TPDP SET CAMERA!!)
	s
	Hi_Engine::PrimitiveRenderer::GetInstance().Render({ CU::Vector3<float>{ 0.5f, 0.3f, 0.3f }, 
		&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Primitive"), { 0.f, 0.f, 0.f }, { 1.f, 1.f}, 0.f });
	
	// CU::Vector3<float>	m_color;
	// class Shader* m_shader;
	// glm::vec3			Position;
	// glm::vec2			Scale;
	// float				Rotation;
	//

	m_sceneManager.Draw();
	m_systemManager.Draw();
}

void Game::OnCreate()
{
	EntityManager::RegisterComponentBuilders();
	RegisterSystems();

	LoadResources();
	SetupScenes();

	//Generated::RegisterComponents();
	//Generated::RegisterPrototypes();	

	MapInput();
}

void Game::OnDestroy()
{
	m_systemManager.Clear();
	m_sceneManager.Clear();
}

void Game::SetupScenes()
{
	SceneManagerProxy proxy{ m_sceneManager };

	m_sceneManager.Register(std::make_unique<GameScene>(SharedContext{ proxy, m_systemManager }), eScene::Game);
	//m_sceneManager.Register(std::make_unique<LoadingScene>(proxy),  eScene::Loading);
	//m_sceneManager.Register(std::make_unique<MenuScene>(proxy),		eScene::Menu);
	//m_sceneManager.Register(std::make_unique<PauseScene>(proxy),	eScene::Pause);
	//m_sceneManager.Register(std::make_unique<TitleScene>(proxy),	eScene::Title);
		
	//m_sceneManager.Init(eScene::Game | eScene::Menu | eScene::Loading | eScene::Title);
	m_sceneManager.Init((int)eScene::Game);
}

void Game::RegisterSystems()
{
	m_systemManager.Register(std::make_unique<CombatSystem>());
	m_systemManager.Register(std::make_unique<MeleeCombatSystem>());
	m_systemManager.Register(std::make_unique<RangedCombatSystem>());
	
	m_systemManager.Register(std::make_unique<PlayerControllerSystem>());
	m_systemManager.Register(std::make_unique<InputSystem>());

	m_systemManager.Register(std::make_unique<CollisionSystem>());
	m_systemManager.Register(std::make_unique<MovementSystem>());

	m_systemManager.Register(std::make_unique<SpriteAnimationSystem>());
	m_systemManager.Register(std::make_unique<CameraSystem>());
	m_systemManager.Register(std::make_unique<DebugRenderSystem>());
	m_systemManager.Register(std::make_unique<SpriteRenderSystem>());
}

void Game::LoadResources()
{
	Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().FetchAll("../Game/Assets/Json/Resources/Textures.json");
	Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().FetchAll("../Engine/Assets/Json/Resources/Shaders.json");
}

void Game::MapInput() // or MapControlls? // Rename ConfigureInput?? Move to InputSystem??
{
	//Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_W, new MoveCommand{  0.f, -1.f });
	//Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_A, new MoveCommand{ -1.f,  0.f });
	//Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_S, new MoveCommand{  0.f,  1.f });
	//Hi_Engine::InputHandler::MapCommand(Hi_Engine::eInputType::Key_D, new MoveCommand{  1.f,  0.f });
}