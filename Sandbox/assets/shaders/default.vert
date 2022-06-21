#version 330 core
layout (location = 0) in vec3 inputPositon;

void main() {
	gl_Position = vec4(inputPositon.xyz, 1.0);
}