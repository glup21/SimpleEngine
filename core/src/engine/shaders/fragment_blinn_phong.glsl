#version 400 core

in vec3 FragPos;
in vec3 WorldNormal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D textureImage;
uniform vec3 LightPosition;
uniform vec3 cameraPosition;

void main()
{
    vec3 lightVector = LightPosition - FragPos;
    vec3 cameraVector = cameraPosition - FragPos;
    vec3 halfwayDir = normalize(lightVector + cameraVector);


    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    float diffuse = max(dot(normalize(WorldNormal), normalize(lightVector)), 0.0);
    float specular = pow(max(dot(normalize(WorldNormal), normalize(halfwayDir)), 0.0), 64);

    vec4 texColor = texture(textureImage, TexCoords);
    texColor = ambient + (texColor * diffuse) + (specular * vec4(1.0, 1.0, 1.0, 1.0) * vec4(0.2)); 

    if (texColor.a < 0.001) {
        discard; 
    }

    FragColor = vec4(texColor.rgb, 1.0f);
}