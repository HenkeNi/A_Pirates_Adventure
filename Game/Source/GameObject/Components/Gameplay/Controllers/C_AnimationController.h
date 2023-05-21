#pragma once
#include "../../Component.h"


enum class eState // reanme... (maybe dont use this enum??)
{
	Idle,
	Walk,
	Run,
	Attack
};


// Reanem SpriteAnimaitonController`??
class C_AnimationController : public Component
{
public:
	C_AnimationController();
	~C_AnimationController();

private:

	// store keyframes => notifys other components when hit...

	unsigned m_currentFrame;
	unsigned	m_numberOfFrames; //vec2 instead??
	bool		m_isLooping;
};