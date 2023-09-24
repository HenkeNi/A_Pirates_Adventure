#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTexIndex;

out vec4 Color;
out vec2 TexCoord;
out float TexIndex;

uniform mat4 uViewProjection;

void main()
{
	Color = aColor;
	TexCoord = aTexCoord;
	TexIndex = aTexIndex;

	gl_Position = uViewProjection * vec4(aPosition, 1.0);
}