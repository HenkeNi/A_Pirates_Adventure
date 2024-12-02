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
	//FVector2 WorldPosition = { 0.f, 0.f };
	//FVector2 LocalPosition = { 0.f, 0.f };

	FVector2 CurrentPos		= { 0.f, 0.f };
	FVector2 PreviousPos	= { 0.f, 0.f };
	FVector2 Scale			= { 1.f, 1.f }; // rename size?
	FVector2 Pivot			= { 0.f, 0.f }; // Rename origin?
	float    Rotation		= 0.f;
};


struct PhysicsComponent
{
	Hi_Engine::PhysicsBody PhysicsBody;

//#ifdef DEBUG

	FVector2 ColliderSize = { 0.f, 0.f };
	//FVector2 ColliderOffset = { 0.f, 0.f }; offset in sprite instead?

//#endif // DEBUG

	// FVector2 Velocity;
	float Density = 0.f;
	float Friction = 0.f;
	eColliderType Type;

	// offset?
};


// rename MovementComponent?
struct VelocityComponent
{
	FVector2 Velocity;
	float	 BaseSpeed = 1.f;
	float	 CurrentSpeed = 1.f;
	float	 SpeedMultiplier = 1.f;
	float SpeedReductionRate = 20.f; // rename...
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
	std::shared_ptr<Hi_Engine::Subtexture2D>	Subtexture	 = nullptr; // Store as int (id) instead?
	int							RenderDepth  = 0; // remove? moved to uicomponent
	bool						IsVisible	 = true;
};

enum class eState;

struct AnimationComponent
{
	struct Frame
	{
		int Row; // make unsigned?
		int Col;
		float Duration;
	};

	struct Animation
	{
		std::vector<Frame> Frames;
		int CurrentFrameIndex = 0;
		bool IsLooping = false;
	};

	std::unordered_map<eState, Animation> Animations;
	std::string TextureID;
	
	eState ActiveAnimation;
	eState DefaultAnimation;
	float ElapsedFrameTime = 0.f;
};

struct TextComponent
{
	std::string				  Text;
	FVector4				  Color;
	unsigned				  Size = 32;
	Hi_Engine::eTextAlginment Alignment;
	std::shared_ptr<class Hi_Engine::Font>    Font = nullptr;
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
	FVector2 MousePosition;
	FVector2 MouseWorldPosition;
	float MouseScroll;
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
//struct FollowComponent
//{
//	unsigned EntityID = 0;
//};

// interactable component?
struct ClickableComponent
{
	Hi_Engine::Physics::AABB2D<float> Bounds;

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