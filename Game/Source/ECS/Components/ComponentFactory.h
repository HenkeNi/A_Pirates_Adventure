#pragma once

class Component;
class ComponentBuilder;

class ComponentFactory
{
public:
	ComponentFactory();
	~ComponentFactory();

	template	<typename... Args>
	Component*  Build(const std::string& type, Args&&... args);

	bool		HasBuilder(const std::string& type) const;

	bool		RegisterBuilder(const std::string& type, ComponentBuilder* builder);
	void		RemoveBuilder(const std::string& type);
	void		Clear();

private:
	std::unordered_map<std::string, ComponentBuilder*> m_builders;
};

#pragma region Method_Definitions

template <typename... Args>
Component* ComponentFactory::Build(const std::string& type, Args&&... args)
{
	assert(HasBuilder(type) && "No Builder for type found!");
	return m_builders.at(type)->Build(std::forward<Args>(args)...);
}

#pragma endregion Method_Definitions