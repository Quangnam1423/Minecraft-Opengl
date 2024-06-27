#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 cube_color;

uniform sampler2D texture;


void main()
{
    FragColor = vec4(cube_color , 1.0f);
}