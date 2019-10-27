#version 330 core
out vec4 fragColor;

in vec3 vertPos;
in vec4 Color;
in vec3 Normal;

uniform vec3 campos;
uniform vec3 lightPos;
uniform float ambientPow;
uniform float diffusePow;
uniform float specularPow;
uniform vec4 ambientColor;
uniform vec4 diffuse;
uniform vec4 specular;
vec4 getAmbient()
{
	return ambientPow*Color;
}
vec4 getDiffuse(vec3 pos, vec3 norm)
{
	vec3 ray =  lightPos - vertPos;
	ray = normalize(ray);
	float diff = dot(Normal, ray);
	vec4 diffColor = diff*Color;
	return diffColor;
}
vec4 getSpecular(vec3 pos, vec3 norm)
{
	vec3 lightray = lightPos - vertPos;
	vec3 eyeRay = campos - vertPos;
	lightray = normalize(lightray);
	vec3 reflected = reflect(campos, norm);
	float spec = max(min(0.0,dot(reflected, eyeRay))	,1.0);
	return spec*Color;
}
void main()
{
	vec4 amb = getAmbient();
	vec4 diff = getDiffuse(vertPos, Normal);
	vec4 spec = getSpecular(vertPos, Normal);
	vec4 totalShit = amb + diff + spec;
	
	fragColor = Colour;
}