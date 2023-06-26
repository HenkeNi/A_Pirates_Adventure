#version 330 core
out vec4 fragment_Color;

in vec2 TexCoord;

uniform sampler2D	Texture;
uniform vec4		Color;

void main()
{
	fragment_Color = texture(Texture, TexCoord) * Color;
}