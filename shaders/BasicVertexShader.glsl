#version 330 core
layout(location = 0)in vec3 pos;
layout(location = 1)in vec4 aColor;
layout(location = 2)in vec2 aTexCoord;
out vec4 Color;
out vec2 TexCoord;
void main()
{
	gl_Position = vec4(pos, 1.0);
	Color = aColor;
	TexCoord = aTexCoord;
}