#pragma once

#include "../../../Utility/Math/Vectors/Vector.hpp"
// FIX::
#include <../../ThirdParty/GLEW/include/GL/glew.h>
#include <../../ThirdParty/glm/glm.hpp>

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Shader
	{
	public:
		Shader();
		~Shader();

		const Shader& Activate() const;	// make const? => change shader in material to const pointer.?!
		
		void Init(const char* vSource, const char* fSource, const char* gSource);
		void SetBool(const std::string& name, bool value)								const;
		void SetInt(const std::string& name, int value)									const;
		void SetFloat(const std::string& name, float value)								const;
		void SetIntArray(const std::string& name, int* values, int count)				const;
		void SetVector2f(const std::string& name, const CU::Vector2<float>& value)		const;
		void SetVector3f(const std::string& name, const CU::Vector3<float>& value)		const;
		void SetVector4f(const std::string& name, const CU::Vector4<float>& value)		const;
		void SetMatrix4(const std::string& name, const glm::mat4& matrix)				const;

	private:
		int	 CreateShader(GLenum shaderType, const char* source);
		void CheckCompileErrors(unsigned object, const std::string& type);

		unsigned m_id;
	};
}