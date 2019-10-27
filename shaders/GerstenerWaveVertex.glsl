#version 330 core
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec4 aColor;
layout(location = 2)in vec3 aNormal;
out vec4 Color;
out vec3 Normal;
out vec3 vertPos;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view*model*(vec4(aPos, 1.0));
	Normal = aNormal;
	Color = aColor;
	vertPos = vec3(model * vec4(aPos, 1.0));
}