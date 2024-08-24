#pragma once
#include <../Hi_Engine.h>
#include "ECSTypes.h"


struct TagComponent
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

	eEntityType Type;
};


// ############# Physics Components ############# //
struct TransformComponent
{
	FVector2 CurrentPos		= { 0.f, 0.f };
	FVector2 PreviousPos	= { 0.f, 0.f };
	FVector2 Scale			= { 1.f, 1.f }; // rename size?
	FVector2 Pivot			= { 0.f, 0.f }; // Rename origin?
	float    Rotation		= 0.f;
};


struct PhysicsComponent
{
	Hi_Engine::PhysicsBody PhysicsBody;
	FVector2 Velocity;
	float Density = 0.f;
	float Friction = 0.f;
	eColliderType Type;

	// offset?
};


// rename MovementComponent?
struct VelocityComponent
{
	FVector2 Velocity;
	float	 Speed = 1.f; 
	bool	 IsVelocityConstant = false; // Dont? use physics instead?
};


struct BoundingBoxComponent
{
	Hi_Engine::Physics::AABB2D<float> Bounds;
	Offset Offset;
};








// Rename BoxColliderComponent (or RectangleComponent)
struct ColliderComponent
{
	Hi_Engine::PhysicsBody PhysicsBody;
	//Hi_Engine::BoxCollider BoxCollider;

	Hi_Engine::Physics::AABB2D<float>	Collider;
	Offset								Offset;
	//FVector2				Offset;
	eColliderType						Type;
	//eCollisionLayer					Layer;

	// replace with collision data?! normal, entity colliding with, etc..
	std::vector<Entity>				CollidingEntities;

	// Store collision normal..

	// store size?
	//CollisionData						CollisionData; // have as pointer?
	// bool								IsColliding;

	bool								IsActive = true; // ?? or just remove component?
};



// ############# Rendering Components ############# //
struct SpriteComponent
{
	FVector4					DefaultColor = { 1.f, 1.f, 1.f, 1.f };
	FVector4					CurrentColor = { 1.f, 1.f, 1.f, 1.f };
	Hi_Engine::Subtexture2D*	Subtexture	 = nullptr; // Store as int (id) instead?
	bool						IsVisible = true;
};

struct AnimationComponent
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

struct TextComponent
{
	std::string				  Text;
	FVector4				  Color;
	unsigned				  Size = 32;
	Hi_Engine::eTextAlginment Alignment;
	class Hi_Engine::Font*    Font = nullptr;
};

struct CameraComponent
{
	Hi_Engine::Camera Camera;
 	FVector2					TargetOffset;
	Hi_Engine::Physics::AABB2D<float> Frustum;
	Hi_Engine::Range<float>	ZoomRange;

	//Entity			Target = 0;
	int 			Target = 0;

	bool ShouldCull = true;
};

// NEEDED??
struct ColorComponent
{
	Color CurrentColor;
	Color DefaultColor;
};
// SpriteSheet component? (stores texture atlas, also holds current frame, etc...)
// Shadow component??


// ############# Input Components ############# //

struct InputComponent
{
	//std::unordered_map<Hi_Engine::eKey, Hi_Engine::eInputState> InputStates; // replace with state instead of bool?? rename KeyStates?
	std::unordered_map<Hi_Engine::eKey, bool> InputStates; // replace with state instead of bool?? rename KeyStates?
	FVector2									MousePosition;
	FVector2									MouseWorldPosition;
	float									  MouseScroll;
};




struct BoundingVolume // Or BOundingBox?
{
	Hi_Engine::Physics::AABB2D<unsigned> Volume;
};


// Rename ChildEntitiesComponent? ChildListComponent
struct SubEntitiesComponent
{
	std::vector<unsigned> IDs; // change to ENtity?
};



// Rename BoundComponent?
struct FollowComponent
{
	unsigned EntityID = 0;
};

// interactable component?
struct ClickableComponent
{

};

// Store current window size. etc...
struct SettingsComponent
{

};


struct LineComponent
{
	Hi_Engine::Physics::LineSegment2D<float> LineSegment;
};


struct SceneTransitionComponent
{
	enum class eScene SceneType; // Scene to transition to
	bool IsActive = true;
	// bool ShouldPush = true;

	bool ShouldTransition = false;
};



// ############# Audio Components ############# //
struct AudioComponent
{
	std::unordered_map<eMessage, std::string> SoundTriggers; 

	bool IsLooping = false;
	bool ShouldPlay = false;
};

// audio component, audio settings component, etc







struct DestinationComponent
{
	FVector2 Destination;
	float ArriveRadius = 0.5f;
	// TODO: store path? (tiles -> pathfinding)?
};

struct TargetComponent
{
	unsigned TargetID;
	int Target;
	//Entity Target;
	//class Entity* Target; // use instead?? make sure some system sets it to nullptr if entity is killed! -> maybe wont work?
};