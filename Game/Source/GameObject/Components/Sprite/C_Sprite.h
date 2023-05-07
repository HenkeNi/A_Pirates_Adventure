#pragma once
#include "../Component.h"

class C_Transform;
class Hi_Engine::Texture2D;


// Make Renderer(s) static or singleton??
// Add render data?? => add to a queue? => gets sorted? 
// Or make call to engine to render?? 

// Or sprite is an engine thing??
class C_Sprite : public Component
{
public:
	C_Sprite(GameObject* anOwner = nullptr);
	~C_Sprite();

	void						Init(rapidjson::Value& aValue)				override;
	void						HandleMessage(CompMessage aMessage)		override;
	void						Update(float aDeltaTime)					override;
	void						Draw()								  const override;
	void						OnActivate()								override;
	C_Sprite*					Copy()								  const override;


	// REMOVE LATER
	void SetTexture(Hi_Engine::Texture2D* aTexture)
	{
		m_texture = aTexture;
	}

private:
	CU::Vector4<float>			m_color;
	C_Transform*				m_transform;
	//std::weak_ptr<C_Transform>	m_transform;
	Hi_Engine::Texture2D*		m_texture;
	// SpriteRenderer*   => or make singleton??

	// Region/View that should be rendered...

};