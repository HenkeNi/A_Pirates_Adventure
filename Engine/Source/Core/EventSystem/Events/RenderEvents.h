#pragma once
#include "../Core/Event.h"
#include "../../../Rendering/Text/TextTypes.h"
#include "../../../Rendering/RenderTypes.h" // needed??

namespace Hi_Engine
{
	struct RenderCommand;
	 

	class SpriteBatchRequest : public Event<SpriteBatchRequest>
	{
	public:
		SpriteBatchRequest();

		void Dispatch(EventListener& listener) override;
		void Init(const SpriteBatch& spriteBatch);

		inline const SpriteBatch& GetBatch() const { return m_spriteBatch; }

	private:
		SpriteBatch m_spriteBatch;
	};




	// RenderSpriteEvent, BatchRenderEvent, BatchSpriteRenderEvent? RenderRequestEvent?
	class RenderEvent : public Event<RenderEvent>
	{
	public:
		RenderEvent();
		~RenderEvent();
		 
		void Dispatch(EventListener& listener)			override;		// make private, have firend class?
		void Init(const std::queue<RenderCommand>& commands);

		const std::queue<RenderCommand>& GetCommands() const;

	private:
		//std::vector<RenderCommand> m_renderCommands;
		std::queue<RenderCommand> m_renderCommands;
	};


	//class TextRenderEvent : public Event<TextRenderEvent>
	//{
	//public:
	//	TextRenderEvent();
	//	~TextRenderEvent();

	//	void Dispatch(EventListener& listener)			override;
	//	void Init(const TextRenderData& data, const glm::mat4& projection);

	//	inline const TextRenderData& GetData() const { return m_data; }
	//	inline const glm::mat4& GetProjection() const { return m_projection; }

	//private:
	//	TextRenderData m_data;
	//	glm::mat4 m_projection;
	//};



	// ### why both RenderSpriteEvent and RenderEvent with sprite data??+ ###

	//class RenderSpriteEvent : public Event<RenderSpriteEvent>
	//{
	//public:
	//	RenderSpriteEvent();
	//	~RenderSpriteEvent();

	//	void Dispatch(EventListener& aListener)			override;
	//	void Reset()									override;
	//	void Init(const SpriteRenderData& someData);

	//	const SpriteRenderData& GetRenderData()			   const;

	//private:
	//	SpriteRenderData m_renderData;
	//};
}
