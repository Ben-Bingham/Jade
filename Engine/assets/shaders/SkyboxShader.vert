#version 330 core

layout (location = 0) in vec3 inputPositon;
layout (location = 1) in vec3 inputNormal;
layout (location = 2) in vec2 inputTextureCords;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    //TexCoords = inputPositon;
    //gl_Position = projection * view * vec4(inputPositon, 1.0);
    TexCoords = inputPositon;
    vec4 pos = projection * view * vec4(inputPositon, 1.0);
    gl_Position = pos.xyww;
}  