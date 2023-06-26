#version 330 core
layout (location = 0) in vec3 vert_Position;
layout (location = 1) in vec2 vert_TexCoords;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(vert_Position, 1.0);
	texCoords = vert_TexCoords;
}