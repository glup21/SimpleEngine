#version 330 core

layout(location = 0) in vec3 vp; // Input vertex position
out vec3 pos; // Output position to the fragment shader

uniform mat4 transform; // Uniform matrix for transformations

void main()
{
    gl_Position = transform * vec4(vp, 1.0); // Apply transformation and set the vertex position
    pos = vp; // Pass the vertex position to the fragment shader
}