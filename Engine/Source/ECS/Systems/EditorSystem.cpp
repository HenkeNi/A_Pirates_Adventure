#include "Pch.h"
#include "EditorSystem.h"
#include "Editor/Editor.h"


namespace Hi_Engine
{
	EditorSystem::EditorSystem(World& world, Editor& editor)
		: System{ world }, m_editor{ editor }
	{
	}

	void EditorSystem::Update(float deltaTime)
	{
		// m_editor.

		// start of frame... after input but before rendering:: Editor -> begin frame()

		// Update	

	}

	eUpdatePhase EditorSystem::GetUpdatePhase() const
	{
		return eUpdatePhase::Update;
	}
}