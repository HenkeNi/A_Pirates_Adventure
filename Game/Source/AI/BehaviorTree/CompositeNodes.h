#pragma once



class Composite
{
public:

private:

	// child nodes...
};



/* Executes every child, and fails when one of the children fails */
class Sequence : public Composite
{
};


class Selector : public Composite
{
};



class Decorator : public Composite
{
private:
	// can only have one child...
};