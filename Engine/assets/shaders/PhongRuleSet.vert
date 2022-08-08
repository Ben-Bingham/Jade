#version 330 core

layout (location = 0) in vec3 inputPositon;
layout (location = 1) in vec3 inputNormal;
layout (location = 2) in vec2 inputTextureCords;

out vec3 normal;
out vec3 fragmentPosition;
out vec2 textureCordinates;

out vec4 fragmentPositionInLightSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 lightSpaceMatrix;

void main() {
	gl_Position = projection * view * model * vec4(inputPositon, 1.0);
	normal = transpose(inverse(mat3(model))) * inputNormal;
	normal = normalize(normal);
	fragmentPosition = vec3(model * vec4(inputPositon, 1.0));
	textureCordinates = inputTextureCords;
	fragmentPositionInLightSpace = lightSpaceMatrix * vec4(fragmentPosition, 1.0);
}