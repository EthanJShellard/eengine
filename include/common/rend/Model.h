#ifndef REND_MODEL
#define REND_MODEL

#include "Mesh.h"
#include "Texture.h"
#include "rendmath.h"

#include <memory>
#include <unordered_map>

#include "sys/Ptr.h"
#include "sys/List.h"
#include "sys/String.h"
#include "sys/Vector.h"
#include "sys/Zero.h"

struct Texture;

namespace rend
{

// KLUUUUDGE
struct Material
{
    float m_specularHighlights;
    glm::vec3 m_ambientColour;
    glm::vec3 m_diffuseColour;
    glm::vec3 m_specularColour;
    glm::vec3 m_emissiveColour;
    float m_opticalDensity;
    float m_dissolve;
    int m_illuminationModel;
    sys::Ptr<Texture> m_texture;

};

struct MaterialGroup : sys::EnablePtr
{
  Mesh mesh;
  sys::Ptr<Texture> texture;
};

struct Part : sys::EnablePtr
{
  sys::String name;
  sys::List<MaterialGroup> mgs;
  vec3 offset;
  vec4 color;
};

struct Model : sys::EnablePtr
{
  Model(const sys::String& _path);

  sys::List<Part>::Iterator partsBegin();
  sys::List<Part>::Iterator partsEnd();

  bool intersect(const Ray& _ray) const;
  sys::Ptr<Part> intersect(const Ray& _ray, float& _distance) const;
  void color(vec4 _color);

private:
  sys::List<Texture> m_textures;
  sys::List<Part> m_parts;
  sys::Vector<Face> m_faces;

  void load(const sys::String& _path);
  void center_parts();

  void LoadMaterials(const std::string _path, std::string _currentLine, std::unordered_map<std::string, std::shared_ptr<Material> >& _map);
};

}

#endif // REND_MODEL

