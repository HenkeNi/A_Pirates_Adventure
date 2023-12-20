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

template <typename T>
inline void RegisterComponent(const std::string& aName) 
{
	PostMaster::GetInstance().SendMessage({ eMessage::ComponentBuilderCreated, std::make_pair(aName, new ConcreteComponentBuilder<T>{} )});
 }

//#define REGISTER_COMPONENT(Name, ComponentType) \
	PostMaster::GetInstance().SendMessage({ eMessage::ComponentBuilderCreated, std::make_pair(Name, new ConcreteComponentBuilder<ComponentType>})
	//EntityManager::GetFactory().RegisterComponentBuilder(Name, new ConcreteComponentBuilder<ComponentType>)
	