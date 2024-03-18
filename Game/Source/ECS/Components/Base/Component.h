#pragma once
#include "PostMaster/PostMaster.h"
#include "PostMaster/Message.h"

template <typename T>
class ConcreteComponentBuilder;

class Component
{
public:
	virtual ~Component() {};
};	

// TODO: remove?
//template <typename T>
//inline void RegisterComponent(const std::string& aName) 
//{
//	PostMaster::GetInstance().SendMessage({ eMessage::ComponentBuilderCreated, std::make_pair(aName, new ConcreteComponentBuilder<T>{} )});
// }