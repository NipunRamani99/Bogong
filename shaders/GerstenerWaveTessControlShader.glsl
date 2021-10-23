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

float GetTessLevel(float Distance0, float Distance1)
{
	float AvgDistance = (Distance0 + Distance1) / 2.0;

	if (AvgDistance <= 2.0) {
		return 10.0;
	}
	else if (AvgDistance <= 5.0) {
		return 7.0;
	}
	else {
		return 3.0;
	}
}

void main() {
	// Just forward the vertex attributes through the GL pipeline.
	tc_out[gl_InvocationID].Pos = tc_in[gl_InvocationID].Pos;
	tc_out[gl_InvocationID].Normal = tc_in[gl_InvocationID].Normal;
	// Calculate the distance from the camera to the three control points
	float EyeToVertexDistance0 = distance(viewPos, tc_in[0].Pos);
	float EyeToVertexDistance1 = distance(viewPos, tc_in[1].Pos);
	float EyeToVertexDistance2 = distance(viewPos, tc_in[2].Pos);
 // Calculate the tessellation levels
	gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
	gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0);
	gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);
	gl_TessLevelInner[0] = gl_TessLevelOuter[2];
}