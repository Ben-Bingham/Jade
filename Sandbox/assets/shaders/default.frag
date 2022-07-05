#version 330 core

out vec4 FragColor;

in vec3 normal; // Diffuse
in vec3 fragmentPosition; // Diffuse // Specular

uniform vec3 objectColour; // Default
uniform vec3 lightColour;  // Default
uniform vec3 lightPosition; // Diffuse
uniform vec3 cameraPosition;  // Specular

void main()
{
	// ======================== Ambient ========================
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColour;

	// ======================== Diffuse ========================
	vec3 normalizedNormal = normalize(normal);										// Specular
	vec3 lightDirection = normalize(lightPosition - fragmentPosition);				// Specular
	float differenceInVectors = max(dot(normalizedNormal, lightDirection), 0.0);
	vec3 diffuse = differenceInVectors * lightColour;

	// ======================== Specular ========================
	float specularStrength = 0.5;
	float shininess = 32;

	vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectionDirection = reflect(-lightDirection, normalizedNormal);

	float specularValue = pow(max(dot(viewDirection, reflectionDirection), 0.0), shininess);
	vec3 specular = specularStrength * specularValue * lightColour;

	// ======================== Combination ========================
	vec3 result = (ambient + diffuse + specular) * objectColour; // Default
	FragColor = vec4(result, 1.0); // Default
}