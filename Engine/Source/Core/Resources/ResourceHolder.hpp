#pragma once
#include "../Rendering/Shader/Shader.h"
#include "../Rendering/Texture/Texture2D.h"
#include "../Rendering/Texture/Subtexture2D.h"
#include "../Audio/AudioSource.h"
#include "../Rendering/Text/Font/Font.h"
#include <../../ThirdParty/rapidjson/document.h>
#include <../../ThirdParty/rapidjson/rapidjson.h>
#include <../../ThirdParty/stb_image/stb_image.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

// #include <irrKlang.h>
#include <../../ThirdParty/FreeType/include/ft2build.h>
//#include <ft2build.h>
#include FT_FREETYPE_H  

// TODO; rename ResourceManager? 

// Todo, use inheritance instead? For loading, etcc..?

namespace Hi_Engine
{
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
		void					CreateResources(const rapidjson::Document& document);
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

		CreateResources(document);
	}

	template <class Resource, typename Identifier>
	inline void	ResourceHolder<Resource, Identifier>::CreateResources(const ::rapidjson::Document& document)
	{
		assert(false && "ERROR: Resource not handled!");
	}

	template <>
	inline void	ResourceHolder<Texture2D, std::string>::CreateResources(const ::rapidjson::Document& document)
	{
		for (auto& value : document.GetArray())
		{
			std::string id = value["id"].GetString();
			std::string path = value["path"].GetString();
			std::string filtering = value["filtering"].GetString();
			bool alpha = value["alpha"].GetBool();

			stbi_set_flip_vertically_on_load(true);

			auto texture = std::make_unique<Texture2D>(alpha ? GL_RGBA : GL_RGB, filtering == "Linear");

			int width, height, nrChannels;
			unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

			texture->Init({ width, height }, data);
			stbi_image_free(data);

			Insert(id, std::move(texture));
				
			// TODO; use static function??
			int rows = value["rows"].GetInt();
			int cols = value["cols"].GetInt();

			float spriteWidth = (float)width / cols;
			float spriteHeight = (float)height / rows;

			for (int row = value["rows"].GetInt() - 1; row >= 0; --row)
			{
				for (int col = value["cols"].GetInt() - 1; col >= 0; --col)
				{
					float minX = (col * spriteWidth) / width;
					float minY = (row * spriteHeight) / height;
					float maxX = ((col + 1) * spriteWidth) / width;
					float maxY = ((row + 1) * spriteHeight) / height;

					auto subtexture = std::make_unique<Subtexture2D>(GetResource(id), glm::vec2{ minX, minY }, glm::vec2{ maxX, maxY });

					int invertedRow = (rows - 1) - row;
					ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().Insert({ id, invertedRow, (int)col }, std::move(subtexture));
				}
			}



			//for (float row = 0; row < rows; ++row)
			//{
			//	for (float col = 0; col < cols; ++col)
			//	{
			//		float minX = (col * spriteWidth) / width;
			//		float minY = (row * spriteHeight) / height;
			//		float maxX = ((col + 1) * spriteWidth) / width;	
			//		float maxY = ((row + 1) * spriteHeight) / height;

			//		auto subtexture = std::make_unique<Subtexture2D>(GetResource(id), glm::vec2{ minX, minY }, glm::vec2{ maxX, maxY });

			//		ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().Insert({ id, (int)col, (int)row }, std::move(subtexture));
			//		//ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().Insert({ id, (int)row, (int)col }, std::move(subtexture));
			//		//std::string subID = id + "_" + std::to_string((int)row) + std::to_string((int)col);
			//		//ResourceHolder<Subtexture2D>::GetInstance().Insert(subID, std::move(subtexture));
			//	}
			//}
		}
	}

	template <>
	inline void	ResourceHolder<Subtexture2D, std::string>::CreateResources(const ::rapidjson::Document& document)
	{
		for (auto& value : document.GetArray())
		{
			std::string parent = value["parent_id"].GetString();
			auto& parentTexture = ResourceHolder<Texture2D>::GetInstance().GetResource(parent);

			float minX = value["min_uv"][0].GetFloat();
			float minY = value["min_uv"][1].GetFloat();

			float maxX = value["max_uv"][0].GetFloat();
			float maxY = value["max_uv"][1].GetFloat();

			auto subtexture = std::make_unique<Subtexture2D>(parentTexture, glm::vec2{ minX, minY }, glm::vec2{ maxX, maxY });

			std::string id = value["id"].GetString();

			Insert(id, std::move(subtexture));
		}
	}

	template <>
	inline void	ResourceHolder<GLSLShader, std::string>::CreateResources(const ::rapidjson::Document& document)
	{
		for (auto& value : document.GetArray())
		{
			std::string id = value["name"].GetString();
			std::string path = value["filepath"].GetString();

			auto shader = std::make_unique<GLSLShader>();

			std::string vertex, fragment;

			std::ifstream vertexStream{ path + id + ".vertex.glsl" };
			vertex = { std::istreambuf_iterator<char>(vertexStream), std::istreambuf_iterator<char>() };

			std::ifstream fragmentStream{ path + id + ".fragment.glsl" };
			fragment = { std::istreambuf_iterator<char>(fragmentStream), std::istreambuf_iterator<char>() };

			// TODO: Geometryshader

			shader->Init(vertex.c_str(), fragment.c_str(), nullptr);

			Insert(id, std::move(shader));
		}
	}

	template <>
	inline void	ResourceHolder<Font, std::string>::CreateResources(const ::rapidjson::Document& document)
	{
		for (auto& value : document.GetArray())
		{
			std::string id = value["name"].GetString();
			std::string path = value["filepath"].GetString();
			std::string name = value["name"].GetString();

			int size = value["size"].GetInt();

			auto font = std::make_unique<Font>();

			// Initialize (and load) the FreeType library			- need to do every time?
			FT_Library ft;
			if (FT_Init_FreeType(&ft))
				assert(false && "ERROR: Could not init FreeType Library");

			// Load font as face
			FT_Face face;
			if (FT_New_Face(ft, path.c_str(), 0, &face))
				assert(false && "ERROR: Failed to load font");

			// Set size to load glyphs as
			FT_Set_Pixel_Sizes(face, 0, size);

			// Disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			const auto& glyph = face->glyph;

			// Compile, and store, the first 128 ASCII characters
			for (unsigned char c = 0; c < 128; ++c)
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR: Failed to load Glyph\n";
					continue;
				}

				std::string identifier = name + "_" + std::to_string(c);
				ResourceHolder<Texture2D>::GetInstance().Insert(identifier, std::make_unique<Texture2D>(GL_RED));
				ResourceHolder<Texture2D>::GetInstance().GetResource(identifier)
					.Init({ (int)glyph->bitmap.width, (int)glyph->bitmap.rows }, glyph->bitmap.buffer);

				Character character;
				character.Size = { glyph->bitmap.width, glyph->bitmap.rows };
				character.m_bearing = { (int)glyph->bitmap_left, (int)glyph->bitmap_top };
				character.m_textureID = identifier;
				character.m_advance = glyph->advance.x;

				font->AddCharacter(c, std::move(character));
			}

			glBindTexture(GL_TEXTURE_2D, 0);

			// destroy FreeType once we're finished
			FT_Done_Face(face);
			FT_Done_FreeType(ft);

			Insert(name, std::move(font));
		}
	}
	
	template <>
	inline void ResourceHolder<AudioSource, std::string>::CreateResources(const ::rapidjson::Document& document)
	{
		for (auto& value : document.GetArray())
		{
			// TODO; use engine parser??
			std::string name = value["name"].GetString();
			std::string path = value["filepath"].GetString();
			bool isLooping = value["is_looping"].GetBool();

			auto audioSource = std::make_unique<AudioSource>();
			// audioSource->SetSource = 


			audioSource->SetSource(path);
			audioSource->SetIsLooping(isLooping);
			// audioSource->SetSource(engine->getSoundSource(path));

			// TODO: Geometryshader

			// shader->Init(vertex.c_str(), fragment.c_str(), nullptr);

			Insert(name, std::move(audioSource));
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