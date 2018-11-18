#version 330

in vec2 vPos;
in vec2 texCoord;

out vec2 vTexCoord;

void main()
{
    gl_Position = vec4(vPos, 0.0, 1.0);
    vTexCoord = texCoord;
}
