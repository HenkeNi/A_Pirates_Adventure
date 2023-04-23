#pragma once
#include "../Scene.h"


// Derive MainMenuScene from MenuScene??
class MenuScene : public Scene
{
public:
	MenuScene(SceneManagerProxy aProxy);
	~MenuScene();

	//void			Init(rapidjson::Value& aValue)		  override;
	void			Update(float aDeltaTime)			  override;
	void			LateUpdate(float aDeltaTime)		  override;
	void			Draw()							const override;

	void			OnEnter()							  override;	// LOad from json OnEnter() => or on Created... 
	void			OnExit()							  override;	// emoty everyting here?

	// void RegisterCallback()?? or Hardcode in OnCreated()??

private:
	//std::unordered_map<std::function<void()>, std::string> m_callbacks; // ??  Store callbacks here?? -> use int/enum instead??
};

