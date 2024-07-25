#include "Pch.h"
#include "TitleScene.h"
#include "ECS/ECS.h"
#include "Entities/EntityManager.h"
#include "Systems/SystemManager.h"



#include <Components/Core/CoreComponents.h>
#include <Components/UI/UIComponents.h>


TitleScene::TitleScene(ECS& ecs)
	: Scene{ ecs }
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float deltaTime)
{
	m_ecs.Update(deltaTime);
}

void TitleScene::Draw() const 
{
	m_ecs.Draw();
}

void TitleScene::OnEnter()
{
	//Entity camera = m_ecs.CreateEntity("Camera");
	//Entity camera = m_ecs.CreateEmptyEntity();
	//m_ecs.AddComponent<CameraComponent, TransformComponent>(camera);


	//Entity image = m_ecs.CreateEntity("Background");

	//Entity image = m_ecs.CreateEmptyEntity();
	//m_ecs.AddComponent<TransformComponent, SpriteComponent, UIComponent>(image);
	//m_ecs.GetComponent<TransformComponent>(image)->Scale = { 1400.f, 800.f };
	//m_ecs.GetComponent<SpriteComponent>(image)->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "title_image", 0, 0 });

}

void TitleScene::OnExit() 
{
	m_ecs.DestroyAllEntities(); // here?
}