#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
uniform sampler2D textureImage;
uniform vec3 cameraPosition;

void main()
{
    vec4 texColor = texture(textureImage, TexCoords);
    if (texColor.a < 0.001) {
        discard; 
    }
    FragColor = texColor;
    //FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
