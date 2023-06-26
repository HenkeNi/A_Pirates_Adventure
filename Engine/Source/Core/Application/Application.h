#pragma once

namespace Hi_Engine
{
	class Application
	{
	public:
		virtual ~Application() = default;

		virtual void OnUpdate(float aDeltaTime)		= 0;
		virtual void OnLateUpdate(float aDeltaTime)	= 0;
		virtual void OnDraw()						= 0;

		virtual void OnCreate()						 {};
		virtual void OnDestroy()					 {};
	};


	// Application* CreateApplication();
}