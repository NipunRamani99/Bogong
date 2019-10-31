#version 330 core
layout(location = 0)in vec3 pos;
layout(location = 1)in vec4 aColor;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
out vec4 Color;
void main()
{
	vec3 Pos = vec3((vec4(pos, 0.0)));
	Color = aColor;
}