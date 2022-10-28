#include "Shader.h"

#include "sys/File.h"
#include "sys/Exception.h"

namespace rend
{

Shader::Shader(const sys::String& _vertPath, const sys::String& _fragPath) :
  m_projectionLoc(-1),
  m_viewLoc(-1),
  m_modelLoc(-1)
{
  sys::String line;

  for(sys::File file(_vertPath); file.read_line(line);)
  {
    m_vertSrc += line;
    m_vertSrc += '\n';
  }

  for(sys::File file(_fragPath); file.read_line(line);)
  {
    m_fragSrc += line;
    m_fragSrc += '\n';
  }
}

Shader::Shader(int _type) :
  m_projectionLoc(-1),
  m_viewLoc(-1),
  m_modelLoc(-1)
{
  if(_type != BASIC) throw sys::Exception("Invalid type");

  m_vertSrc += "uniform mat4 u_Projection;                         \n";
  m_vertSrc += "uniform mat4 u_View;                               \n";
  m_vertSrc += "uniform mat4 u_Model;                              \n";
  m_vertSrc += "                                                   \n";
  m_vertSrc += "attribute vec3 a_Position;                         \n";
  m_vertSrc += "attribute vec2 a_TexCoord;                         \n";
  m_vertSrc += "attribute vec3 a_Normal;                           \n";
  m_vertSrc += "                                                   \n";
  m_vertSrc += "varying vec2 v_TexCoord;                           \n";
  m_vertSrc += "varying vec3 v_Normal;                             \n";
  m_vertSrc += "varying vec3 v_FragPos;                            \n";
  m_vertSrc += "                                                   \n";
  m_vertSrc += "void main()                                        \n";
  m_vertSrc += "{                                                  \n";
  m_vertSrc += "  gl_Position = u_Projection * u_View * u_Model *  \n";
  m_vertSrc += "    vec4(a_Position, 1);                           \n";
  m_vertSrc += "                                                   \n";
  m_vertSrc += "  v_TexCoord = a_TexCoord;                         \n";
  m_vertSrc += "  v_Normal = vec3(u_Model * vec4(a_Normal, 0));    \n";
  m_vertSrc += "  v_FragPos = vec3(u_Model * vec4(a_Position, 1)); \n";
  m_vertSrc += "}                                                  \n";

  m_fragSrc += "uniform sampler2D u_Texture;                       \n";
  m_fragSrc += "uniform vec4 u_Color;                              \n";
  m_fragSrc += "                                                   \n";
  m_fragSrc += "varying vec2 v_TexCoord;                           \n";
  m_fragSrc += "varying vec3 v_Normal;                             \n";
  m_fragSrc += "varying vec3 v_FragPos;                            \n";
  m_fragSrc += "                                                   \n";
  m_fragSrc += "void main()                                        \n";
  m_fragSrc += "{                                                  \n";
  m_fragSrc += "  vec3 lightPos = vec3(10, 10, 10);                \n";
  m_fragSrc += "  vec3 diffColor = vec3(1, 1, 1);                  \n";
  m_fragSrc += "  vec3 ambient = vec3(0.2, 0.2, 0.2);              \n";
  m_fragSrc += "                                                   \n";
  m_fragSrc += "  vec3 N = normalize(v_Normal);                    \n";
  m_fragSrc += "  vec3 lightDir = normalize(lightPos - v_FragPos); \n";
  m_fragSrc += "                                                   \n";
  m_fragSrc += "  float diff = max(dot(N, lightDir), 0.0);         \n";
  m_fragSrc += "  vec3 diffuse = diffColor * diff;                 \n";
  m_fragSrc += "                                                   \n";
  m_fragSrc += "  vec3 light = max(diffuse, ambient);              \n";
  m_fragSrc += "  vec4 tex = texture2D(u_Texture, v_TexCoord);     \n";
  m_fragSrc += "                                                   \n";
  m_fragSrc += "  tex *= u_Color;                                  \n";
  m_fragSrc += "                                                   \n";
  m_fragSrc += "  gl_FragColor = tex * vec4(light, 1);             \n";
  m_fragSrc += "}                                                  \n";
}

Shader::~Shader()
{
  if(m_id)
  {
    glDeleteProgram(m_id);
  }
}

GLuint Shader::id()
{
  if(m_id) return m_id;

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  if(!vs) throw sys::Exception("Failed to create vertex shader");

  const GLchar *src = m_vertSrc.unsafe_raw();
  glShaderSource(vs, 1, &src, NULL);
  glCompileShader(vs);

  GLint success = 0;
  glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    GLchar infoLog[512] = {0};
    glGetShaderInfoLog(vs, 512, NULL, infoLog);
    sys::String err = "Failed to compile vertex shader: ";
    err += infoLog;

    throw sys::Exception(err);
  }

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  if(!fs) throw sys::Exception("Failed to create fragment shader");

  src = m_fragSrc.unsafe_raw();
  glShaderSource(fs, 1, &src, NULL);
  glCompileShader(fs);

  glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    GLchar infoLog[512] = {0};
    glGetShaderInfoLog(fs, 512, NULL, infoLog);
    sys::String err = "Failed to compile fragment shader: ";
    err += infoLog;

    throw sys::Exception(err);
  }

  m_id = glCreateProgram();
  if(!m_id) throw sys::Exception("Failed to create shader");

  glBindAttribLocation(m_id, 0, "a_Position");
  glBindAttribLocation(m_id, 1, "a_TexCoord");
  glBindAttribLocation(m_id, 2, "a_Normal");

  glAttachShader(m_id, vs);
  glAttachShader(m_id, fs);
  glLinkProgram(m_id);

  glDeleteShader(vs);
  glDeleteShader(fs);

  glGetProgramiv(m_id, GL_LINK_STATUS, &success);

  if(!success)
  {
    GLchar infoLog[512] = {0};
    glGetProgramInfoLog(m_id, 512, NULL, infoLog);
    sys::String err = "Failed to link shader: ";
    err += infoLog;

    throw sys::Exception(err);
  }

  m_projectionLoc = glGetUniformLocation(m_id, "u_Projection");
  m_viewLoc = glGetUniformLocation(m_id, "u_View");
  m_modelLoc = glGetUniformLocation(m_id, "u_Model");
  m_texture0Loc = glGetUniformLocation(m_id, "u_Texture");
  m_texture1Loc = glGetUniformLocation(m_id, "u_Texture1");
  m_colorLoc = glGetUniformLocation(m_id, "u_Color");

  return m_id;
}

GLint Shader::projectionLoc()
{
  return m_projectionLoc;
}

GLint Shader::modelLoc()
{
  return m_modelLoc;
}

GLint Shader::viewLoc()
{
  return m_viewLoc;
}

GLint Shader::texture0Loc()
{
  return m_texture0Loc;
}

GLint Shader::texture1Loc()
{
  return m_texture1Loc;
}

GLint Shader::colorLoc()
{
  return m_colorLoc;
}

}

