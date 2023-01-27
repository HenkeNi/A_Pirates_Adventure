#include "Pch.h"
#include "TitleScene.h"


TitleScene::TitleScene(SceneManagerProxy aProxy)
	: Scene{ aProxy }
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float aDeltaTime)
{
	std::cout << "UPDATING TITLE SCENE\n";
}

void TitleScene::LateUpdate(float aDeltaTime)
{
}

void TitleScene::Draw() const
{
}

void TitleScene::OnCreated()
{
	int x = 10;
	x += 20;
}

void TitleScene::OnEnter()
{
}

void TitleScene::OnExit()
{
}
