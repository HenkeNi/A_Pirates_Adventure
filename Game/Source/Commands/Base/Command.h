#pragma once

// TODO; delete copy constructor/assignment??
class Command
{
public:
	virtual ~Command() = default;

	virtual void		Execute()		  = 0;
	virtual Command*	Clone()		const = 0; // Needed??

	// Init?? Takes in document..
};