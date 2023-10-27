#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 vs_color;

out vec3 color;

void main()
{
	gl_Position = vec4(pos, 1, 1);
	color = vs_color;
}