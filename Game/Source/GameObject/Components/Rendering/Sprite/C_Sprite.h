#pragma once
#include "../../Component.h"

class C_Transform;

using Material = Hi_Engine::Material;

// Make billboard component??
// TODO; Region/View that should be rendered...
// Make sprite an engine thing??... pass in camera on draw??
class C_Sprite : public Component
{
public:
	C_Sprite(GameObject* anOwner = nullptr);
	~C_Sprite();

	void			Init(rapidjson::Value& aValue)			override;	
	void			HandleMessage(const CompMessage& aMsg)	override;
	void			Update(float aDeltaTime)				override;
	void			Draw()							  const override;
	void			OnActivate()							override;
	C_Sprite*		Copy()							  const override;

	void			SetMaterial(const Material& aMaterial);
	const Material&	GetMaterial()							   const;

private:
	C_Transform*	m_transform;	// replace with weak_ptr??
	Material		m_material;		// Make into pointer instead? make const?
};