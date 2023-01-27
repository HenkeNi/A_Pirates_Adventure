#pragma once


namespace Hi_Engine
{
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void Init();
		void ProcessInput();
		void MapEvent();


		// Command pattern??
		// Don't have bool isKeyPressed functions... (do with events instead....) -> works better later when implememnting controll support...
	};
}