#version 330 core //TODO optimizations

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
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

#define MAX_POINT_LIGHTS 16
#define MAX_DIRECTIONAL_LIGHTS 16

out vec4 FragColor;

in vec3 normal;
in vec3 fragmentPosition;
in vec2 textureCordinates;

in vec4 fragmentPositionInLightSpace;

uniform sampler2D shadowMap; //TODO make an array

uniform vec3 cameraPosition;
uniform Material material;

uniform int numberOfPointLights;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform int numberOfDirectionalLights;
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

float shadowCalculation(vec4 fragPosInLight, vec3 lightDir) {
	vec3 projCords = fragPosInLight.xyz / fragPosInLight.w;

	projCords = projCords * 0.5 + 0.5;
	float currentDepth = projCords.z;
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for (int x = -1; x <= 1; ++x) {
		for (int y = -1; y <=1; ++y) {
			float pcfDepth = texture(shadowMap, projCords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}

	shadow /= 9.0;

	if (projCords.z > 1.0) {
		shadow = 0.0;
	}

	return shadow;
}

void main() {
	vec3 result = vec3(0.0, 0.0, 0.0);
		
	for (int i = 0; i < numberOfPointLights; i++) {
		result += CalcPointLight(pointLights[i], normal, fragmentPosition, cameraPosition);
	}
	
	vec3 viewDir = normalize(cameraPosition - fragmentPosition);
	
	for (int i = 0; i < numberOfDirectionalLights; i++) {
		result += CalcDirLight(directionalLights[i], normal, viewDir);
	}
	
	FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 cameraPosition) {
	vec3 ambient = light.ambient * texture(material.diffuse, textureCordinates).rgb;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragmentPosition);
	float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, textureCordinates).rgb;  

	vec3 viewDir = normalize(cameraPosition - fragmentPosition);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * texture(material.specular, textureCordinates).rgb);

	float Distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * Distance + light.quadratic * (Distance * Distance));    

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

	vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * texture(material.diffuse, textureCordinates).rgb;
    vec3 diffuse = light.diffuse * texture(material.diffuse, textureCordinates).rgb;  
    vec3 specular = light.specular * texture(material.specular, textureCordinates).rgb;

	float shadow = shadowCalculation(fragmentPositionInLightSpace, lightDir);

	vec3 color = texture(material.diffuse, textureCordinates).rgb;
	vec3 lightAmb = 0.3 * light.ambient;

	vec3 lighting = (light.ambient + (1.0 - shadow) * ((diff * light.diffuse) + (spec * light.specular)))* diffuse;

	return lighting;
}