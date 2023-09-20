#version 330 core

out vec4 OutputColor;

in vec4 Color; 
in vec2 TexCoord;
in float TexIndex;

uniform sampler2D uTextures[32];

void main()
{
	int index = int(TexIndex);
	vec4 texColor = texture(uTextures[index], TexCoord) * Color;

	//vec4 texColor = texture(uTextures[TexIndex], TexCoord) * Color;
	
	if (texColor.a < 0.1)
		discard;
	
	OutputColor = texColor;		
} 