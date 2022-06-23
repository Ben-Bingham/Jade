#version 330 core

out vec4 FragColor;
in vec2 outTextureCords;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = mix(texture(texture1, outTextureCords), texture(texture2, outTextureCords), 0.2);
}