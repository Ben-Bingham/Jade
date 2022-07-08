#version 330 core

out vec4 FragColor;

uniform vec4 objectColour;

void main() {
	FragColor = objectColour;
}
