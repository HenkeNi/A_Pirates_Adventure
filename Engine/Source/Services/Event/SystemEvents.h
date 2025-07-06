#pragma once
#include "Event.h"
#include "../Input/InputTypes.h"
// #include "Utility/Math/Vectors/Vector.hpp" // Remove? 
#include "Math/Vectors/Vector.hpp"

struct GLFWwindow;

namespace Hi_Engine
{
	//using namespace Math;

	/*
	enum class eWindowEvent;
	enum class eMouseBtn;
	enum class eInputState;
	enum class eKey;*/
	//enum class eInputState;

	class InputHandler;

	/* ########################## Termination Event ########################## */
	class TerminationEvent : public Event<TerminationEvent>
	{
	public:
		TerminationEvent();

		//void Dispatch(EventListener& listener) override;

	private:
	};

	// find better name: 
	class ServiceEvent : public Event<ServiceEvent>
	{
	public:
		ServiceEvent();

		//void Dispatch(EventListener& listener) override;

	private:
		// IService* m_
	};

	/* ########################## Window Event ########################## */
	enum class eWindowEvent
	{
		None,
		Created,
		Resize,
		LostFocus,
		GainedFocus,
		Close
	};

	class WindowEvent : public Event<WindowEvent>
	{
	public:
		WindowEvent();
		WindowEvent(eWindowEvent type, const IVector2& size, GLFWwindow* window);			// Overload new operatp`?? placement new?? 

		//void			Dispatch(EventListener& listener)	override;	// Put in base class?

		eWindowEvent	GetEventType()						   const;
		const IVector2& GetSize()							   const;
		inline GLFWwindow* GetWindow() { return m_window; }

	private:
		eWindowEvent	m_eventType;
		IVector2		m_windowSize;
		GLFWwindow*		m_window;
	};


	class WindowResizeRequestEvent;





	/* ########################## Input Event ########################## */
	class InputEvent : public Event<InputEvent>
	{
	public:
		InputEvent();
		InputEvent(const std::unordered_map<eKey, eInputState>& keyStates, 
			std::unordered_map<eMouseBtn, eInputState>& mouseButtonStates, const FVector2& mousePosition);

		//void				Dispatch(EventListener& listener)   override;

		eInputState			GetKeyState(eKey key)				    const;
		eInputState			GetMouseBtnState(eMouseBtn btn)			const;
		const FVector2&		GetMousePosition()						const;

	private:
		std::unordered_map<eKey, eInputState>		m_keyStates;
		std::unordered_map<eMouseBtn, eInputState>	m_mouseButtonStates;
		FVector2									m_mousePosition;
	};

	/*class KeyEvent : public Event
	{
	public:
		KeyEvent();
		KeyEvent(eInputState aState, int aCode);
		~KeyEvent();

		void		Dispatch(EventListener& aListener)   override;
		void		Destroy()							 override;
		void		Clean()								 override;
		void		Init(eInputState aState, int aCode);

		eInputState	GetKeyState()						    const;
		int			GetKeyCode()						    const;

	private:
		eInputState	m_keyState;
		int			m_keyCode;
	};*/



	// OR KEy mesage and mouse messag (current pos, last pos, maybe keypressed as well (rather tha having to listen for a key)) or combine it all and send a Input Event?
	// Maybe store relevant keys here as well??
	//class MouseEvent : public Event
	//{
	//public:
	//	MouseEvent();
	//	~MouseEvent();

	//	void	Dispatch(EventListener& aListener)	override;
	//	void	Destroy()							override;
	//	void	Clean()								override;
	//	void	Init(const CU::Vector2<unsigned>& aCurrentMousePos, const CU::Vector2<unsigned>& aPrevMousePos);

	//	const CU::Vector2<unsigned>& GetCurrentMousePos() const;

	//private:
	//	// Store under struct MouseData??
	//	CU::Vector2<unsigned>	m_currMousePos, m_prevMousePos;
	//	bool					m_leftMouseCliked; // STATE? Clicked, Held, Releasd?	map for different buttons??
	//};

}