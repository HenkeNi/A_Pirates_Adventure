#version 330 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 uProjection;

void main()
{
	Color = aColor;
	TexCoord = aTexCoord;

	gl_Position = uProjection * vec4(aPosition.xy, 0.0, 1.0);
}