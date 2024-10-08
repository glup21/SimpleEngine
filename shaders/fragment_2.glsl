#version 330

out vec4 frag_colour;
in vec3 pos;

void main() 
{
    frag_colour = vec4(
        0.5 * (pos.x + 1.0),
        0.5 * (pos.y + 1.0),
        0.5 * (pos.z + 1.0), 
        1.0                  
    );
}