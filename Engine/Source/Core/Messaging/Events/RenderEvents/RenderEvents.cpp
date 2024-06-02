#include "Pch.h"
#include "RenderEvents.h"
//#include "../../Listener/EventListener.h"
#include "../../../../Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"
#include "../../../../Data/Structs.h"


namespace Hi_Engine
{
	RenderEvent::RenderEvent()
		: Event{ ePriority::Moderate }
	{
	}

	RenderEvent::~RenderEvent()
	{
	}

	void RenderEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}

	void RenderEvent::Init(const std::queue<RenderCommand>& commands)
	{
		m_renderCommands = commands;
	}

	//void RenderEvent::AddRenderCommand(const RenderCommand& aCommand)
	//{
	//	m_renderCommands.push(aCommand);
	//}

	const std::queue<RenderCommand>& RenderEvent::GetCommands() const
	{
		return m_renderCommands;
	}

















	TextRenderEvent::TextRenderEvent()
		: Event{ ePriority::Moderate }
	{
	}

	TextRenderEvent::~TextRenderEvent()
	{
	}

	/*RenderSpriteEvent::RenderSpriteEvent()
	{
	}

	RenderSpriteEvent::~RenderSpriteEvent()
	{
	}

	void RenderSpriteEvent::Dispatch(EventListener& aListener)	
	{
		aListener.HandleEvent(*this);
	}

	void RenderSpriteEvent::Reset()								
	{
	}

	void RenderSpriteEvent::Init(const SpriteRenderData& someData)
	{
		m_renderData = someData;
	}

	const SpriteRenderData& RenderSpriteEvent::GetRenderData() const
	{
		return m_renderData;
	}*/
	void TextRenderEvent::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}

	void TextRenderEvent::Init(const TextRenderData& data, const glm::mat4& projection)
	{
		m_data = data;
		m_projection = projection;
	}
}
