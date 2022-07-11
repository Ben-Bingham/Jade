#version 330 core

struct TexturedMaterial {
	sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);

#define MAX_LIGHTS 128

out vec4 FragColor;

in vec3 normal;
in vec3 fragmentPosition;
in vec2 textureCordinates;

uniform vec3 cameraPosition;
uniform TexturedMaterial material;

uniform float numberOfLights;
uniform PointLight lights[MAX_LIGHTS];

uniform DirectionalLight directionalLight;

void main() {

	vec3 result = vec3(0.0, 0.0, 0.0);
		
	for (int i = 0; i < numberOfLights; i++) {
		result += CalcPointLight(lights[i], normal, fragmentPosition, cameraPosition);
	}

	vec3 viewDir = normalize(cameraPosition - fragmentPosition);

	result += CalcDirLight(directionalLight, normal, viewDir);

	FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 cameraPosition) {
	vec3 ambient = light.ambient * texture(material.diffuse, textureCordinates).rgb;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragmentPosition);
	float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, textureCordinates).rgb;  

	vec3 viewDir = normalize(cameraPosition - fragmentPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * texture(material.specular, textureCordinates).rgb);

	float Distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * Distance + light.quadratic * (Distance * Distance));    

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * texture(material.diffuse, textureCordinates).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, textureCordinates).rgb;  
    vec3 specular = light.specular * spec * texture(material.specular, textureCordinates).rgb;
    return (ambient + diffuse + specular);
}