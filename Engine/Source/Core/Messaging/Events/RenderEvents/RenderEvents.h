#pragma once
#include "../Event.h"
#include "Data/Structs.h"

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

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
