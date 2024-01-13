#pragma once
#include <Utility/Math/Vectors/Vector3.hpp>
#include "../Base/Component.h"

namespace CU = CommonUtilities;

struct TransformComponent : public Component
{
	CU::Vector2<float> CurrentPos   = { 0.f, 0.f };
	CU::Vector2<float> PreviousPos  = { 0.f, 0.f };	
	CU::Vector2<float> Scale		= { 1.f, 1.f };
	float			   Rotation		= 0.f;
};

struct VelocityComponent : public Component
{
	CU::Vector2<float>	Velocity;
	CU::Vector2<float>	Acceleration;

	float				MaxVelocity;
	float				Speed;
};


// ########################## Rendering ########################## // 
struct SpriteComponent : public Component
{
	Hi_Engine::Subtexture2D* Subtexture = nullptr;
	CU::Vector4<float> Color = { 1.f, 1.f, 1.f, 1.f };
	// Hi_Engine::Material m_material;	// Store strings instead?? keys..

	CU::Vector2<float> Pivot = { 0.5f, 1.f };

	// int m_textureID; ?
	// int m_shaderID; ?
	// width, hight??
};

struct InputComponent : public Component
{
	std::unordered_map<Hi_Engine::eKey, bool> InputStates; // replace with state instead of bool??
	CU::Vector2<double>						  MousePosition;
	float									  MouseScroll;
};

struct TextComponent : public Component
{
	class Hi_Engine::Font* Font;
	std::string				Text;
	unsigned				Size = 32;
	//Hi_Engine::Shader*	Shader;
	//Hi_Engine::Font*	Font;
	// float				m_scale; use transform instead..
	CU::Vector4<float>		Color;
};

struct AnimationComponent : public Component
{
	std::unordered_map<std::string, Animation>	Animations;	// replace with Array?? or enum for key?
	std::string									Active;		// index instead??




	// store default??

	/*std::string m_identifier;
	std::vector<std::string> m_animations;
	unsigned	m_totalFrames;
	unsigned	m_currentFrame;
	float		m_frameDuration;
	float		m_elapsedFrameTime;
	bool		m_isPlaying;
	bool		m_isLooping;*/
};

struct CameraComponent : public Component
{
	Hi_Engine::Camera	Camera;
	CU::Vector3<float>  TargetOffset;
	CU::Vector2<float>	ZoomRange;
	//class Entity*		m_target = nullptr;
	unsigned			TargetID = 0;
};





struct DebugRectComponent : public Component
{
	Hi_Engine::Shader* Shader;
	CU::Vector4<float> Color;
};



// Rename? PrimitiveRect or DebugRect? 
struct RectComponent : public Component
{
	Hi_Engine::Shader* Shader;
	CU::Vector4<float> Color;
};


struct LineComponent : public Component
{
	Hi_Engine::Physics::LineSegment2D<float> LineSegment;
};






struct CollisionComponent : public Component
{

	bool IsTrigger;
};

struct ColliderComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
	CU::Vector2<float>					Offset;
	eCollisionLayer						Layer;
	bool								IsStatic;					// enum for type (trigger, static?
};




// inherit from ColliderComponent?
struct RectangleColliderComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
	bool								IsStatic;
	// isTrigger?
};

struct CircleColliderComponent : public Component
{
};

struct TriggerComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
};
