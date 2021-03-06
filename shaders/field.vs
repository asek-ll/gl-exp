#version 450 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in float aColor;

out VS_OUT {
    vec4 color;
} vs_out;

void main()
{
    gl_Position = vec4(aPos.x/10-0.5, aPos.y/10-0.9, 0.0, 1.0);
    vs_out.color = vec4(aColor, aColor, aColor, 0.5);
}
