#version 450 
#define MAX_LIGHTS 100

struct Light
{
  vec4 color;
  vec3 position;  
  vec3 rotation;
  float distance;  
  float angle;     
  int type;        
};

uniform Light lights[MAX_LIGHTS];
uniform int lightsCount;
uniform vec3 cameraPosition;  
uniform vec4 ambientLight;    
uniform sampler2D textureImage;

uniform vec3 directionalLightDirection;
uniform vec4 directionalLightColor;

in vec3 FragPos;        
in vec3 WorldNormal;    
in vec2 TexCoords;      
out vec4 FragColor;     

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
        if (lights[i].type == 1) // Point Light
        {
            vec3 lightVector = normalize(lights[i].position - FragPos);
            float distance = length(lights[i].position - FragPos);
            float attenuation = getAttenuation(1.0, 0.1, 0.01, distance);

            // Diffuse calculation
            float diff = max(dot(lightVector, normalize(WorldNormal)), 0.0);
            diffuse += diff * lights[i].color.rgb * attenuation * lights[i].color.w;

            // Specular calculation
            vec3 halfwayDir = normalize(lightVector + cameraVector);
            float spec = pow(max(dot(normalize(WorldNormal), halfwayDir), 0.0), 32.0);
            specular += spec * lights[i].color.rgb * attenuation * lights[i].color.w;
        }
        if (lights[i].type == 2) // Spotlight
        {
            vec3 lightVector = normalize(lights[i].position - FragPos);
            
            float spotEffect = dot(lightVector, normalize(WorldNormal));
            if (spotEffect < cos(lights[i].angle))
                continue; 

            float distance = length(lightVector);

            // Diffuse calculation
            float diff = max(spotEffect, 0.0);
            diffuse += diff * lights[i].color.rgb  * lights[i].color.w;

            // Specular calculation
            vec3 halfwayDir = normalize(lightVector + cameraVector);
            float spec = pow(max(dot(normalize(WorldNormal), halfwayDir), 0.0), 32.0);
            specular += spec * lights[i].color.rgb ;
        }
        if (directionalLightDirection != vec3(0.0)) 
        {
            vec3 lightVector = normalize(directionalLightDirection);

            float diff = max(dot(WorldNormal, -lightVector), 0.0);
            diffuse += diff * directionalLightColor.rgb * texColor.rgb;

        }
    }

    vec3 finalColor = ambient.rgb + texColor.rgb * diffuse + specular;
    FragColor = vec4(clamp(finalColor, 0.0, 1.0), texColor.a);
}
