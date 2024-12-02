#pragma once
#include "../Core/Event.h"
//#include "ImGui/ImGuiTypes.h"
#include "../../../Editor/ImGui/ImGuiTypes.h"

namespace Hi_Engine
{
	class CreateImGuiWindowRequest : public Event<CreateImGuiWindowRequest>
	{
	public:
		CreateImGuiWindowRequest();

		void					Dispatch(EventListener& listener)		  override;
		void					Init(const ImGuiWindow& window);

		inline const ImGuiWindow& GetWindow() const { return m_window; }

	private:
		ImGuiWindow m_window;
	};
}