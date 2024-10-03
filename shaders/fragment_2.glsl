#version 330

out vec4 frag_colour;
in vec3 pos;

void main() 
{
    // Create a gradient effect based on the position
    frag_colour = vec4(
        0.5 * (pos.x + 1.0), // Red component varies with x position
        0.5 * (pos.y + 1.0), // Green component varies with y position
        0.5 * (pos.z + 1.0), // Blue component varies with z position
        1.0                  // Alpha component is fully opaque
    );
}