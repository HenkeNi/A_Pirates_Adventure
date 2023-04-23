#pragma once

namespace Hi_Engine
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
		//Command() = default;
		//Command(const Command&) = delete;

		//Command& operator=(const Command&) = delete;
	};
}