#pragma once
#include "../../Rendering/Camera/Camera.h"
#include "../Core/Math/Geometry/AABB2D.hpp"
#include "../Core/Math/Range/Range.hpp"

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

	struct CameraComponent
	{
		Camera					 Camera;
		FVector2				 TargetOffset;
		Geometry::AABB2D<float>  Frustum;
		Math::Range<float>			 ZoomRange;

		//Entity			Target = 0;
		int 			Target = 0;

		bool ShouldCull = true;
		bool IsActive = true; // fix, default to false
	};

	struct SpriteComponent
	{
		FVector4					DefaultColor = { 1.f, 1.f, 1.f, 1.f };
		FVector4					CurrentColor = { 1.f, 1.f, 1.f, 1.f };
		std::shared_ptr<class Subtexture2D>	Subtexture = nullptr;
		int							RenderDepth = 0; // remove? moved to uicomponent
		bool						IsVisible = true;
	};

	struct UIComponent
	{
		std::shared_ptr<class Subtexture2D>	Subtexture = nullptr;
		FVector4					DefaultColor = { 1.f, 1.f, 1.f, 1.f };
		FVector4					CurrentColor = { 1.f, 1.f, 1.f, 1.f };
		int							RenderDepth = 0;
		bool						IsVisible = true;
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

	struct TimerComponent
	{
		std::function<void(int entity)> Callback;
		float Duration = 0.f;
		float ElapsedTime = 0.f;

		bool IsDone = false; // or remove afterwards?
	};

	//struct HierarchyComponent
	//{
	//	Entity Parent;
	// 
	// };
}