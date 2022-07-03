#version 330 core

out vec4 FragColor;
in vec2 textureCords;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColour;
uniform vec3 lightColour;

void main()
{
	FragColor = vec4(lightColour * objectColour, 1.0);
}