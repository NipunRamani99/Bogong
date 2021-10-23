#version 410 core
out vec4 FragColor;
in VS_OUT {
	vec3 Pos;
	vec3 Normal;
} fc_in;


uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	// Primary colors of these waves (not accurate!).
	vec3 shallow_wave_albedo = vec3(0.152, 1, 0.737);
	vec3 normal = normalize(fc_in.Normal);
	vec3 lightColor = vec3(0.3);
	vec3 ambient = 0.3 * lightColor;
	vec3 lightDir = normalize(lightPos - fc_in.Pos);
	vec3 viewDir = normalize(viewPos - fc_in.Pos);
	float diff = max(dot(lightDir, normal),0.);
	vec3 halfwayDir = normalize(viewDir + lightDir);
	float spec = max(dot(halfwayDir, normal), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 specular = spec * lightColor;
	vec3 lighting = (ambient + spec + diff) * shallow_wave_albedo;
	FragColor = vec4(lighting,1.0);
}