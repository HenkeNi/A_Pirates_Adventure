#pragma once
#include "Dependencies/rapidjson/document.h"


namespace Hi_Engine
{
	template <class Resource, typename Identifier = std::string>
	class ResourceHolder
	{
	public:
		ResourceHolder(const ResourceHolder&)			 = delete;
		ResourceHolder& operator=(const ResourceHolder&) = delete;

		ResourceHolder(ResourceHolder&&)				 = default;
		ResourceHolder& operator=(ResourceHolder&&)		 = default;

		static ResourceHolder&				GetInstance();
		
		std::shared_ptr<Resource>			GetResource(const Identifier& identifier);					// return pointer instead
		const std::shared_ptr<Resource>&	GetResource(const Identifier& identifier)		const;
		bool								HasResource(const Identifier& identifier)		const;

		void								LoadResources(const std::string& filePath);
		void								Insert(Identifier identifier, std::shared_ptr<Resource> resource);
		void								Clear();

	private:
		ResourceHolder() = default;

		std::unordered_map<Identifier, std::shared_ptr<Resource>> m_resources;
	};

	/*using TextureHolder = ResourceHolder<Texture2D>;
	using ShaderHolder  = ResourceHolder<GLSLShader>;*/

#pragma region Method_Definitions

	template <class Resource, typename Identifier>
	ResourceHolder<Resource, Identifier>& ResourceHolder<Resource, Identifier>::GetInstance()
	{
		static ResourceHolder instance;
		return instance;
	}

	template <class Resource, typename Identifier>
	std::shared_ptr<Resource> ResourceHolder<Resource, Identifier>::GetResource(const Identifier& identifier)
	{
		assert(HasResource(identifier) && "[ResourceHolder::GetResource] - Resource not found");
		return m_resources.find(identifier)->second;
	}

	template <class Resource, typename Identifier>
	const std::shared_ptr<Resource>& ResourceHolder<Resource, Identifier>::GetResource(const Identifier& identifier) const
	{
		assert(HasResource(identifier) && "[ResourceHolder::GetResource] - Resource not found");
		return m_resources.find(identifier)->second;
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
	void ResourceHolder<Resource, Identifier>::Insert(Identifier identifier, std::shared_ptr<Resource> resource)
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