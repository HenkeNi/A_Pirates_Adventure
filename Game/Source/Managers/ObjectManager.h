#pragma once
#include "../GameObject/GameObject.h"

namespace CU = CommonUtilities;

class ComponentBuilder;

// Put in Scene.h or make singleton?!
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	GameObject*	Create(const std::string& aType);	// rebane AddObject?
	GameObject* Search(int anID);					// SearchObject

	void		AddObject(const GameObject& aGameObject);				// Maybe remove??
	void		DestroyObject(GameObject* aGameObject);					// unnecessary??  pass ID instead?
	void		DestroyAllObjects();
	void		DestroyAllObjects(const std::string& aType);


	// Get object by ID/type, get first 
	// get all objects by tyoe

	// create component?? 

	//void		RegisterPrototype(const std::string& aType, const std::string& aPath);
	//void		RegisterPrototype(const std::string& aType, const GameObject& aGameObject);
	void		RemovePrototype(const std::string& aType);
	

	//void		LoadFromFile(const std::string& aPath); // Loads prototypes or gameobjects??
	void		Clear();

	static void	RegisterBuilder(const std::string& aType, ComponentBuilder* aBuilder);
	static void RegisterPrototype(const std::string& aType, const GameObject& aGameObject);
	static void LoadPrototypes(const std::string& aPath);

	const GameObject*				GetObject(int anID)		const;
	GameObject*						GetObject(int anID);
	const std::vector<GameObject>&	GetAllObjects()			const;
	std::vector<GameObject>&		GetAllObjects();

	// std::vector<GameObject> GetObjectsByType(const std::string& aType);


private:
	//friend class Scene;	// Should scene be able to see everything??

	bool		ContainsPrototype(const std::string& aType)	const;
	void		CreatePrototype();

	static CU::Factory<ComponentBuilder, Component>		s_componentFactory;
	static std::unordered_map<std::string, GameObject>	s_prototypes;				// use blueprints instead??

	std::vector<GameObject>								m_gameObjects; // layers??
	// store components here??
};