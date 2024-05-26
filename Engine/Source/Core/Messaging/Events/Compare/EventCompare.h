#pragma once

namespace Hi_Engine
{
	class BaseEvent;

	/* Comparers */
	struct EventCompare
	{
		bool operator()(const BaseEvent* lhs, const BaseEvent* rhs);
	};
}