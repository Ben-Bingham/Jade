#version 330 core
layout (location = 0) in vec3 inputPositon;
layout (location = 1) in vec2 inputTextureCords;

out vec2 textureCords;

uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(inputPositon, 1.0);
	textureCords = inputTextureCords;
}