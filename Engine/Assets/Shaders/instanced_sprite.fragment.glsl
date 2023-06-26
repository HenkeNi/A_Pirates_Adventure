//#version 330 core
//out vec4 frag_Color;

//in vec2 texCoords;

//uniform sampler2D texture1;

//void main()
//{
//	vec4 texColor = texture(texture1, texCoords);

//	if (texColor.a < 0.1)
//		discard;

//	frag_Color = texColor;
//}







#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}