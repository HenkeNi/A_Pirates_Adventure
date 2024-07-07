#include "Pch.h"
#include "Texture2D.h"

#include "../../Resources/ResourceHolder.hpp"
#include "Dependencies/stb_image/stb_image.h"

#include "Constants.h"
#include "Subtexture2D.h" // REMOVE!!! read subtextures from json as well...

namespace Hi_Engine
{
	Texture2D::Texture2D()
		: m_data{ nullptr }, m_id{ 0 }
	{
	}

	Texture2D::~Texture2D()
	{
		Unbind();
		glDeleteTextures(1, &m_id);
	}

	void Texture2D::Init(const rapidjson::Value& value)
	{
		m_name = value["id"].GetString();
		std::string path = Constants::TextureDirectory + value["path"].GetString();
		std::string filtering = value["filtering"].GetString();

		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		
		if (!data)
		{
			std::cerr << "ERROR: Failed to load image '" << path << "': " << stbi_failure_reason() << std::endl;
			return;
		}


		static std::unordered_map<int, GLenum> ChannelFormatMap =
		{
			{ 1, GL_RED },
			{ 3, GL_RGB },
			{ 4, GL_RGBA }
		};

		GLenum format;
		if (ChannelFormatMap.contains(nrChannels))
			format = ChannelFormatMap.at(nrChannels);

		Create({ width, height }, format, true, data);
		stbi_image_free(data);





		// Create subtextures...
		int rows = value["rows"].GetInt();
		int cols = value["cols"].GetInt();

		float spriteWidth = (float)width / cols;
		float spriteHeight = (float)height / rows;

		for (int row = rows - 1; row >= 0; --row)
		{
			for (int col = cols - 1; col >= 0; --col)
			{
				float minX = (col * spriteWidth) / width;
				float minY = (row * spriteHeight) / height;
				float maxX = ((col + 1) * spriteWidth) / width;
				float maxY = ((row + 1) * spriteHeight) / height;

				auto subtexture = std::make_unique<Subtexture2D>();
				subtexture->Temp(this, glm::vec2{ minX, minY }, glm::vec2{ maxX, maxY });

				int invertedRow = (rows - 1) - row;
				ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().Insert({ m_name, invertedRow, (int)col }, std::move(subtexture));
			}
		}
	}

	void Texture2D::Create(const IVector2& size, GLenum format, bool linear, unsigned char* data)
	{
		m_size = size;
		m_data = data;

		/* Generate Texture */
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_size.x, m_size.y, 0, format, GL_UNSIGNED_BYTE, m_data);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "ERROR: Initializing texture\n";
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		/* Set Texture Wrap and Filter Modes */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format != GL_RGB ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format != GL_RGB ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		/* Unbind Texture */
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	const IVector2& Texture2D::GetSize() const
	{
		return m_size;
	}

	unsigned Texture2D::GetID() const
	{
		return m_id;
	}
	unsigned char* Texture2D::GetData() const
	{
		return m_data;
	}
}