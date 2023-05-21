#pragma once
#include "../../../Utility/Math/Vectors/Vector.hpp"

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Shader;
	class Texture2D;

	class Material
	{
	public:
		Material();
		Material(Texture2D* aTexture, Shader* aShader);

		void						SetColor(const CU::Vector4<float> aColor);
		void						SetTexture(const Texture2D* aTexture);
		void						SetShader(Shader* aShader);

		const CU::Vector4<float>&	GetColor()		const;
		const Texture2D*			GetTexture()	const;
		const Shader*				GetShader()		const;

	private:
		CU::Vector4<float>			m_color;
		const Texture2D*			m_texture; 
		const Shader*				m_shader;
	};
}