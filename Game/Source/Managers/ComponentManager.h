#pragma once


// Todo; make singleton? or put all template version in a Component System??

class Component;

//template <class Type>
class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	//template <typename T>
	void RegisterComponent(Component* aComponent);


	// GetComponentOfType()?? tempalted??

private:
	bool Contains(Component* aComponent) const;



	// Container for update comp => late update => drawable?? > or sort them in that order??
 
	std::unordered_map<std::type_index, std::vector<Component*>> m_components; // use type id as key???




	//std::vector<Type> m_components;
};

//#pragma region Constructors
//
//template <class T>
//ComponentManager<T>::ComponentManager()
//{
//}
//
//template <class T>
//ComponentManager<T>::~ComponentManager()
//{
//}
//
//#pragma endregion Constructors