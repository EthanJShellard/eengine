#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform vec2 u_TilingRatios;
uniform float u_Alpha;

varying vec2 v_TexCoord;
varying vec3 v_Normal;
varying vec3 v_FragPos;

void main()
{
  vec3 lightPos = vec3(10, 10, 10);
  vec3 diffColor = vec3(1, 1, 1);
  vec3 ambient = vec3(0.2, 0.2, 0.2);

  vec3 N = normalize(v_Normal);
  vec3 lightDir = normalize(lightPos - v_FragPos);

  float diff = max(dot(N, lightDir), 0.0);
  vec3 diffuse = diffColor * diff;

  vec3 light = max(diffuse, ambient);
  vec4 tex = texture2D(u_Texture, u_TilingRatios * v_TexCoord);

  tex *= u_Color;

  gl_FragColor = tex * vec4(light, u_Alpha);
}

