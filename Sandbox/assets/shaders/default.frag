#version 330 core


struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct PointLight {
	vec3 position;

	//float constant;
    //float linear;
    //float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir); //TODO atinuation

out vec4 FragColor;

in vec3 normal; // Diffuse
in vec3 fragmentPosition; // Diffuse // Specular

uniform vec3 objectColour; // Default
uniform vec3 lightColour;  // Default
uniform vec3 lightPosition; // Diffuse

uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;

void main()
{
	/*// ======================== Ambient ========================
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
	FragColor = vec4(result, 1.0); // Default*/


}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 cameraPosition) {
	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragmentPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	vec3 viewDir = normalize(cameraPosition - fragmentPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	return (ambient + diffuse + specular);
}