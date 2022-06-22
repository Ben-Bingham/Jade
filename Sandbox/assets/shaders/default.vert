#version 330 core
layout (location = 0) in vec3 inputPositon;
layout (location = 1) in vec2 inputTextureCords;

out vec2 outputTextureCords;

void main() {
	gl_Position = vec4(inputPositon.xyz, 1.0);
	outputTextureCords = inputTextureCords;
}