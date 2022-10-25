#include <GL/glew.h>

#include <string>

#include "sys/String.h"
#include "sys/Ptr.h"
#include "sys/Zero.h"

namespace rend
{

struct Shader : sys::EnablePtr
{
  Shader(const char* _vertPath, const char* _fragPath);
  Shader(const std::string& _vertPath, const std::string& _fragPath);
  Shader(const sys::String& _vertPath, const sys::String& _fragPath);
  Shader();
  ~Shader();

  void LoadShaders(const char* _vertPath, const char* _fragPath);

  GLuint id();
  GLint projectionLoc();
  GLint modelLoc();
  GLint viewLoc();
  GLint texture0Loc();
  GLint texture1Loc();
  GLint colorLoc();

private:
  sys::Zero<GLuint> m_id;
  sys::Zero<GLint> m_projectionLoc;
  sys::Zero<GLint> m_viewLoc;
  sys::Zero<GLint> m_modelLoc;
  sys::Zero<GLint> m_texture0Loc;
  sys::Zero<GLint> m_texture1Loc;
  sys::Zero<GLint> m_colorLoc;

  sys::String m_vertSrc;
  sys::String m_fragSrc;

  Shader(const Shader& _copy);
  Shader& operator=(const Shader& _other);

};

}
