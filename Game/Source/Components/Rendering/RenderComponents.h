#pragma once
#include "../Base/ComponentBase.h"
#include "../Data/Structs.h"


struct SpriteComponent : public ComponentBase
{
	Hi_Engine::Subtexture2D* Subtexture;
	CU::Vector4<float> Color = { 1.f, 1.f, 1.f, 1.f };
	// Hi_Engine::Material m_material;	// Store strings instead?? keys..

	// int m_textureID; ?
	// int m_shaderID; ?
	// width, hight??
};

struct AnimationComponent : public ComponentBase
{
	std::unordered_map<std::string, Animation>	Animations;	// replace with Array?? or enum for key?
	std::string									Active;		// index instead??




	// store default??

	/*std::string m_identifier;
	std::vector<std::string> m_animations;
	unsigned	m_totalFrames; 
	unsigned	m_currentFrame;
	float		m_frameDuration;
	float		m_elapsedFrameTime;
	bool		m_isPlaying;
	bool		m_isLooping;*/
};

struct CameraComponent : public ComponentBase
{
	Hi_Engine::Camera	Camera;
	CU::Vector3<float>  TargetOffset;
	//class Entity*		m_target = nullptr;
	unsigned			TargetID = 0;
};





struct DebugRectComponent : public ComponentBase
{
	Hi_Engine::Shader* Shader;
	CU::Vector4<float> Color;
};



// Rename? PrimitiveRect or DebugRect? 
struct RectComponent : public ComponentBase
{
	Hi_Engine::Shader* Shader;
	CU::Vector4<float> Color;
};


struct LineComponent : public ComponentBase
{
	Hi_Engine::Physics::LineSegment2D<float> LineSegment;
};


struct TextComponent : public ComponentBase
{
	class Hi_Engine::Font* Font;
	std::string				Text;
	unsigned				Size = 32;
	//Hi_Engine::Shader*	Shader;
	//Hi_Engine::Font*	Font;
	// float				m_scale; use transform instead..
	CU::Vector4<float>		Color;
};






// HERE?? Or maybe use two sprites instead?? add system HealthBarSystem?
struct HealthBarComponent : public ComponentBase
{
	Hi_Engine::Material Container;
	Hi_Engine::Material Bar;
	// position? size?
};









// SpriteSheet component? (stores texture atlas, also holds current frame, etc...)




// Shadow component??




// REMOVE!!!
//struct TileComponent : public ComponentBase
//{
//	// Tile specific data..
//	CU::Vector2<float>	m_size;
//	unsigned			m_type;		
//	bool				m_isTraversable; // Needed???
//};
//
//struct MapChunkComponent : public ComponentBase
//{
//	CU::Vector2<unsigned>	m_size;
//	CU::Vector2<int>		m_position;
//	unsigned				m_chunkID;
//
//
//	// Data for chunk of tiles
// };

// Store each tile as an Entity? depending on which chunk it is in => render it or not..???