#pragma once

//class Component;
//class ComponentBuilder;
//
//class ComponentFactory
//{
//public:
//	ComponentFactory();
//	~ComponentFactory();
//
//	template	<typename... Args>
//	Component*  Build(const std::string& aType, Args&&... args);
//
//	bool		HasBuilder(const std::string& aType) const;
//
//	bool		RegisterBuilder(const std::string& aType, ComponentBuilder* aBuilder);
//	void		RemoveBuilder(const std::string& aType);
//	void		Clear();
//
//private:
//	std::unordered_map<std::string, ComponentBuilder*> m_builders;
//};
//
//#pragma region Method_Definitions
//
//template <typename... Args>
//Component* ComponentFactory::Build(const std::string& aType, Args&&... args)
//{
//	assert(HasBuilder(aType) && "No Builder for type found!");
//	return m_builders.at(aType)->Build(std::forward<Args>(args)...);
//}
//
//#pragma endregion Method_Definitions