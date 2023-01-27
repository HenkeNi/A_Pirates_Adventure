#pragma once
#include <document.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace Hi_Engine
{
	template <class Resource, typename Identifier = std::string>
	class ResourceHolder
	{
	public:
		ResourceHolder(const ResourceHolder&)			 = delete;
		ResourceHolder& operator=(const ResourceHolder&) = delete;

		static ResourceHolder&	GetInstance();
		Resource&				GetResource(const Identifier& anID);
		const Resource&			GetResource(const Identifier& anID)		const;
		bool					Contains(const Identifier& anID)		const;

		void					FetchAll(const std::string& aFilePath);
		void					Insert(Identifier anID, std::unique_ptr<Resource> aResource);
		void					Load(const Identifier& anID, const std::string& aPath, bool alpha);
		void					Load(const Identifier& anID, const std::string& aPath);
		void					Clear();

	private:
		ResourceHolder();

		std::unordered_map<Identifier, std::unique_ptr<Resource>> m_resources;
	};


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
	Resource& ResourceHolder<Resource, Identifier>::GetResource(const Identifier& anID)
	{
		assert(Contains(anID));
		return *m_resources.find(anID)->second;
	}

	template <class Resource, typename Identifier>
	const Resource& ResourceHolder<Resource, Identifier>::GetResource(const Identifier& anID) const
	{
		return GetResource(anID);
	}

	template <class Resource, typename Identifier>
	bool ResourceHolder<Resource, Identifier>::Contains(const Identifier& anID) const
	{
		auto found = m_resources.find(anID);
		return found != m_resources.end();
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::FetchAll(const std::string& aFilePath)
	{
		std::ifstream ifs{ aFilePath };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		if (document.Parse(content.c_str()).HasParseError())
		{
			std::cerr << "[Parse Error]: " << aFilePath << '\n'; 
			return;
		}

		for (auto& value : document.GetArray())
		{
			auto name = value["name"].GetString();
			auto path = value["resource_path"].GetString();

			value.HasMember("alpha") ? Load(name, path, value["alpha"].GetBool()) : Load(name, path);
		}
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Insert(Identifier anID, std::unique_ptr<Resource> aResource)
	{
		auto inserted = m_resources.insert(std::make_pair(anID, std::move(aResource)));
		assert(inserted.second);
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Load(const Identifier& anID, const std::string& aPath, bool alpha)
	{
	}
	
	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Load(const Identifier& anID, const std::string& aPath)
	{
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Clear()
	{
		m_resources.empty();
	}

#pragma endregion Method_Definitions
}