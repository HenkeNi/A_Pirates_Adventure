#pragma once
#include "Dependencies/rapidjson/document.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

namespace Hi_Engine
{
	// TODO; rename ResourceManager? 
	template <class Resource, typename Identifier = std::string>
	class ResourceHolder
	{
	public:
		ResourceHolder(const ResourceHolder&)			 = delete;
		ResourceHolder& operator=(const ResourceHolder&) = delete;

		static ResourceHolder&	GetInstance();
		
		Resource&				GetResource(const Identifier& identifier);					// return pointer instead
		const Resource&			GetResource(const Identifier& identifier)		const;
		bool					HasResource(const Identifier& identifier)		const;

		void					LoadResources(const std::string& filePath);
		void					Insert(Identifier identifier, std::unique_ptr<Resource> resource);
		void					Clear();

	private:
		ResourceHolder();

		std::unordered_map<Identifier, std::unique_ptr<Resource>> m_resources;
	};

	/*using TextureHolder = ResourceHolder<Texture2D>;
	using ShaderHolder  = ResourceHolder<GLSLShader>;*/

#pragma region Constructor

	template <class Resource, typename Identifier>
	ResourceHolder<Resource, Identifier>::ResourceHolder()
	{
	}

#pragma endregion Constructor

#pragma region Method_Definitions

	template <class Resource, typename Identifier>
	ResourceHolder<Resource, Identifier>& ResourceHolder<Resource, Identifier>::GetInstance()
	{
		static ResourceHolder instance;
		return instance;
	}

	template <class Resource, typename Identifier>
	Resource& ResourceHolder<Resource, Identifier>::GetResource(const Identifier& identifier)
	{
		assert(HasResource(identifier));
		return *m_resources.find(identifier)->second;
	}

	template <class Resource, typename Identifier>
	const Resource& ResourceHolder<Resource, Identifier>::GetResource(const Identifier& identifier) const
	{
		return GetResource(identifier);
	}

	template <class Resource, typename Identifier>
	bool ResourceHolder<Resource, Identifier>::HasResource(const Identifier& identifier) const
	{
		auto found = m_resources.find(identifier);
		return found != m_resources.end();
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::LoadResources(const std::string& filePath)
	{
		std::ifstream ifs{ filePath };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		::rapidjson::Document document;
		document.Parse(content.c_str());

		assert(!document.HasParseError() && "Failed to parse resource!");

		for (auto& value : document.GetArray())
		{
			auto resource = std::make_unique<Resource>();
			resource->Init(value);

			std::string name = resource->GetName();
			Insert(name, std::move(resource));
		}
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Insert(Identifier identifier, std::unique_ptr<Resource> resource)
	{
		auto inserted = m_resources.insert(std::make_pair(identifier, std::move(resource)));
		assert(inserted.second);
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Clear()
	{
		m_resources.clear(); // TODO; delete/unload resources (call function)?
	}

#pragma endregion Method_Definitions
}