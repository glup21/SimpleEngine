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
    vec4 texColor = texture(textureImage, TexCoords);
    if (texColor.a < 0.001) {
        discard; 
    }

    //variable calculation
    vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
    vec3 lightVector = LightPosition - FragPos;
    vec3 cameraVector = cameraPosition - FragPos;
    vec3 halfwayDir = normalize(lightVector + cameraVector);
    
    float proximityToWhite = length(vec3(1.0) - texColor.rgb);
    float shininess = proximityToWhite * 128.0;
    float specularCoeff = 0.5;

    //light calculation
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * texColor;
    float diffuse = max(dot(normalize(WorldNormal), normalize(lightVector)), 0.0);
    float specular = pow(max(dot(normalize(WorldNormal), normalize(halfwayDir)), 0.0), shininess) * specularCoeff;

    //output
    vec3 color = ambient.rgb + texColor.rgb * diffuse + specular * lightColor.rgb;
    FragColor = vec4(color, 1.0f);
}