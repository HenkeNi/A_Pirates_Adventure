#include "Pch.h"
#include "RenderEvents.h"
#include "../../Listener/EventListener.h"
#include "../../../../Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"


namespace Hi_Engine
{
	RenderEvent::RenderEvent()
	{
	}

	RenderEvent::~RenderEvent()
	{
	}

	void RenderEvent::Dispatch(EventListener& aListener)
	{
		aListener.HandleEvent(*this);
	}

	void RenderEvent::Destroy()						
	{
		CU::MemoryPool<RenderEvent>::GetInstance().ReturnResource(this); // TODO; Make more generic
	}

	void RenderEvent::Clean()						
	{
	}

	void RenderEvent::Init(const std::queue<RenderCommand>& someCommands)
	{
		m_renderCommands = someCommands;
	}

	//void RenderEvent::AddRenderCommand(const RenderCommand& aCommand)
	//{
	//	m_renderCommands.push(aCommand);
	//}

	const std::queue<RenderCommand>& RenderEvent::GetCommands() const
	{
		return m_renderCommands;
	}

















	RenderSpriteEvent::RenderSpriteEvent()
	{
	}

	RenderSpriteEvent::~RenderSpriteEvent()
	{
	}

	void RenderSpriteEvent::Dispatch(EventListener& aListener)	
	{
		aListener.HandleEvent(*this);
	}

	void RenderSpriteEvent::Destroy()							
	{
		//CommonUtilities::MemoryPool<RenderSpriteEvent>::GetInstance().ReturnResource(this); // Else where???
	}

	void RenderSpriteEvent::Clean()								
	{
	}

	void RenderSpriteEvent::Init(const SpriteRenderData& someData)
	{
		m_renderData = someData;
	}

	const SpriteRenderData& RenderSpriteEvent::GetRenderData() const
	{
		return m_renderData;
	}
}
