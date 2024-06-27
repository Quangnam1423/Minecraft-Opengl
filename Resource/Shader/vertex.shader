#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textCoords;
layout (location = 2) in int id;

out vec2 TexCoord;
out vec3 cube_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec3 hash31(float p) {
    vec3 p3 = fract(vec3(p * 21.2f) * vec3(0.1031f, 0.1030f, 0.0973f));
    p3 += dot(p3, p3.yzx + 33.33f);
    return fract((p3.xxy + p3.yzz) * p3.zyx) + 0.05f;
}

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoord = textCoords;
    cube_color = hash31(id);
}