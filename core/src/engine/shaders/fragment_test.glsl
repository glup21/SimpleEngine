#version 450 
#define MAX_LIGHTS 5

struct Light
{
  vec4 color;
};
uniform Light lights[MAX_LIGHTS];

in vec3 FragPos;
in vec3 WorldNormal;
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D textureImage;
uniform int lightsCount;
uniform vec3 cameraPosition;

void main() 
{
   vec4 finalColor=vec4(0.0,0.0,1.0,1);
   for (int index = 0; index < MAX_LIGHTS; index++) // for all light sources
   {
      finalColor+=lights[index].color;
   }
   FragColor = finalColor;

    // vec4 texColor = texture(textureImage, TexCoords);
    // if (texColor.a < 0.001)
    // {
    //     discard;
    // }

    // vec4 ambient = vec4(0.0);
    // vec4 diffuse = vec4(0.0);
    // vec4 specular = vec4(0.0);
    // vec3 finalColor = vec3(0.0);
    // vec3 color = vec3(0.0, 0.0, 0.0);
    // float proximityToWhite = length(vec3(1.0) - texColor.rgb);
    // float shininess = proximityToWhite * 128.0;
    // float specularCoeff = 0.5;

    // ambient += vec4(texColor.rgb * 0.1, 1.0);

    // for (int i = 0; i < MAX_LIGHTS; i++) 
    // {

    //     vec3 lightDir = normalize(lights[i] - FragPos);
    //     vec3 normal = normalize(WorldNormal);
    //     vec3 viewDir = normalize(cameraPosition - FragPos);
    //     vec3 halfwayDir = normalize(lightDir + viewDir);

    //     float diff = max(dot(normal, lightDir), 0.0);
    //     diffuse += vec4(diff * vec3(1.0), 0.0);

    //     float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    //     specular += vec4(spec * specularCoeff * vec3(1.0), 1.0);

    //     color += lights[i];
    // }

    // finalColor = ambient.rgb + texColor.rgb * diffuse.rgb + specular.rgb + color;
    // FragColor = vec4(finalColor, 1.0);
}

    //     switch(lights[i].type)
    //     {
    //         case 0:
    //             finalColor = vec3(0.0, 1.0, 0.0);
    //             ambient += vec4(texColor.rgb * lights[i].color.rgb * 0.1, 1.0);
    //             break;
    //         case 1:
                
    //             finalColor = vec3(1.0, 1.0, 0.0);
    //             vec3 lightDir = normalize(lights[i].position.xyz - FragPos);
    //             vec3 normal = normalize(WorldNormal);
    //             vec3 viewDir = normalize(cameraPosition - FragPos);
    //             vec3 halfwayDir = normalize(lightDir + viewDir);

    //             float diff = max(dot(normal, lightDir), 0.0);
    //             diffuse += lights[i].color * diff * lights[i].color.w;

    //             float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    //             specular += lights[i].color * spec * specularCoeff * lights[i].color.w;
    //             break;

    //     }

    // }