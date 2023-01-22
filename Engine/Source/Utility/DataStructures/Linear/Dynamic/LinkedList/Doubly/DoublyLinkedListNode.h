#pragma once

namespace CommonUtilities
{
	template <class Type>
	struct DoublyLinkedListNode
	{
		Type					m_data;
		DoublyLinkedListNode*	m_nextNode, *m_prevNode;
	};
}