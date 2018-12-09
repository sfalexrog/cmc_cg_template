#version 330


in vec4 vPos;
in vec3 vNorm;
in vec2 vUv;

out vec4 Color;

void main()
{
    Color = vec4((vNorm + vec3(1.0, 1.0, 1.0)) / 2.0, 1.0);
}
