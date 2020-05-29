#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 TexCoord;

uniform mat4 u_Transform;
uniform vec4 u_TexTransform;
uniform float u_ElapsedTime;


void main()
{
    float magnitude = sin(u_ElapsedTime * 10.0) * 0.05;
    float row = floor(a_Position.y / 0.001);
    gl_Position = u_Transform * vec4(a_Position, 1.0);
    gl_Position.x += sin(row / 100.0) * magnitude;
    TexCoord = vec2(
        a_TexCoord.x * u_TexTransform.z + u_TexTransform.x, 
        a_TexCoord.y * u_TexTransform.w + u_TexTransform.y);
}