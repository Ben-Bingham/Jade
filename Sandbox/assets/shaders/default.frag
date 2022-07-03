#version 330 core

out vec4 FragColor;
in vec2 textureCords;

uniform vec3 objectColour;
uniform vec3 lightColour;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColour;

	vec3 result = ambient * objectColour;
	FragColor = vec4(result, 1.0);
}