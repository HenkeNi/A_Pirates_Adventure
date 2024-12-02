#pragma once

namespace Hi_Engine
{
	template <class Type>
	struct SinglyLinkedListNode
	{
		Type					m_data;
		SinglyLinkedListNode*	m_nextNode = nullptr;
	};
}