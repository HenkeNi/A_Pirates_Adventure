#pragma once
#include "Data/Enumerations.h"

// Command pattern??
// Don't have bool isKeyPressed functions... (do with events instead....) -> works better later when implememnting controll support...

namespace Hi_Engine
{
	class Command;
	struct GLFWwindow;

	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void Init();
		void ProcessInput();
		void MapCommand(eInputType aType, Command* aCommand);	// Rename: Map or bInd?

		static void			KeyCallback(GLFWwindow* aWindow, int aKey, int aScanCode, int anAction, int someMods);
		static eInputState	GetKeyState(int aKey);


	private:
		static std::unordered_map<eInputType, eInputState> s_inputStates;
		// previous input state??

		//std::unordered_map<eInputType, std::unique_ptr<Command>> m_inputCommands;	// array of commands?? reanme just commands??

		// std::unordered_map<eInputType, eAction>	// Map input (keys) to events/actions (window resized, etc..)
	};
}