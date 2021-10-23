#version 410 core
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec4 aColor;
layout(location = 2)in vec3 aNormal;

out VS_OUT{
	 vec3 Pos;
	 vec3 Normal;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	vs_out.Pos = vec3(model * vec4(aPos, 1.0));
	gl_Position = projection * view * vec4(vs_out.Pos, 1.0);
	vs_out.Normal = transpose(inverse(mat3(model)))*aNormal;
}