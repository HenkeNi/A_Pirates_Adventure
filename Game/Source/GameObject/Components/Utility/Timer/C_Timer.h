#pragma once
#include "../../Component.h"
#include "../Data/Structs.h"

// TODO; add a struct for elapsed time and duration?? 
class C_Timer : public Component
{
public:
	C_Timer(GameObject* anOwner = nullptr);
	~C_Timer();

	void		Init(rapidjson::Value& aValue)			override;
	void		HandleMessage(const CompMessage& aMsg)	override;
	void		Update(float aDeltaTime)				override;

	void		OnActivate()							override;
	void		OnDeactivate()							override;
	C_Timer*	Copy()							  const override;

	void		SetTimer(const Timer& aTimer);
	void		Reset();

private:
	Timer		m_timer;
	bool		m_isRunning;
};