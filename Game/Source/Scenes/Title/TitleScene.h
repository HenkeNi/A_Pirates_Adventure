#pragma once
#include "../Scene.h"


#include "../World/Map/Map.h"


class TitleScene : public Scene, public Hi_Engine::EventListener
{
public:
	TitleScene(SceneManagerProxy aProxy);
	~TitleScene();

	void			Init(rapidjson::Value& aValue)				override;
	void			HandleEvent(Hi_Engine::KeyEvent& anEvent)   override;
	void			Update(float aDeltaTime)					override;
	void			LateUpdate(float aDeltaTime)				override;
	void			Draw()								  const override;

	void			OnCreated()									override;
	void			OnEnter()									override;
	void			OnExit()									override;


private:
	float			m_duration, m_elapsedTime; // register a time callback in a time manager isntead?!
	// store valid keycodes??

	// TEST
	Map m_map;	
};