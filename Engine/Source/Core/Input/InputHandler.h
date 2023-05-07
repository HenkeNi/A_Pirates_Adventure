#pragma once
#include "Data/Enumerations.h"
#include <GLFW/glfw3.h> // FIX...

// Don't have bool isKeyPressed functions... (do with events instead....) -> works better later when implememnting controll support...

// TODO: Separete between key and joystick?? => use GLFW_KEY as key in map instead???
// TODO; make singleton?? or figure out best way for Game to be able to communicate with input handler...

namespace Hi_Engine
{
	class Command;

	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void				Init();
		void				ProcessInput();
		void				ProcessCommands();		// ??
		void				ClearCommands();
		
		static void			KeyCallback(GLFWwindow* aWindow, int aKey, int aScanCode, int anAction, int someMods);
		static void			MapCommand(eInputType anInput, Command* aCommand);	// Rename: Map or bInd? RegisterCommand?? 
		static bool			IsKeyPressed(eInputType anInput);
		static bool			IsKeyHeld(eInputType anInput);
		static bool			IsKeyReleased(eInputType anInput);

	private:
		static eInputState	GetKeyState(int anAction);	// renaem GetInputState??
		
		bool				IsCommandMapped(eInputType anInput) const;
		void				SendEvent(eInputType anInput);

		static std::unordered_map<eInputType, eInputState>	s_inputStates;	// Store previous input as well? mappedInput mappedInputStates
		static std::unordered_map<eInputType, Command*>		s_mappedCommands; // or just commands?
	};
}


// have input handler return Commands instead => command takes in a GameObject or a C_Controller... 
// AI simply emits commands... 

//Command* command = inputHandler.handleInput();
//if (command)
//{
//	command->execute(actor);
//}