#pragma once
#include "../Base/Component.h"
#include <../Hi_Engine.h>


struct TagComponent : public Component
{
	enum class eEntityType
	{
		Player,
		Enemy,
		NPC,
		UI,
		Collectable,
		Environment,
		Camera
	};

	eEntityType type;
};


// ############# Physics Components ############# //
struct TransformComponent : public Component
{
	FVector2 CurrentPos		= { 0.f, 0.f };
	FVector2 PreviousPos	= { 0.f, 0.f };
	FVector2 Scale			= { 1.f, 1.f }; // rename size?
	FVector2 Pivot			= { 0.f, 0.f }; // Rename origin?
	float    Rotation		= 0.f;
};

struct VelocityComponent : public Component
{
	FVector2 Velocity;
	float	 Speed = 1.f;
	bool	 IsVelocityConstant = false;
};

// Rename BoxColliderComponent (or RectangleComponent)
struct ColliderComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
	Offset								Offset;
	//FVector2				Offset;
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
	FVector4					DefaultColor = { 1.f, 1.f, 1.f, 1.f };
	FVector4					CurrentColor = { 1.f, 1.f, 1.f, 1.f };
	Hi_Engine::Subtexture2D*	Subtexture	 = nullptr; // Store as int (id) instead?
	bool						ShouldRender = true;
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
	std::string				  Text;
	FVector4				  Color;
	unsigned				  Size = 32;
	Hi_Engine::eTextAlginment Alignment;
	class Hi_Engine::Font*    Font = nullptr;
};

struct CameraComponent : public Component
{
	Hi_Engine::Camera Camera;
 	FVector2					TargetOffset;
	Hi_Engine::Physics::AABB2D<float> Frustum;
	Hi_Engine::Range<float>	ZoomRange;

	unsigned			TargetID = 0;

	bool ShouldCull = true;
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
	std::unordered_map<eMessage, std::string> SoundTriggers; 
	
	// std::string AudioName; // REmove?

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