#include "Pch.h"
#include "Texture2D.h"

namespace Hi_Engine
{
	Texture2D::Texture2D(bool hasAlpha)
		: m_internalFormat{ hasAlpha ? GL_RGBA : GL_RGB }, m_imageFormat{ m_internalFormat }, m_id{ 0 }
	{
	}

	Texture2D::~Texture2D()
	{
		Unbind();
		glDeleteTextures(1, &m_id);
	}

	void Texture2D::Init(const CU::Vector2<int>& aSize, unsigned char* someData)
	{
		assert(someData);

		/* Generate Texture */
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, aSize.x, aSize.y, 0, m_imageFormat, GL_UNSIGNED_BYTE, someData);
		glGenerateMipmap(GL_TEXTURE_2D);

		/* Set Texture Wrap and Filter Modes */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_internalFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_internalFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR /*GL_LINEAR_MIPMAP_LINEAR*/); // Or just GL_Linear??
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR /*GL_LINEAR_MIPMAP_LINEAR*/);

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
}