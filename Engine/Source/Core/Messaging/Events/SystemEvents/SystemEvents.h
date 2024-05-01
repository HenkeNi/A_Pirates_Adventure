#pragma once
#include "../Event.h"
#include "../../../../Data/Enumerations.h"


namespace Hi_Engine
{
	using namespace Math;

	class TerminationEvent : public Event<TerminationEvent>
	{
	public:
		TerminationEvent();

		void					Init();
		void					Dispatch(EventListener& listener)		  override;
		ePriority				GetPriority()						const override;
		bool					IsHandled()							const override;
		void					Reset()									  override;

	private:
	};

	class WindowEvent : public Event<WindowEvent>
	{
	public:
		WindowEvent();			// Overload new operatp`?? placement new?? 
		~WindowEvent()										override;

		void			Dispatch(EventListener& listener)	override;	// Put in base class?
		void			Reset()								override;
		void			Init(eWindowEvent type);

		eWindowEvent	GetEventType()						   const;

	private:
		eWindowEvent	m_eventType;
		UVector2		m_windowSize;
	};


	
	class InputHandler;
	class InputEvent : public Event<InputEvent>
	{
	public:
		InputEvent();

		void				Dispatch(EventListener& listener)   override;
		void				Reset()								 override;

		eInputState			GetKeyState(eKey key)				    const;
		eInputState			GetMouseBtnState(eMouseBtn btn)			const;
		const glm::vec2&	GetMousePosition()						const;

	private:
		friend class InputHandler;

		std::unordered_map<eKey, eInputState>		m_keyStates;
		std::unordered_map<eMouseBtn, eInputState>	m_mouseButtonStates;
		glm::vec2									m_mousePosition;
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