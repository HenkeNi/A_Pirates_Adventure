#include "Pch.h"
#include "TitleScene.h"
#include "SceneParser.h"

#define DEFAULT_DURATION 2.3f 

TitleScene::TitleScene(SceneManagerProxy aProxy)
	: Scene{ aProxy }, m_duration{ DEFAULT_DURATION }, m_elapsedTime{ 0.f }
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
	SceneParser::ParseScene("Title", *this);
}

void TitleScene::OnExit()
{
}
