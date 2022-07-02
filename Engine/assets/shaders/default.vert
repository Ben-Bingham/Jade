#version 330 core
layout (location = 0) in vec3 inputPositon;
layout (location = 1) in vec2 inputTextureCords;

out vec2 textureCords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(inputPositon, 1.0);
	textureCords = inputTextureCords;
}