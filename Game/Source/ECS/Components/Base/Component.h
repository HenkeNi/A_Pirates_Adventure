#pragma once

//template <typename T>
//class ConcreteComponentBuilder;

class Component
{
public:
	virtual ~Component() {};
};	


//using ComponentType = std::uint8_t;

// TODO: remove?
//template <typename T>
//inline void RegisterComponent(const std::string& aName) 
//{
//	PostMaster::GetInstance().SendMessage({ eMessage::ComponentBuilderCreated, std::make_pair(aName, new ConcreteComponentBuilder<T>{} )});
// }