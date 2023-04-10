#pragma once
#include "../Event.h"
#include "Data/Enumerations.h"


namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class WindowEvent : public Event
	{
	public:
		WindowEvent();			// Overload new operatp`?? placement new?? 
		~WindowEvent();

		void					Dispatch(EventListener& aListener)	override;
		void					Destroy()							override;
		void					Init(eWindowEvent aType);

		eWindowEvent			GetEventType()						   const;

	private:
		eWindowEvent			m_eventType;
		CU::Vector2<unsigned>	m_windowSize;
	};



	class KeyEvent : public Event
	{
	public:
		KeyEvent();
		~KeyEvent();

		void		Dispatch(EventListener& aListener)   override;
		void		Destroy()							 override;
		void		Init(eKeyState aState, int aCode);

		eKeyState	GetKeyState()						    const;
		int			GetKeyCode()						    const;

	private:
		eKeyState	m_keyState;
		int			m_keyCode;
	};



	// OR KEy mesage and mouse messag (current pos, last pos, maybe keypressed as well (rather tha having to listen for a key)) or combine it all and send a Input Event?
	// Maybe store relevant keys here as well??
	class MouseEvent : public Event
	{
	public:
		MouseEvent();
		~MouseEvent();

		void	Dispatch(EventListener& aListener)	override;
		void	Destroy()							override;
		void	Init(const CU::Vector2<unsigned>& aCurrentMousePos, const CU::Vector2<unsigned>& aPrevMousePos);

		const CU::Vector2<unsigned>& GetCurrentMousePos() const;

	private:
		// Store under struct MouseData??
		CU::Vector2<unsigned>	m_currMousePos, m_prevMousePos;
		bool					m_leftMouseCliked; // STATE? Clicked, Held, Releasd?	map for different buttons??
	};

}