#include "Pch.h"
#include "TitleScene.h"


TitleScene::TitleScene(SceneManagerProxy aProxy)
	: Scene{ aProxy } 
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init(rapidjson::Value& aValue)
{
}

void TitleScene::Update(float aDeltaTime)
{
	for (auto& object : m_objectManager.GetAllObjects())
		object.Update(aDeltaTime);
}

void TitleScene::LateUpdate(float aDeltaTime) {}

void TitleScene::Draw() const
{
	{
		//Hi_Engine::SpriteRenderer::GetInstance().BeginRendering(m_mainCamera); // put in engine?? r keep here an rename beignscene
		// store/caclutate camera transform??
	}

	// Todo; pass in a SceneCamera?? or just the transform (view matrix only change once per frame - no need to calcualte it more times) ??
	// const auto& Sprite

	for (auto& object : m_objectManager.GetAllObjects())
		object.Draw();
}

void TitleScene::OnCreated()
{
	// m_sceneObjects = SceneFactory::GetInstance().CreateFromBlueprint("Title");
}

void TitleScene::OnEnter()
{
	// TODO: Load in objects again?? or reset them??

	for (auto& object : m_objectManager.GetAllObjects())
		object.Activate();
}

void TitleScene::OnExit()
{
	for (auto& object : m_objectManager.GetAllObjects())
		object.Deactivate();


	//  delete all objects... (empty object manager)...
}