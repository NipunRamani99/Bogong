#version 410 core
layout(triangles, fractional_even_spacing) in;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

in TC_OUT{
	vec3 Pos;
	vec3 Normal;
} tc_out[];

out TE_OUT{
	vec3 Pos;
	vec3 Normal;
} te_out;


uniform mat4 view;
uniform mat4 projection;

void main() {
	te_out.Pos = interpolate3D(tc_out[0].Pos, tc_out[1].Pos, tc_out[2].Pos);
	te_out.Normal = normalize(interpolate3D(tc_out[0].Normal, tc_out[1].Normal, tc_out[2].Normal));
	//gl_Position = projection * view * vec4(te_out.Pos,1.0);
}
