#version 330 core

in vec3 FragPos;
in vec3 WorldNormal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D textureImage;
uniform vec3 LightPosition;

void main()
{
    vec3 lightVector = LightPosition - FragPos;
    vec4 texColor = texture(textureImage, TexCoords);
    vec4 ambient = vec4(0.05, 0.05, 0.05, 1.0) * texColor;
    float diffuse = max(dot(normalize(WorldNormal), normalize(lightVector)), 0.0);

    
    texColor = texColor * diffuse + ambient; 

    if (texColor.a < 0.001) {
        discard; 
    }

    texColor = vec4(texColor.rgb, 1.0f); 
    
    FragColor = texColor;
}