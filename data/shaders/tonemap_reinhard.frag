#version 330

uniform sampler2D frame;
uniform float exposition;
uniform float gamma = 2.2;

in vec2 vTexCoord;

out vec4 Color;

void main()
{
    vec3 texColor = texture(frame, vTexCoord).xyz;
    texColor *= exposition;
    texColor = texColor / (1.0 + texColor);
    vec3 gammaColor = pow(texColor, vec3(1.0 / gamma));
    Color = vec4(gammaColor, 1.0);
}
