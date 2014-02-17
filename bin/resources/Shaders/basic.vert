attribute vec3 positions;

uniform mat4 WorldViewProjection;

void main() {
    //gl_Position = WorldViewProjection * vec4(positions, 1.0);
    gl_Position = vec4(positions, 1.0);
}
