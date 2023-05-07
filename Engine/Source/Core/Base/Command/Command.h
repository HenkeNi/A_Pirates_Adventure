#pragma once

namespace Hi_Engine
{
	// TODO; delete copy constructor/assignment??
	class Command
	{
	public:
		virtual ~Command() = default;

		virtual void		Execute()		  = 0;	// Take in a gmaeobject??	ór a C_Controller (base class for enemy/player controllers??
		virtual Command*	Clone()		const = 0; // Needed??

		// Init?? Takes in document..
	};
}