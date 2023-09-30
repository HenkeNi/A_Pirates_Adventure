#pragma once
#include "../../../Utility/Math/Vectors/Vector.hpp"

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Shader;
	//class Subtexture2D;
	class Texture2D;

	class Material
	{
	public:
		Material();
		//Material(Subtexture2D* aSubtexture, Shader* aShader);
		Material(Texture2D* aTexture, Shader* aShader);

		void						SetColor(const CU::Vector4<float> aColor);
		//void						SetSubtexture(const Subtexture2D* aSubtexture);
		void						SetTexture(const Texture2D* aTexture);
		void						SetShader(Shader* aShader);

		const CU::Vector4<float>&	GetColor()		const;
		//const Subtexture2D*			GetSubtexture()	const;
		const Texture2D*			GetTexture()	const;
		const Shader*				GetShader()		const;

	private:
		CU::Vector4<float>			m_color;
		//const Subtexture2D*			m_subtexture;
		const Texture2D*			m_texture; 
		const Shader*				m_shader;
	};
}