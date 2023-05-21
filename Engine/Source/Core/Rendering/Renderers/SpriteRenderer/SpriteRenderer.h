#pragma once
#include "../../../Messaging/Listener/EventListener.h"

// TODO: Store EBO, VBO as members and delete later? (optional?)
// TODO: Rename 2D renderer?? Also renders billboards?? Also renders planes?? 


namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class OrthographicCamera;
	class Camera;
	class Shader;
	struct SpriteRenderData;

	class SpriteRenderer : public EventListener	// BatchRenderer2D or Renderer2D BillboardRenderer?
	{
	public:
		~SpriteRenderer();
		SpriteRenderer(const SpriteRenderer&)				= delete;
		SpriteRenderer& operator=(const SpriteRenderer&)	= delete;

		static SpriteRenderer& GetInstance();

		void HandleEvent(RenderSpriteEvent& anEvent)		override;
		void Render(const SpriteRenderData& someData);	
		
		//void SetCamera(OrthographicCamera* aCamera);
		void SetCamera(Camera* aCamera);


		void Init();
		void Shutdown();

		//void BeginRendering(); // instead of begin scene...
		//void EndRendering();


		//void BeginBatch();
		//void EndBatch();
		//void Flush();

		//void RenderQuad(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor); // ´TODO; use render data...
		//void RenderQuad(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aSize, uint32_t aTextureID);



		//void RenderRotatedQuad();


		void SetShader(Shader* aShader);
		void ConfigureShader();



		// Todo; pass in Shader and Camera in Render...

		//void InitBatch(); // find better name; how many vertices to allocate on the gpu...
		//void RenderBatch(Camera* aCamera, const SpriteRenderData& someData); // take in a shader... or an material... (mateiral = a shader + some data (all of its uniforms)



		//void RenderInstanced(const std::vector<CU::Vector3<float>> somePositions);	// MOVE?? create an InstancedRenderer class??? Struct for InstancedData 

		//void AddRenderCommand();


		//static Vertex* CreateQuad(Vertex* target, float aX, float aY, float aTextureID);

	private:
		SpriteRenderer();

		//static const size_t s_maxNumberOfQuads;	// max number of Quads that can be rendered

		//unsigned	m_quadVAO;
		Camera*		m_camera;

		std::unordered_map<std::string, unsigned> m_VAOs;
		//OrthographicCamera* m_camera;

		
		
		
		
		// TODO; store shader here.. but pass in camera...
		//Shader*		m_shader;		// shader manager?? or pass in string for shader type??? keep in unoredermap? 













		// static??
		
		//static const size_t s_maxVertexCount;	// MAYBVE NOT NEEDED???
		//static const size_t s_maxIndexCount;		
		////static const size_t s_maxTexturesCount; // max number of texture sloths
		//


		//SpriteRendererData m_rendererData;	// make static??

		//Vertex* m_quadBuffer;	// sprite buffer??
		//Vertex* m_currentQuad; // points to current position in quadBuffer... replace with index?? or iterator
		//
		//GLuint	m_quadVA, m_quadVB, m_quadIB;


		// store projection matrix?? => camera updates it??

		// vector<SpriteRenderData>??
	};
}



















//
//
//
//
//
//
//
//
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//class SpriteRenderer {
//public:
//    SpriteRenderer() {
//        // Set up the VBO, VAO, and EBO for rendering quads
//        glGenVertexArrays(1, &m_vao);
//        glGenBuffers(1, &m_vbo);
//        glGenBuffers(1, &m_ebo);
//
//        glBindVertexArray(m_vao);
//        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, m_indices, GL_STATIC_DRAW);
//
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr);
//
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindVertexArray(0);
//
//        // Set up the shader program
//        const char* vertexShaderSource = R"(
//            #version 330 core
//
//            layout (location = 0) in vec4 position;
//            out vec2 texCoord;
//
//            uniform mat4 model;
//            uniform mat4 viewProjection;
//
//            void main() {
//                gl_Position = viewProjection * model * position;
//                texCoord = position.zw;
//            }
//        )";
//
//        const char* fragmentShaderSource = R"(
//            #version 330 core
//
//            in vec2 texCoord;
//            out vec4 color;
//
//            uniform sampler2D textureSampler;
//
//            void main() {
//                color = texture(textureSampler, texCoord);
//            }
//        )";
//
//        m_shaderProgram.compile(vertexShaderSource, fragmentShaderSource);
//    }
//
//    ~SpriteRenderer() {
//        glDeleteBuffers(1, &m_vbo);
//        glDeleteBuffers(1, &m_ebo);
//        glDeleteVertexArrays(1, &m_vao);
//    }
//
//    void draw(const Texture& texture, const glm::mat4& modelMatrix, const glm::mat4& viewProjectionMatrix) {
//        // Bind the texture and shader program
//        glActiveTexture(GL_TEXTURE0);
//        texture.bind();
//
//        m_shaderProgram.use();
//
//        // Set the uniform matrices
//        m_shaderProgram.setUniformMatrix4fv("model", 1, GL_FALSE, &modelMatrix[0][0]);
//        m_shaderProgram.setUniformMatrix4fv("viewProjection", 1, GL_FALSE, &viewProjectionMatrix[0][0]);
//
//        // Bind the VAO and draw
//        glBindVertexArray(m_vao);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//        glBindVertexArray(0);
//    }
//
//private:
//    unsigned int m_vao;
//    unsigned int m_vbo;
//    unsigned int m_ebo;
//
//    unsigned int m_indices[6] = {
//        0, 1, 2,
//        2, 3, 0
//    };
//
//    ShaderProgram m_shaderProgram;
//};