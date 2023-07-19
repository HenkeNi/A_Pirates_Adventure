#pragma once
#include "Base/System.h"


class PrimitiveRenderSystem : public System
{
public:
	PrimitiveRenderSystem();
	~PrimitiveRenderSystem();

	void Receive(Message& aMsg)	override;
	void Draw()					override;

private:
	Hi_Engine::Shader* m_shader;	// Needed??
};