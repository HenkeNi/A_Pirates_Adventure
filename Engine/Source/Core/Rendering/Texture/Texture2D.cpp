#include "Pch.h"
#include "Texture2D.h"

namespace Hi_Engine
{
	Texture2D::Texture2D(GLenum textureFormat, bool linearFiltering)
		: m_internalFormat{ textureFormat }, m_imageFormat{ textureFormat }, m_id{ 0 }, m_size{ 0, 0 }, m_linearFiltering{ linearFiltering } //  todo fix texture id... (maybe frm json??)
	{
		//static unsigned ID = 1;
		//m_id = ID;
		//++ID;
	}

	Texture2D::~Texture2D()
	{
		Unbind();
		glDeleteTextures(1, &m_id);
	}

	void Texture2D::Init(const CU::Vector2<int>& size, unsigned char* data)
	{
		// assert(someData);
		m_size = size;
		m_data = data;

		/* Generate Texture */
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_size.x, m_size.y, 0, m_imageFormat, GL_UNSIGNED_BYTE, m_data);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "ERROR: Initializing texture\n";
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		/* Set Texture Wrap and Filter Modes */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_internalFormat != GL_RGB ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_internalFormat != GL_RGB ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_linearFiltering ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_linearFiltering ? GL_LINEAR : GL_NEAREST);

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

	const CU::Vector2<int>& Texture2D::GetSize() const
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