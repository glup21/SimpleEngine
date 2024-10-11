#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D textureImage;

void main()
{
    // Sample the texture
    vec4 texColor = texture(textureImage, TexCoords);

    // Debugging: Check if texColor has valid image data
    if (texColor.r == 0.0 && texColor.g == 0.0 && texColor.b == 0.0 && texColor.a == 1.0) {
        // If texColor is completely black and transparent, output red color
        FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color
    } else {
        // Otherwise, output the sampled texture color
        FragColor = texColor;
    }

    // Uncomment the following line to output a constant color for debugging
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0); // White color
}