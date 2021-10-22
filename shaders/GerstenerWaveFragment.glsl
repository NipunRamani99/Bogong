#version 330 core
out vec4 FragColor;
in VS_OUT{
	 vec3 Normal;
	 vec3 FragPos;
} vs_out;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 normal = normalize(vs_out.Normal);
	vec3 lightColor = vec3(0.3);
	vec3 ambient = 0.3 * lightColor;
	vec3 lightDir = normalize(lightPos - vs_out.FragPos);
	vec3 viewDir = normalize(viewPos - vs_out.FragPos);
	float diff = max(dot(lightDir, normal),0.);
	vec3 halfwayDir = normalize(viewDir + lightDir);
	float spec = max(dot(halfwayDir, normal), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 specular = spec * lightColor;
	vec3 lighting = (ambient + spec + diff) * vec3(FragPos.y, 0., 1.);
	FragColor = vec4(lighting,1.0);
}