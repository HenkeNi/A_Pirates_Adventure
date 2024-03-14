#pragma once
#include <Utility/Math/Vectors/Vector3.hpp>
#include "../Base/Component.h"

namespace CU = CommonUtilities;


// ############# Physics Components ############# //
struct TransformComponent : public Component
{
	CU::Vector2<float> CurrentPos   = { 0.f, 0.f };
	CU::Vector2<float> PreviousPos  = { 0.f, 0.f };	
	CU::Vector2<float> Scale		= { 1.f, 1.f };
	float			   Rotation		= 0.f;
};

struct VelocityComponent : public Component // Physics componetn instad?
{
	CU::Vector2<float>	Velocity;
	CU::Vector2<float>	Acceleration;
	//float DeaccelerationRate; TODO; implement instead of bool check? or put in physics? mass, etc?

	float				MaxVelocity;
	float				Speed;
	bool				ShouldSlowDown = true;
};

// Rename BoxColliderComponent (or RectangleComponent)
struct ColliderComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
	Offset								Offset;
	//CU::Vector2<float>				Offset;
	eColliderType						Type;
	//eCollisionLayer					Layer;

	// replace with collision data?! normal, entity colliding with, etc..
	std::vector<class Entity*>				CollidingEntities;

	// Store collision normal..

	// store size?
	//CollisionData CollisionData; // have as pointer?
	// bool								IsColliding;

	bool								IsActive; // ?? or just remove component?
};

struct CircleColliderComponent : public Component
{
};


// ############# Rendering Components ############# //
struct SpriteComponent : public Component
{
	Hi_Engine::Subtexture2D* Subtexture = nullptr;
	CU::Vector4<float> Color = { 1.f, 1.f, 1.f, 1.f };
	// Hi_Engine::Material m_material;	// Store strings instead?? keys..

	CU::Vector2<float> Pivot = { 0.5f, 1.f };// use a matrix instead? default: identify matrix?
	bool ShouldRender; 
	// int m_textureID; ?
	// int m_shaderID; ?
	// width, hight??
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

struct CameraComponent : public Component
{
	Hi_Engine::Camera	Camera;
	CU::Vector3<float>  TargetOffset;
	CU::Vector2<float>	ZoomRange;
	//class Entity*		m_target = nullptr;
	unsigned			TargetID = 0;

	bool ShouldCull = true;

	Hi_Engine::Physics::AABB2D<float> Frustum; 
};



// ############# Input Components ############# //

struct InputComponent : public Component
{
	//std::unordered_map<Hi_Engine::eKey, Hi_Engine::eInputState> InputStates; // replace with state instead of bool?? rename KeyStates?
	std::unordered_map<Hi_Engine::eKey, bool> InputStates; // replace with state instead of bool?? rename KeyStates?
	CU::Vector2<double>						  MousePosition;
	CU::Vector2<double>						  MouseWorldPosition;
	float									  MouseScroll;
};




struct BoundingVolume : public Component // Or BOundingBox?
{
	Hi_Engine::Physics::AABB2D<unsigned> Volume;
};


// Rename ChildEntitiesComponent? ChildListComponent
struct SubEntitiesComponent : public Component
{
	std::vector<unsigned> IDs;
};



// Rename BoundComponent?
struct FollowComponent : public Component
{
	unsigned EntityID = 0;
};


struct ClickableComponent : public Component
{

};

// Store current window size. etc...
struct SettingsComponent : public Component
{

};


struct LineComponent : public Component
{
	Hi_Engine::Physics::LineSegment2D<float> LineSegment;
};


struct SceneTransitionComponent : public Component
{
	enum class eScene SceneType;
};