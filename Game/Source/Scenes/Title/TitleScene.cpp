#include "Pch.h"
#include "TitleScene.h"
 
//#include "Systems/Base/System.h"
//#include "ECS/ECS.h"


TitleScene::TitleScene(Hi_Engine::RegistryContext context)
	: Scene{ std::move(context) }
{
}

void TitleScene::OnUpdate(float deltaTime)
{
}

void TitleScene::OnEnter()
{
	//auto& systemFactory = Hi_Engine::ECSRegistry::GetSystemFactory();
	// systemFactory.


	// ----------
	// TODO; place factory in scene? (static?)

	// auto& entityFactory = Hi_Engine::ECSRegistry::GetEntityFactory();
	//auto imageHandle = entityFactory.CreateFromPrefab(m_world, "Image");


	//auto cameraHandle = m_world.CreateEntity();

	//if (cameraHandle.has_value())
	//{
	//	auto cameraEntity = cameraHandle.value().GetEntity();

	//	m_world.AddComponent<Hi_Engine::CameraComponent>(cameraEntity);
	//	m_world.AddComponent<Hi_Engine::TransformComponent>(cameraEntity);
	//}

	//entityFactory.CreateFromPrefab(m_world, "Image");

	////for (int i = 0; i < Hi_Engine::MaxEntities; ++i)
	//for (int i = 0; i < 1000; ++i)
	//{
	//	auto entityHandle = m_world.CreateEntity();

	//	if (entityHandle.has_value())
	//	{
	//		auto entity = entityHandle.value().GetEntity();

	//		auto texture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({"settings_image", 0, 0 });
	//		m_world.AddComponent<Hi_Engine::SpriteComponent>(entity, texture);
	//		m_world.AddComponent<Hi_Engine::TransformComponent>(entity);
	//	}
	//}
}

void TitleScene::OnExit() 
{
	// m_ecs.DestroyAllEntities(); // here?
}