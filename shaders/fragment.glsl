#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D textureImage;

void main()
{
    // vec4 texColor = texture(textureImage, TexCoords);

    // if (texColor.r == 0.0 && texColor.g == 0.0 && texColor.b == 0.0 && texColor.a == 1.0) {
        //FragColor = vec4(1.0, 0.0, 0.0, 1.0); 
    // } else {
    //     FragColor = texColor;
    // }
    FragColor = vec4(TexCoords, 0.0f, 1.0);
}