#version 330

in vec2 in_vPos;
in vec2 in_vTexCoord;

out vec2 s_vTexCoord;

void main()
{
  gl_Position = vec4(in_vPos, 0, 1);
  s_vTexCoord = (in_vTexCoord + vec2(1, 1)) / 2;
}
