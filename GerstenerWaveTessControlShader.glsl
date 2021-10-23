#version 410 core

layout(vertices = 3) out;

in VS_OUT{
	vec3 Pos;
	vec3 Normal;
} tc_in[];
out TC_OUT{
	vec3 Pos;
	vec3 Normal;
} tc_out[];

uniform vec3 viewPos;

void main() {
	// Just forward the vertex attributes through the GL pipeline.
	tc_out[gl_InvocationID].Pos = tc_in[gl_InvocationID].Pos;
	tc_out[gl_InvocationID].Normal = tc_in[gl_InvocationID].Normal;

	float base_contribution = 4.0;
	float distance_contribution = 12.0;
	float max_contribution = base_contribution + distance_contribution;
	float half_contribution = 0.5*max_contribution; // For outer edges.
	float distance_to_eye = distance(tc_in[gl_InvocationID].Pos, viewPos);
	float tessel_lod = 1.0 - smoothstep(0.0, 24.0, viewPos); // 1 --> close.
	float tessellation_level = distance_contribution * tessel_lod + base_contribution;
	gl_TessLevelInner[0] = tessellation_level;
	gl_TessLevelInner[1] = tessellation_level;
	gl_TessLevelOuter[0] = half_contribution; gl_TessLevelOuter[1] = half_contribution;
	gl_TessLevelOuter[2] = half_contribution; gl_TessLevelOuter[3] = half_contribution;

}