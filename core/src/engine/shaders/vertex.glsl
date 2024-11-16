#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 WorldNormal;

uniform mat4 transform;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    TexCoords = aTexCoords;
    WorldNormal = aNormal * transpose(inverse(mat3(transform)));
    FragPos = vec3(transform * vec4(aPos, 1.0));


    gl_Position = projectionMatrix * viewMatrix * transform * vec4(aPos, 1.0);
 
}