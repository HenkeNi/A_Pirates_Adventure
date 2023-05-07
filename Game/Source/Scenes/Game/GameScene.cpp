#include "Pch.h"
#include "GameScene.h"


GameScene::GameScene(SceneManagerProxy aProxy)
	: Scene{ aProxy }
{
}

GameScene::~GameScene()
{
}

void GameScene::Init(rapidjson::Value& aValue)
{
	auto type = aValue["type"].GetString();

	static int ax = 10;

}

void GameScene::Update(float aDeltaTime)
{
}

void GameScene::LateUpdate(float aDeltaTime)
{
}

void GameScene::Draw() const
{
}

void GameScene::OnEnter()
{
}

void GameScene::OnExit()
{
}