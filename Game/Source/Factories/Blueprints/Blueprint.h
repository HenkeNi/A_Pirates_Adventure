#pragma once

class Component;
class ComponentFactory;
class GameObject;

class Blueprint
{
public:
	Blueprint();
	~Blueprint();


	GameObject Create(const ComponentFactory& aFactory) const; // ??????

	void LoadFromJson(rapidjson::Value& aBlueprintObject, ComponentFactory& aFactory);
	//void Insert(const std::string& aType, Component* aComponent);
	void Insert(Component* aComponent);
	bool Contains(Component* aComponent) const;

	// bool IsOfType() const;

private:
	std::vector<Component*> m_components;
	std::string				m_name, m_type;

	// std::vector<std::string> m_componentList; // USE THIS INSTEAD??? store name of component!!!! -> CANT!! need to set up components...


	// how to store compoennts??
	//std::unordered_map<std::string, Component*> m_components;
	//std::unordered_map<std::string, std::type_index> m_components;





	// Blueprint store std::string, sstd::string => blueprint name 
};

