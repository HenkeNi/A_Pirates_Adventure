#include "Pch.h"
#include "SystemEvents.h"
#include "../../Listener/EventListener.h"
#include "../../../../Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"

namespace Hi_Engine
{
#pragma region WINDOW_EVENT

	WindowEvent::WindowEvent()
		: Event{ ePriority::Moderate }, m_eventType{ eWindowEvent::None }, m_windowSize{ 0, 0 }
	{
	}

	WindowEvent::~WindowEvent()
	{
	}

	void WindowEvent::Dispatch(EventListener& aListener)
	{
		aListener.HandleEvent(*this);
	}

	void WindowEvent::Destroy()
	{
		CU::MemoryPool<WindowEvent>::GetInstance().ReturnResource(this);
	}

	void WindowEvent::Clean()
	{
	}
	
	void WindowEvent::Init(eWindowEvent aType)
	{
		m_eventType = aType;
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

	void InputEvent::Dispatch(EventListener& aListener) 
	{
		aListener.HandleEvent(*this);
	}

	void InputEvent::Destroy()
	{
		CU::MemoryPool<InputEvent>::GetInstance().ReturnResource(this);
	}

	void InputEvent::Clean()
	{
	}

	void InputEvent::Init(const std::unordered_map<eKey, eInputState>& someKeyStates,
		const std::unordered_map<eMouseBtn, eInputState>& someMouseBtnStates,
		const glm::vec2& aMousePos)
	{
		m_keyStates = someKeyStates;
		m_mouseButtonStates = someMouseBtnStates;
		m_mousePosition = aMousePos;	
	}

	eInputState InputEvent::GetKeyState(eKey aKey) const
	{
		if (m_keyStates.contains(aKey))
			return m_keyStates.at(aKey);
	}
	
	eInputState InputEvent::GetMouseBtnState(eMouseBtn aBtn) const
	{
		if (m_mouseButtonStates.contains(aBtn))
			return m_mouseButtonStates.at(aBtn);
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