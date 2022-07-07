#version 330 core // Default

layout (location = 0) in vec3 inputPositon; // Based on attribute pointers
layout (location = 1) in vec3 inputNormal;  // Based on attribute pointers

out vec3 normal; // Diffuse
out vec3 fragmentPosition;  // Diffuse // Specular

uniform mat4 model; // Default
uniform mat4 view;  // Default
uniform mat4 projection; // Default

void main() {
	gl_Position = projection * view * model * vec4(inputPositon, 1.0); // Default
	normal = mat3(transpose(inverse(model))) * inputNormal; // Diffuse
	fragmentPosition = vec3(model * vec4(inputPositon, 1.0)); // Diffuse // Specular
}