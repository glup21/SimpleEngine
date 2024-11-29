#version 450 
#define MAX_LIGHTS 5

struct Light
{
  vec4 color;
  vec3 position;
  float distance;
};

uniform Light lights[MAX_LIGHTS];

in vec3 FragPos;
in vec3 WorldNormal;
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D textureImage;
uniform int lightsCount;
uniform vec3 cameraPosition;
uniform vec4 ambientLight;

float getAttenuation(float c, float l, float q, float dist)
{
    float att = 1.0 / (c + l * dist + q * dist * dist);
    return clamp(att, 0.0, 1.0);
}

void main() 
{
    vec4 texColor = texture(textureImage, TexCoords);
    if (texColor.a < 0.001) discard;

    vec4 ambient = ambientLight * texColor;
    ambient *= ambientLight.w;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    vec3 cameraVector = normalize(cameraPosition - FragPos);

    for (int i = 0; i < lightsCount; i++)
    {
        vec3 lightVector = normalize(lights[i].position - FragPos);
        float distance = length(lights[i].position - FragPos);
        float attenuation = getAttenuation(1.0, 0.1, 0.01, distance);

        // Diffuse calculation
        float diff = max(dot(lightVector, normalize(WorldNormal)), 0.0);
        diffuse += diff * lights[i].color.rgb * attenuation;

        // Specular calculation
        vec3 halfwayDir = normalize(lightVector + cameraVector);
        float spec = pow(max(dot(normalize(WorldNormal), halfwayDir), 0.0), 32.0);
        specular += spec * lights[i].color.rgb * attenuation;
    }

    vec3 finalColor = ambient.rgb + texColor.rgb * diffuse + specular;
    FragColor = vec4(clamp(finalColor, 0.0, 1.0), texColor.a);
}
