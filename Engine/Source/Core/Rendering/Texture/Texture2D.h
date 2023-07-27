#pragma once

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Texture2D
	{
	public:
		Texture2D(bool hasAlpha = false);
		~Texture2D();

		void					Init(const CU::Vector2<int>& aSize, unsigned char* someData);		// Take in texturedata...
		void					Bind()																const;
		void					Unbind()															const;

		const CU::Vector2<int>& GetSize()															const;

	private:
		CU::Vector2<int>		m_size;
		int						m_internalFormat, m_imageFormat;
		unsigned				m_id;
	};
}