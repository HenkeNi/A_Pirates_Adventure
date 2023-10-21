#pragma once
//#include "Data/Enumerations.h"
#include "../../Data/Enumerations.h"
#include <unordered_map>
//#include "../Data/Enumerations.h"
//#include <GLFW/glfw3.h> // FIX...

// Don't have bool isKeyPressed functions... (do with events instead....) -> works better later when implememnting controll support...

// TODO: Separete between key and joystick?? => use GLFW_KEY as key in map instead???
// TODO; make singleton?? or figure out best way for Game to be able to communicate with input handler...

struct GLFWwindow;	// NEEDED??

namespace Hi_Engine
{
	class Command;

	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void				Init(GLFWwindow* aWindow);
		void				ProcessInput();

		static void			KeyCallback(GLFWwindow* aWindow, int aKey, int aScanCode, int anAction, int someMods);
		static void			MouseButtonCallback(GLFWwindow* window, int aButton, int anAction, int someMods);
		static void			CursorCallback(GLFWwindow* aWindow, double xPos, double yPos);

		static glm::vec2	GetMousePosition();
		static bool			IsKeyPressed(eKey aKey);
		static bool			IsKeyHeld(eKey aKey);
		static bool			IsKeyReleased(eKey aKey);

	private:
		// static eInputState	GetKeyState(int anAction);	// renaem GetInputState??
		
		// bool				IsCommandMapped(eInputType anInput) const;
		// void				SendMessage(eInputType anInput);

		//static std::unordered_map<eInputType, eInputState>	s_inputStates;	// Store previous input as well? mappedInput mappedInputStates
	
		static std::unordered_map<eKey, eInputState>		s_keyStates;
		static std::unordered_map<eMouseBtn, eInputState>	s_mouseButtonStates;
		static glm::vec2									s_mousePosition;

		const GLFWwindow*									m_window;
		// static std::unordered_map<eInputType, Command*>		s_mappedCommands; // or just commands?
	
	
	
	};
}


// have input handler return Commands instead => command takes in a GameObject or a C_Controller... 
// AI simply emits commands... 
