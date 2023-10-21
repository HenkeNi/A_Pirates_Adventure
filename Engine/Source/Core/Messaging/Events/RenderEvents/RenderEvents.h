#pragma once
#include "../Event.h"
#include "Data/Structs.h"

namespace Hi_Engine
{
	namespace CU = CommonUtilities;



	class RenderEvent : public Event<RenderEvent>
	{
	public:
		RenderEvent();
		~RenderEvent();

		void Dispatch(EventListener& aListener)			override;
		void Reset()									override;

		void Init(const std::queue<RenderCommand>& someCommands);
		//void AddRenderCommand(const RenderCommand& aCommand);

		const std::queue<RenderCommand>& GetCommands() const;

	private:
		std::queue<RenderCommand> m_renderCommands;
	};



	class RenderSpriteEvent : public Event<RenderSpriteEvent>
	{
	public:
		RenderSpriteEvent();
		~RenderSpriteEvent();

		void Dispatch(EventListener& aListener)			override;
		void Reset()									override;
		void Init(const SpriteRenderData& someData);

		const SpriteRenderData& GetRenderData()			   const;

	private:
		SpriteRenderData m_renderData;
	};
}
