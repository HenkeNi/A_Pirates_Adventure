#pragma once
//#include <Utility/Math/Vectors/Vector3.hpp>
//#include <../Engine/Source/Utility/Math/Vectors/Vector3.hpp> // ?
#include <../Hi_Engine.h>

#include "../Base/Component.h"



// ############# Physics Components ############# //
struct TransformComponent : public Component
{
	FVector2 CurrentPos		= { 0.f, 0.f };
	FVector2 PreviousPos	= { 0.f, 0.f };
	FVector2 Scale			= { 1.f, 1.f };
	FVector2 Pivot			= { 0.f, 0.f }; // Rename origin?
	float    Rotation		= 0.f;
};

struct VelocityComponent : public Component // Physics componetn instad?
{
	FVector2 Velocity;
	FVector2 Acceleration;
	//float DeaccelerationRate; TODO; implement instead of bool check? or put in physics? mass, etc?

	float	MaxVelocity;
	float	Speed;
	bool	ShouldSlowDown = true;
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
	//CollisionData						CollisionData; // have as pointer?
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
	FVector4 Color = { 1.f, 1.f, 1.f, 1.f };
	// CU::Vector4<float> DefaultColor = { 1.f, 1.f, 1.f, 1.f };
	FVector4 CurrentColor = { 1.f, 1.f, 1.f, 1.f };

	// TINT????

	// Hi_Engine::Material m_material;	// Store strings instead?? keys..

	// Store temporary color, or alterantive color? or fix by having a component?

	// CU::Vector2<float> Pivot; //  = { 0.5f, 0.5f };// use a matrix instead? default: identify matrix? rename Origin?
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
	//Hi_Engine::GLSLShader*	GLSLShader;
	//Hi_Engine::Font*	Font;
	// float				m_scale; use transform instead..
	FVector4		Color;
	Hi_Engine::eTextAlginment Alignment;
};

struct CameraComponent : public Component
{
	Hi_Engine::Camera			Camera;
 	FVector2					TargetOffset;
	Hi_Engine::Range<float>	ZoomRange;
	//class Entity*		m_target = nullptr;
	unsigned			TargetID = 0;

	bool ShouldCull = true;

	Hi_Engine::Physics::AABB2D<float> Frustum;
};

// NEEDED??
struct ColorComponent : public Component
{
	Color CurrentColor;
	Color DefaultColor;
};


// ############# Input Components ############# //

struct InputComponent : public Component
{
	//std::unordered_map<Hi_Engine::eKey, Hi_Engine::eInputState> InputStates; // replace with state instead of bool?? rename KeyStates?
	std::unordered_map<Hi_Engine::eKey, bool> InputStates; // replace with state instead of bool?? rename KeyStates?
	FVector2									MousePosition;
	FVector2									MouseWorldPosition;
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

// interactable component?
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
	enum class eScene SceneType; // Scene to transition to
	bool IsActive = true;
	bool ShouldPush = true;

	bool ShouldTransition = false;
};



// ############# Audio Components ############# //
struct AudioComponent : public Component
{
	std::unordered_map<eMessage, Hi_Engine::Audio> AudioTriggers; // TODO; store sounds when doing something "bad", like trying to mine with an axe -> "AttackFailed" as key?

	Hi_Engine::Audio Audio;				// Store array of sounds? with key that determines when it should play
	bool IsLooping = false;
	bool ShouldPlay = false;
};

// audio component, audio settings component, etc







struct DestinationComponent : public Component
{
	FVector2 Destination;
	float ArriveRadius = 0.5f;
	// TODO: store path? (tiles -> pathfinding)?
};

struct TargetComponent : public Component
{
	unsigned TargetID;
	class Entity* Target; // use instead?? make sure some system sets it to nullptr if entity is killed! -> maybe wont work?
};