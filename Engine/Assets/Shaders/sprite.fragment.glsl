#version 330 core

out vec4 FragColor;

//struct Material
//{
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//	float shininess;
//};

//struct Light
//{
//	vec3 position;
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//}

in vec2 TexCoord;

uniform sampler2D uTexture;
//uniform vec3 uLightColor;

void main()
{
	vec4 texColor = texture(uTexture, TexCoord);
	
	//float ambientStrenth = 0.1;
	//vec3 ambient = ambientStrength * uLightColor;


	if (texColor.a < 0.1)
		discard;
	
	FragColor = texColor;
}