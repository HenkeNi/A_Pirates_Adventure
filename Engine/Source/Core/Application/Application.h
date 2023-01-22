#pragma once

namespace Hi_Engine
{
	class Application
	{
	public:
		virtual ~Application() = default;

		virtual void OnUpdate(float aDeltaTime)	= 0;
		virtual void OnRender()					= 0;

		virtual void OnCreate()					 {};
		virtual void OnDestroy()				 {};

	private:

	};


	Application* CreateApplication();
}