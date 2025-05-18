#include "Pch.h"
#include "TitleScene.h"
//#include <../ECS/World.h>

//#include "Systems/Base/System.h"
//#include "ECS/ECS.h"


//TitleScene::TitleScene(Hi_Engine::ECSCoordinator& ecs)
//	: Scene{ ecs }
//{
//}

//TitleScene::~TitleScene()
//{
//}

void TitleScene::OnUpdate(float deltaTime)
{
}

void TitleScene::OnEnter()
{
	auto cameraEntity = m_ecs.CreateEntity();
	m_ecs.AddComponent<Hi_Engine::CameraComponent>(cameraEntity.value());
	m_ecs.AddComponent<Hi_Engine::TransformComponent>(cameraEntity.value());


	//for (int i = 0; i < Hi_Engine::MaxEntities; ++i)
	for (int i = 0; i < 1000; ++i)
	{
		auto entity = m_ecs.CreateEntity();

		if (entity.has_value())
		{
			auto texture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({"settings_image", 0, 0 });
			m_ecs.AddComponent<Hi_Engine::SpriteComponent>(entity.value(), texture);
			m_ecs.AddComponent<Hi_Engine::TransformComponent>(entity.value());
		}
	}
}

void TitleScene::OnExit() 
{
	// m_ecs.DestroyAllEntities(); // here?
}