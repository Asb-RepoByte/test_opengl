#version 430

uniform float offset;

void main() {
    if (gl_VertexID == 0) {
        gl_Position = vec4(-0.5 + offset, -0.5, 0.0, 1.0);
    } else if (gl_VertexID == 1) {
        gl_Position = vec4(0.5 + offset, -0.5, 0.0, 1.0);
    } else {
        gl_Position = vec4(0.0 + offset, 0.5, 0.0, 1.0);
    }
}
