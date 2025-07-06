#pragma once
#include "../../Services/Rendering/Camera.h"
#include "../Core/Math/Geometry/AABB2D.hpp"
#include "../Core/Math/Range/Range.hpp"

#include "Utility/JsonUtils.h" // used for PropertyValue...

namespace Hi_Engine
{
	struct TransformComponent
	{
		FVector2 Position	= { 0.f, 0.f };
		FVector2 Scale		= { 1.f, 1.f };
		FVector2 Pivot		= { 0.f, 0.f };
		float	 Rotation   = 0.f;
	};

	struct VelocityComponent
	{
		FVector2 Velocity;
		float	 BaseSpeed = 1.f;
		float	 CurrentSpeed = 1.f;
		float	 SpeedMultiplier = 1.f;
		float	 SpeedReductionRate = 20.f;  // rename...
		bool	 IsVelocityConstant = false; // Dont? use physics instead?
	};

	struct CameraComponent // TODO; store camera data intead of camera!
	{
		Camera					 Camera; // eplace with camera data... (projection matrix etc...
		FVector2				 TargetOffset;
		Geometry::AABB2D<float>  Frustum;
		Math::Range<float>			 ZoomRange;

		//Entity			Target = 0;
		int 			Target = 0;

		bool ShouldCull = true;
		bool IsActive = true; // fix, default to false
	};

	struct TextureData
	{
		std::string TextureID;
		IVector2 Coordinates;
	};

	struct SpriteComponent
	{
	/*	SpriteComponent(std::shared_ptr<class Subtexture2D> subtexture = nullptr)
			: Subtexture{ subtexture }
		{
		}*/

		FVector4					DefaultColor = { 1.f, 1.f, 1.f, 1.f };
		FVector4					CurrentColor = { 1.f, 1.f, 1.f, 1.f };
		//std::shared_ptr<class Subtexture2D>	Subtexture = nullptr; // store id instead? and CachedSubtexture?
		TextureData TextureData;
		int							RenderDepth = 0; // remove? moved to uicomponent
		bool						IsVisible = true;
	};

	struct UIComponent
	{
		//std::shared_ptr<class Subtexture2D>	Subtexture = nullptr;
		//TextureData TextureData;
		//FVector4					DefaultColor = { 1.f, 1.f, 1.f, 1.f };
		//FVector4					CurrentColor = { 1.f, 1.f, 1.f, 1.f };
		//int							RenderDepth = 0;
		//bool						IsVisible = true;
	};

	/*struct UIRenderComponent
	{};*/

	struct InputComponent
	{
		std::unordered_map<Hi_Engine::eKey, bool> InputStates; // replace with state instead of bool?? rename KeyStates?
		FVector2 MousePosition;
		FVector2 MouseWorldPosition;
		float MouseScroll;
	};

	struct AudioComponent
	{

	};

	struct TagComponent
	{

	};

	// Maybe rename?
	struct EventTrigger
	{
		std::string EventName;
		std::unordered_map<std::string, PropertyValue> Params;
	};

	struct EventTriggerComponent
	{
		std::vector<EventTrigger> Triggers;
	};


	struct TimerComponent
	{
		EventTrigger OnCompleted; // optional?
		// std::function<void(int entity)> Callback; //  - dont allow non trivial data`? store id to callback insteaD?

		float Duration = 0.f;
		float ElapsedTime = 0.f;

		bool IsDone = false; // or remove afterwards?
	};

	

	
	
	struct TextComponent
	{};

	//struct SceneTransitionComponent
	//{};

	//struct HierarchyComponent
	//{
	//	Entity Parent;
	// 
	// };
}