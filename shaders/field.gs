#version 450 core
layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 ourColor;

void createPrimitive(vec4 position)
{    
    ourColor = gs_in[0].color;
    gl_Position = position + vec4(-0.02, -0.02, 0.0, 0.0);
    EmitVertex();   
    gl_Position = position + vec4( 0.02, -0.02, 0.0, 0.0);
    EmitVertex();
    gl_Position = position + vec4(-0.02,  0.02, 0.0, 0.0);
    EmitVertex();
    gl_Position = position + vec4( 0.02,  0.02, 0.0, 0.0);
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.04, 0.0, 0.0);
    EmitVertex();
    EndPrimitive();
}

void main() {    
    createPrimitive(gl_in[0].gl_Position);
}  
