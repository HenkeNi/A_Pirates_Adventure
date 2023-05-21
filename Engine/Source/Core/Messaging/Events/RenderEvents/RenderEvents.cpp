#include "Pch.h"
#include "RenderEvents.h"
#include "../../Listener/EventListener.h"


namespace Hi_Engine
{
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
