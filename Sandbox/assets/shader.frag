#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform float u_ElapsedTime;

void main()
{
    vec2 NewCoord = TexCoord;
    float magnitude = sin(u_ElapsedTime * 10.0) * 0.05;
    float row = floor(TexCoord.y / 0.001);
    NewCoord.x += sin(row / 100.0) * magnitude;
    FragColor = texture(u_Texture, NewCoord);
}