#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D uText;
uniform vec4 uTextColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uText, TexCoord).r);
    //FragColor = vec4(uTextColor) * sampled;
    vec4 texColor = vec4(uTextColor) * sampled;

    if (texColor.a < 0.1)
        discard;

    FragColor = texColor;
}