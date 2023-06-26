#version 330 core
layout (location = 0) in vec3 vertex_Position;
layout (location = 1) in vec2 vertex_TexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(vertex_Position, 1.0);
	TexCoord = vertex_TexCoord;
}