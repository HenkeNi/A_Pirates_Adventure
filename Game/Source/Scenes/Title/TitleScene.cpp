#include "Pch.h"
#include "TitleScene.h"


TitleScene::TitleScene(SharedContext aContext)
	: Scene{ aContext }
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float aDeltaTime) {}

void TitleScene::LateUpdate(float aDeltaTime) {}

void TitleScene::Draw() const
{
}

//void TitleScene::Draw() const {}

void TitleScene::OnCreated()
{
	// TODO; Register for events...
}

void TitleScene::OnEnter()
{
	// TODO; Load in new entities...
}

void TitleScene::OnExit() 
{
	// TODO; Clear entities...
}