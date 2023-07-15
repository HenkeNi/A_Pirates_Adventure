#pragma once
#include "Components.h"
//struct TransformComponent;
//struct SpriteComponent;
#include <Core/Resources/ResourceHolder.hpp>


// Rename ComponentBuilder?


class ComponentBase;

class ComponentBaseBuilder
{
public:
	virtual ~ComponentBaseBuilder() = default;
	//virtual ComponentBase* Build() const = 0;
	virtual ComponentBase* Build(std::unordered_map<std::string, std::any> someData) = 0;	// perfect forwarding instead?
};

// change name to DerivedComponentBuilder??
//template <typename T, typename... Args>
template <typename T>
class ConcreteComponentBuilder : public ComponentBaseBuilder
{
public:
	//ComponentBase* Build() const override
	//{
	//	 return CU::MemoryPool<T>::GetInstance().GetResource();		// Have Init function in Component?  
	//}


	// template <typename... Args>
	//ComponentBase* Build(Args&&... args) override
	ComponentBase* Build(std::unordered_map<std::string, std::any> someData) override
	{
		T* component = CU::MemoryPool<T>::GetInstance().GetResource();

		//auto component = CU::MemoryPool<T>::GetInstance().GetResource();

//std::unordered_map<std::string, std::any> map;
//map.insert(std::make_pair<std::string, std::any>{ "Hello", 1 });

//// InitializeComponent<T>(component, std::make_pair{ "Hello", 1 });

//return component;

//InitializeComponent<T>(component, args); // or unpack first???

//return component;

//std::unordered_map<std::string, std::any> someData;


		InitializeComponent(component, someData);

		return component;
	}


	template <typename T>
	void InitializeComponent(T* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{}

	template <>
	void InitializeComponent<TransformComponent>(TransformComponent* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{
		auto position	= std::any_cast<std::array<float, 3>>(someData.at("position"));
		auto scale		= std::any_cast<std::array<float, 3>>(someData.at("scale"));
		float rotation	= std::any_cast<float>(someData.at("rotation"));

		aComponent->m_currentPos = aComponent->m_previousPos = { position[0], position[1], position[2] };
		aComponent->m_scale			= { scale[0], scale[1], scale[2] };
		aComponent->m_rotation		= rotation;
	}

	template <>
	void InitializeComponent<SpriteComponent>(SpriteComponent* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));
		auto texture = std::any_cast<std::string>(someData.at("texture"));
		auto color = std::any_cast<std::array<float, 4>>(someData.at("color"));

		aComponent->m_material = {
			&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(texture),
			&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader)
		};

		aComponent->m_material.SetColor({ color[0], color[1], color[2], color[3] });
	}

	template <>
	void InitializeComponent<RectComponent>(RectComponent* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{
		auto shader = std::any_cast<std::string>(someData.at("shader"));

		aComponent->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource(shader);
		aComponent->m_color = { 1.f, 1.f, 1.f, 1.f }; // TODO; read from json..
	}

	template <>
	void InitializeComponent<ResourceComponent>(ResourceComponent* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{
		int quantity = std::any_cast<int>(someData.at("quantity"));
		aComponent->m_quantity = (unsigned)quantity;
	}

	template <>
	void InitializeComponent<InventoryComponent>(InventoryComponent* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{
		int xx = 20;
		xx += 20;
	}

	template <>
	void InitializeComponent<AnimationComponent>(AnimationComponent* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{
		int xx = 20;
		xx += 20;
	}

	template <>
	void InitializeComponent<AttackColliderComponent>(AttackColliderComponent* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{
		auto startPos = CU::Vector3<float>{ 0.f, 0.f, 0.f };
		auto colliderSize = 0.2f;								// FIX!

		aComponent->m_offset = { 1.0f, 0.f, 0.f };
		aComponent->m_collider.Init({ startPos.x - colliderSize, startPos.y - colliderSize }, { startPos.x + colliderSize, startPos.y + colliderSize });
	}

	template <>
	void InitializeComponent<CameraComponent>(CameraComponent* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{
		int xx = 20;
		xx += 20;
	}

	template <>
	void InitializeComponent<HealthComponent>(HealthComponent* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{
		int value = std::any_cast<int>(someData.at("value"));
		aComponent->m_currentValue = value;

		// TODO; set health stat?!
	}

	template <>
	void InitializeComponent<HitboxColliderComponent>(HitboxColliderComponent* aComponent, const std::unordered_map<std::string, std::any>& someData)
	{
		CU::Vector3<float> position = { 0.f, 0.f, 0.f };
		auto halfSize = std::any_cast<float>(someData.at("halfSize"));

		aComponent->m_collider.Init({ position.x - halfSize, position.z - halfSize }, { position.x + halfSize, position.y + halfSize });
	}




};



/*
template <typename T>
void InitializeComponent(ComponentBase* aComponent, rapidjson::Document& someData)
{
	auto other = someData;

	int x = 10;
	x += 10;
}


template <>
void InitializeComponent<TransformComponent>(ComponentBase* aComponent, const std::unordered_map<std::string, std::any>& someData)
{
	auto data = someData;

	int x = 10;
	x += 10;
}*/

// Derived component builders??