#pragma once
#include "System.h"

namespace Hi_Engine
{
	class Editor;

	class EditorSystem : public System
	{
	public:
		EditorSystem(ECSCoordinator& ecs, Editor& editor);

		void Update(float deltaTime) override;
		eUpdatePhase GetUpdatePhase() const override;

	private:
		Editor& m_editor;
	};
}
