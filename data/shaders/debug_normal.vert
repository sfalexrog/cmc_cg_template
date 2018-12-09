#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec3 uv;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec4 vPos;
out vec3 vNorm;
out vec3 vUv;

void main()
{
    mat4 mvp = Projection * View * Model;
    vPos = mvp * vec4(pos, 1.0);
    gl_Position = vPos;
    vNorm = norm;
    vUv = uv;
}
