#include "Pch.h"
#include "Texture2D.h"

namespace Hi_Engine
{
	Texture2D::Texture2D(GLenum aTextureFormat, bool aLinearFiltering)
		: m_internalFormat{ aTextureFormat }, m_imageFormat{ aTextureFormat }, m_id{ 0 }, m_size{ 0, 0 }, m_linearFiltering{ aLinearFiltering } //  todo fix texture id... (maybe frm json??)
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

	void Texture2D::Init(const CU::Vector2<int>& aSize, unsigned char* someData)
	{
		// assert(someData);
		m_size = aSize;
		m_data = someData;

		/* Generate Texture */
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, aSize.x, aSize.y, 0, m_imageFormat, GL_UNSIGNED_BYTE, someData);

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