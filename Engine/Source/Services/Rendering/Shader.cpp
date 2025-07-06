#include "Pch.h"
#include "Shader.h"


namespace Hi_Engine
{
    GLSLShader::GLSLShader()
        : m_id{ 0 }
    {
    }

    GLSLShader::~GLSLShader()
    {
        glDeleteProgram(m_id);
    }

    void GLSLShader::Init(const rapidjson::Value& value)
    {
        m_name = value["name"].GetString();
        std::string path = value["filepath"].GetString();
        
        std::string vertex, fragment;

        std::ifstream vertexStream{ path + m_name + ".vertex.glsl" };
        vertex = { std::istreambuf_iterator<char>(vertexStream), std::istreambuf_iterator<char>() };

        std::ifstream fragmentStream{ path + m_name + ".fragment.glsl" };
        fragment = { std::istreambuf_iterator<char>(fragmentStream), std::istreambuf_iterator<char>() };

        // TODO: Geometryshader

        Create(vertex.c_str(), fragment.c_str(), nullptr);
    }

    const GLSLShader& GLSLShader::Activate() const
    {
        glUseProgram(m_id);
        return *this;
    }

    void GLSLShader::Create(const char* vSource, const char* fSource, const char* gSource)
    {
        /* Create Vertex GLSLShader */
        unsigned vertexShader = CreateShader(GL_VERTEX_SHADER, vSource);
        CheckCompileErrors(vertexShader, "VERTEX");

        /* Create Fragment GLSLShader */
        unsigned fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fSource);
        CheckCompileErrors(fragmentShader, "FRAGMENT");

        /* Create Geometry GLSLShader */
        unsigned geometryShader;
        if (gSource)
        {
            geometryShader = CreateShader(GL_GEOMETRY_SHADER, gSource);
            CheckCompileErrors(geometryShader, "GEOMETRY");
        }

        /* Create Program */
        m_id = glCreateProgram();
        glAttachShader(m_id, vertexShader);
        glAttachShader(m_id, fragmentShader);

        if (gSource)
            glAttachShader(m_id, geometryShader);

        /* Link Program */
        glLinkProgram(m_id);
        CheckCompileErrors(m_id, "PROGRAM");

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        if (gSource)
            glDeleteShader(geometryShader);
    }

    void GLSLShader::SetBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
    }

    void GLSLShader::SetInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void GLSLShader::SetFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void GLSLShader::SetIntArray(const std::string& name, int* values, int count) const
    {
        glUniform1iv(glGetUniformLocation(m_id, name.c_str()), count, values);
    }

    void GLSLShader::SetVector2f(const std::string& name, const FVector2& value) const
    {
        glUniform2f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y);
    }

    void GLSLShader::SetVector3f(const std::string& name, const FVector3& value) const
    {
        glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z);
    }

    void GLSLShader::SetVector4f(const std::string& name, const FVector4& value) const
    {
        glUniform4f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z, value.w);
    }

    void GLSLShader::SetMatrix4(const std::string& name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, false, glm::value_ptr(matrix));
    }

    int GLSLShader::CreateShader(GLenum shaderType, const char* source)
    {
        unsigned shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        return shader;
    }

    void GLSLShader::CheckCompileErrors(unsigned object, const std::string& type)
    {
        int		success;
        char	infoLog[1024];

        type != "PROGRAM" ? glGetShaderiv(object, GL_COMPILE_STATUS, &success) : glGetProgramiv(object, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER -> " << type << '\n' << infoLog << '\n';
        }
        //int		success;
        //char	infoLog[1024];

        //aType != "PROGRAM" ? glGetShaderiv(anObject, GL_COMPILE_STATUS, &success) : glGetProgramiv(anObject, GL_LINK_STATUS, &success);

        //if (!success)
        //    std::cout << "ERROR::SHADER -> " << aType << '\n' << infoLog << '\n';
    }
}