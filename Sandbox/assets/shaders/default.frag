#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragmentPosition;

uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 lightPosition;

void main()
{
	// ======================== Ambient ========================
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColour;

	// ======================== Diffuse ========================
	vec3 normalizedNormal = normalize(normal);
	vec3 lightDirection = normalize(lightPosition - fragmentPosition);
	float differenceInVectors = max(dot(normalizedNormal, lightDirection), 0.0);
	vec3 diffuse = differenceInVectors * lightColour;

	// ======================== Combination ========================
	vec3 result = (ambient + diffuse) * objectColour;
	FragColor = vec4(result, 1.0);
}