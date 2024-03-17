#include "Pch.h"
#include "SystemEvents.h"
#include "../../Listener/EventListener.h"
#include "../../../../Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"

namespace Hi_Engine
{
#pragma region TERMINATION_EVENT

	TerminationEvent::TerminationEvent()
	{
	}

	void TerminationEvent::Init()
	{
	}

	void TerminationEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}

	ePriority TerminationEvent::GetPriority() const
	{
		return ePriority::High;
	}

	bool TerminationEvent::IsHandled() const
	{
		return false;
	}

	void TerminationEvent::Reset()
	{
	}

#pragma endregion TERMINATION_EVENT

#pragma region WINDOW_EVENT
	WindowEvent::WindowEvent()
		: Event{ ePriority::Moderate }, m_eventType{ eWindowEvent::None }, m_windowSize{ 0, 0 }
	{
	}

	WindowEvent::~WindowEvent()
	{
	}

	void WindowEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}

	void WindowEvent::Reset()
	{
	}
	
	void WindowEvent::Init(eWindowEvent type)
	{
		m_eventType = type;
		m_isHandled = false;
	}

	eWindowEvent WindowEvent::GetEventType() const
	{
		return m_eventType;
	}

#pragma endregion WINDOW_EVENT


#pragma region INPUT_EVENT

	InputEvent::InputEvent()
	{}

	/*InputEvent::InputEvent(const std::unordered_map<eKey, eInputState>& someKeyStates,
		const std::unordered_map<eMouseBtn, eInputState>& someMouseBtnStates,
		const glm::vec2& aMousePos)
		: m_keyStates{ someKeyStates }, m_mouseButtonStates{ someMouseBtnStates }, m_mousePosition{ aMousePos }
	{
	}*/

	void InputEvent::Dispatch(EventListener& listener) 
	{
		listener.HandleEvent(*this);
	}

	void InputEvent::Reset()
	{
	}

	eInputState InputEvent::GetKeyState(eKey key) const
	{
		if (m_keyStates.contains(key))
			return m_keyStates.at(key);

		return eInputState::Invalid;
	}
	
	eInputState InputEvent::GetMouseBtnState(eMouseBtn btn) const
	{
		if (m_mouseButtonStates.contains(btn))
			return m_mouseButtonStates.at(btn);
	}

	const glm::vec2& InputEvent::GetMousePosition() const
	{
		return m_mousePosition;
	}

#pragma endregion INPUT_EVENT


#pragma region KEY_EVENT

	/*KeyEvent::KeyEvent()
		: Event{ ePriority::High }, m_keyState{ eInputState::Release }, m_keyCode{ -1 }
	{
	}

	KeyEvent::KeyEvent(eInputState aState, int aCode)
		: Event{ ePriority::High }, m_keyState{ aState }, m_keyCode{ aCode }
	{
	}

	KeyEvent::~KeyEvent()
	{
	}

	void KeyEvent::Dispatch(EventListener& aListener)
	{
		aListener.HandleEvent(*this);
	}

	void KeyEvent::Destroy()
	{
		CU::MemoryPool<KeyEvent>::GetInstance().ReturnResource(this);
	}

	void KeyEvent::Clean()
	{
	}

	void KeyEvent::Init(eInputState aState, int aCode)
	{
		m_keyState = aState;
		m_keyCode = aCode;
	}

	eInputState KeyEvent::GetKeyState() const
	{
		return m_keyState;
	}

	int	KeyEvent::GetKeyCode() const
	{
		return m_keyCode;
	}*/

#pragma endregion KEY_EVENT



#pragma region MOUSE_EVENT

	/*MouseEvent::MouseEvent()
		: Event{ ePriority::Low }, m_currMousePos{ 0, 0 }, m_prevMousePos{ 0, 0 }
	{
	}

	MouseEvent::~MouseEvent()
	{
	}

	void MouseEvent::Dispatch(EventListener& aListener)
	{
		aListener.HandleEvent(*this);
	}

	void MouseEvent::Destroy()
	{
		CU::MemoryPool<MouseEvent>::GetInstance().ReturnResource(this);
	}

	void MouseEvent::Clean()
	{
	}

	void MouseEvent::Init(const CU::Vector2<unsigned>& aCurrentMousePos, const CU::Vector2<unsigned>& aPrevMousePos)
	{
		m_currMousePos = aCurrentMousePos;
		m_prevMousePos = aPrevMousePos;
	}

	const CU::Vector2<unsigned>& MouseEvent::GetCurrentMousePos() const
	{
		return m_currMousePos;
	}*/

#pragma endregion MOUSE_EVENT
}