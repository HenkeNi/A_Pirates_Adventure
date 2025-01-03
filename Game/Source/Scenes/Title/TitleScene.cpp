#include "Pch.h"
#include "TitleScene.h"
//#include "Systems/Base/System.h"
//#include "ECS/ECS.h"


//TitleScene::TitleScene(Hi_Engine::ECSCoordinator& ecs)
//	: Scene{ ecs }
//{
//}

//TitleScene::~TitleScene()
//{
//}

void TitleScene::Update(float deltaTime)
{
	/*for (auto& systemWeak : m_systems)
	{
		if (auto system = systemWeak.lock())
		{
			system->Update(deltaTime);
		}
	}*/
}

void TitleScene::OnEnter()
{
}

void TitleScene::OnExit() 
{
	// m_ecs.DestroyAllEntities(); // here?
}