#pragma once

namespace CommonUtilities
{
	template <class Type>
	struct SinglyLinkedListNode
	{
		Type					m_data;
		SinglyLinkedListNode*	m_nextNode = nullptr;
	};
}