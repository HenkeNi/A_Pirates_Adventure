#pragma once

// TODO; rename to Component?? 
// maybe dont use inheritance??
class ComponentBase 
{
public:
	virtual ~ComponentBase() {};

	virtual void Init()		 {};
	virtual void Update()	 {};
};