#include "Pch.h"
#include "Material.h"
#include "../Shader/Shader.h"

namespace Hi_Engine
{
	Material::Material()
		: Material{ nullptr, nullptr }
	{
	}

	Material::Material(Texture2D* aTexture, Shader* aShader)
		: m_texture{ aTexture }, m_shader{ aShader }, m_color{ 1.f, 1.f, 1.f, 1.f }
	{
	}

	void Material::SetColor(const CU::Vector4<float> aColor)
	{
		m_color = aColor;
	}

	void Material::SetTexture(const Texture2D* aTexture)
	{
		m_texture = aTexture;
	}

	void Material::SetShader(Shader* aShader)
	{
		m_shader = aShader;
	}

	const CU::Vector4<float>& Material::GetColor() const
	{
		return m_color;
	}

	const Texture2D* Material::GetTexture() const
	{
		return m_texture;
	}

	const Shader* Material::GetShader() const
	{
		return m_shader;
	}
}