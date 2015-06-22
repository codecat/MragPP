#version 130

in vec2 s_vTexCoord;

out vec4 s_colOut;

uniform float s_fFrameCount;
uniform sampler2DRect s_texSampler;

void main()
{
  float f = 0.5 + sin(s_fFrameCount / 20) * 0.5;
  vec4 col = vec4(1, f, f, 1);
  //s_colOut = col;
  s_colOut = col * texture(s_texSampler, s_vTexCoord * textureSize(s_texSampler));
}
