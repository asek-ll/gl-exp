#version 450 core
layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in VS_OUT { vec4 color; }
gs_in[];

out vec4 ourColor;

void createPrimitive(vec4 position) {
  ourColor = gs_in[0].color;
  gl_Position = position + vec4(-0.04, -0.04, 0.0, 0.0);
  EmitVertex();
  gl_Position = position + vec4(0.05, -0.04, 0.0, 0.0);
  EmitVertex();
  gl_Position = position + vec4(-0.04, 0.05, 0.0, 0.0);
  EmitVertex();
  gl_Position = position + vec4(0.05, 0.05, 0.0, 0.0);
  EmitVertex();
  EndPrimitive();
}

void main() { createPrimitive(gl_in[0].gl_Position); }
