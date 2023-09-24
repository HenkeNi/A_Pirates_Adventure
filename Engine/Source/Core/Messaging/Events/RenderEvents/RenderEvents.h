#pragma once
#include "../Event.h"
#include "Data/Structs.h"

namespace Hi_Engine
{
	namespace CU = CommonUtilities;



	class RenderEvent : public Event
	{
	public:
		RenderEvent();
		~RenderEvent();

		void Dispatch(EventListener& aListener)			override;
		void Destroy()									override;
		void Clean()									override;

		void Init(const std::queue<RenderCommand>& someCommands);
		//void AddRenderCommand(const RenderCommand& aCommand);

		const std::queue<RenderCommand>& GetCommands() const;

	private:
		std::queue<RenderCommand> m_renderCommands;
	};



	class RenderSpriteEvent : public Event
	{
	public:
		RenderSpriteEvent();
		~RenderSpriteEvent();

		void Dispatch(EventListener& aListener)			override;
		void Destroy()									override;
		void Clean()									override;
		void Init(const SpriteRenderData& someData);

		const SpriteRenderData& GetRenderData()			   const;

	private:
		SpriteRenderData m_renderData;
	};
}
