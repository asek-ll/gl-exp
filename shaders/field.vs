#version 450 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in float aColor;

out VS_OUT {
    vec4 color;
} vs_out;

vec4 rgbGen(in float h)
{
    float b = abs(h * 5.0 - 3.0) - 1.0;
    float g = 2.0 - abs(h * 5.0 - 2.0);
    float r = 2.0 - abs(h * 5.0 - 4.0);
    return vec4(clamp(vec3(r,g,b), 0.0, 1.0), 1.0);
}

void main()
{
    gl_Position = vec4(aPos.x/10-0.5, aPos.y/10-0.9, 0.0, 1.0);
    vs_out.color = rgbGen(aColor);
}
