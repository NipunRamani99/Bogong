#version 330 core

// Ouput data
in vec2 texCoords;
in vec4 fragColor;
out vec4 color;
uniform bool isTextured;
uniform sampler2D image;
uniform bool horizontal;
uniform vec3 lightColor;
float Opacity=1.0;
void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    if(isTextured){
	vec3 result = texture(image, texCoords).rgb;
    result = result * ambient;
    color = vec4(result,1.0);
  }
  else
  {
    color = fragColor*vec4(ambient,1.0);
  }
}
/*
void main()
{             
    vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
    vec3 result = texture(image, TexCoords).rgb * weight[0]; // current fragment's contribution
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    FragColor = vec4(result, 1.0);
}
*/