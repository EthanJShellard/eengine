#include <fstream>

#include "Model.h"

#include "sys/File.h"
#include "sys/Ptr.h"

namespace rend
{


Model::Model(const sys::String& _path)
{
  load(_path);
}

static void split_string_whitespace(const sys::String& _input,
  sys::Vector<sys::String>& _output)
{
  _output.clear();
  sys::String curr;

  for(size_t ci = 0; ci < _input.length(); ++ci)
  {
    char c = _input[ci];

    if(c == '\r' || c == '\n' || c == ' ' || c == '\t')
    {
      if(curr.length() > 0)
      {
        _output.push(curr);
        curr = "";
      }
    }
    else
    {
      curr += c;
    }
  }

  if(curr.length() > 0)
  {
    _output.push(curr);
  }
}

static void split_string(const sys::String& _input, char splitter,
  sys::Vector<sys::String>& _output)
{
  _output.clear();
  sys::String curr;

  for(size_t ci = 0; ci < _input.length(); ++ci)
  {
    char c = _input[ci];

    if(c == splitter)
    {
      _output.push(curr);
      curr = "";
    }
    else
    {
      curr += c;
    }
  }

  if(curr.length() > 0)
  {
    _output.push(curr);
  }
}

void Model::LoadMaterials(const sys::String& _path, std::unordered_map<std::string, Material>& _mats)
{
    std::ifstream file(_path.unsafe_raw());
    std::string currentLine;
    Material currentMaterial;

    if (!file.is_open()) 
    {
        throw std::exception();
    }

    while (!file.eof()) 
    {
        std::getline(file, currentLine);
        sys::Vector<sys::String> tokens;
        split_string_whitespace(currentLine.c_str(), tokens);

        // If line is empty, continue
        if (tokens.size() < 1) continue;

        if (tokens[0] == "newmtl") 
        {
            if (currentMaterial.name.length() != 0) 
            {
                auto itr = _mats.find(std::string(currentMaterial.name.unsafe_raw()));
                if (itr != _mats.end()) 
                {
                    // Overwrite!
                    itr->second.name = currentMaterial.name;
                    itr->second.relativePath = currentMaterial.relativePath;
                }
                else 
                {
                    // Create!
                    _mats.insert(std::pair<std::string, Material>(std::string(itr->second.name.unsafe_raw()), itr->second));
                }
            }

            currentMaterial.name = tokens[1];
            currentMaterial.relativePath = "";
        }
        else if (tokens[0] == "map_Kd") 
        {
            std::string newPath = std::string(_path.unsafe_raw());
            newPath = newPath.substr(0, newPath.find_last_of('\\') + 1);
            newPath.append(tokens[1].unsafe_raw());
            currentMaterial.relativePath = newPath.c_str();
        }
    }
}

void Model::load(const sys::String& _path)
{
  sys::String line;
  sys::Vector<sys::String> tokens;
  sys::Vector<vec3> positions;
  sys::Vector<vec2> texcoords;
  sys::Vector<vec3> normals;
  sys::Vector<sys::String> innerTokens;
  std::unordered_map<std::string, Material> mats;

  sys::String pn("Untitled");
  sys::Ptr<Part> part;
  sys::Ptr<MaterialGroup> mg;

  for(sys::File file(_path); file.read_line(line);)
  {
    if(line.length() < 1) continue;

    split_string_whitespace(line, tokens);

    if(tokens[0] == "v" && tokens.size() >= 4)
    {
      vec3 p(
        atof(tokens[1].unsafe_raw()),
        atof(tokens[2].unsafe_raw()),
        atof(tokens[3].unsafe_raw()));

      positions.push(p);
    }
    else if(tokens[0] == "vt" && tokens.size() >= 3)
    {
      vec2 p(
        atof(tokens[1].unsafe_raw()),
        atof(tokens[2].unsafe_raw()));

      texcoords.push(p);
    }
    else if(tokens[0] == "vn" && tokens.size() >= 4)
    {
      vec3 n(
        atof(tokens[1].unsafe_raw()),
        atof(tokens[2].unsafe_raw()),
        atof(tokens[3].unsafe_raw()));

      normals.push(n);
    }
    else if(tokens[0] == "f" && tokens.size() >= 4)
    {
      Face f;
      split_string(tokens[1], '/', innerTokens);
      f.a.position = positions[atoi(innerTokens[0].unsafe_raw()) - 1];
      if(texcoords.size()) f.a.texcoord = texcoords[atoi(innerTokens[1].unsafe_raw()) - 1];
      if(normals.size()) f.a.normal = normals[atoi(innerTokens[2].unsafe_raw()) - 1];
      split_string(tokens[2], '/', innerTokens);
      f.b.position = positions[atoi(innerTokens[0].unsafe_raw()) - 1];
      if(texcoords.size()) f.b.texcoord = texcoords[atoi(innerTokens[1].unsafe_raw()) - 1];
      if(normals.size()) f.b.normal = normals[atoi(innerTokens[2].unsafe_raw()) - 1];
      split_string(tokens[3], '/', innerTokens);
      f.c.position = positions[atoi(innerTokens[0].unsafe_raw()) - 1];
      if(texcoords.size()) f.c.texcoord = texcoords[atoi(innerTokens[1].unsafe_raw()) - 1];
      if(normals.size()) f.c.normal = normals[atoi(innerTokens[2].unsafe_raw()) - 1];

      if(!part)
      {
        part = m_parts.emplace();
        part->name = pn;
        part->color = vec4(1, 1, 1, 1);
        printf("%s\n", part->name.unsafe_raw());
      }

      if(!mg) mg = part->mgs.emplace();

      mg->mesh.add(f);
      m_faces.push(f);

      if(tokens.size() >= 5)
      {
        f.b = f.a;
        f.a = f.c;
        f.c = f.b;

        split_string(tokens[4], '/', innerTokens);
        f.b.position = positions[atoi(innerTokens[0].unsafe_raw()) - 1];
        if(texcoords.size()) f.b.texcoord = texcoords[atoi(innerTokens[1].unsafe_raw()) - 1];
        if(normals.size()) f.b.normal = normals[atoi(innerTokens[2].unsafe_raw()) - 1];

        mg->mesh.add(f);
        m_faces.push(f);
      }
    }
    else if(tokens[0] == "g" || tokens[0] == "o")
    {
      part = NULL;
      mg = NULL;

      if(tokens.size() >= 2)
      {
        pn = tokens[1];
      }
    }
    else if (tokens[0] == "mtllib") //Load material library
    {
        std::string stringPath = std::string(_path.unsafe_raw());
        std::string newPath = stringPath.substr(0, stringPath.find_last_of('/') + 1);
        newPath.append(tokens[1].unsafe_raw());
        LoadMaterials(newPath.c_str(), mats);
    }
    else if (tokens[0] == "usemtl") 
    {
        if (!mg) 
        {
            throw std::exception();
        }

        auto itr = mats.find(std::string(tokens[1].unsafe_raw()));
        if (itr == mats.end()) 
        {
            throw std::exception();
        }
        sys::Ptr<Texture> tex;
        mg->texture = new Texture(itr->second.relativePath);
    }
  }

  center_parts();
}

void Model::center_parts()
{
  for(sys::List<Part>::Iterator pit = m_parts.begin();
    pit != m_parts.end(); ++pit)
  {
    vec3 minPos(FLT_MAX, FLT_MAX, FLT_MAX);
    vec3 maxPos(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for(sys::List<MaterialGroup>::Iterator mit = pit->mgs.begin();
      mit != pit->mgs.end(); ++mit)
    {
      for(sys::Vector<Face>::Iterator fit = mit->mesh.faces()->begin();
        fit != mit->mesh.faces()->end(); ++fit)
      {
        minPos = min(minPos, fit->a.position);
        minPos = min(minPos, fit->b.position);
        minPos = min(minPos, fit->c.position);

        maxPos = max(maxPos, fit->a.position);
        maxPos = max(maxPos, fit->b.position);
        maxPos = max(maxPos, fit->c.position);
      }
    }

    pit->offset = (minPos + maxPos) / 2.0f;

/*
    for(sys::List<MaterialGroup>::Iterator mit = pit->mgs.begin();
      mit != pit->mgs.end(); ++mit)
    {
      for(sys::Vector<Face>::Iterator fit = mit->mesh.faces()->begin();
        fit != mit->mesh.faces()->end(); ++fit)
      {
        fit->a.position -= pit->offset;
        fit->b.position -= pit->offset;
        fit->c.position -= pit->offset;
      }
    }
*/
  }
}

bool Model::intersect(const Ray& _ray) const
{
  for(sys::List<Part>::Iterator pit = m_parts.begin();
    pit != m_parts.end(); ++pit)
  {
    Ray r(_ray);

    for(sys::List<MaterialGroup>::Iterator mit = pit->mgs.begin();
      mit != pit->mgs.end(); ++mit)
    {
      if(mit->mesh.intersect(r)) return true;
    }
  }

  return false;
}

sys::Ptr<Part> Model::intersect(const Ray& _ray, float& _distance) const
{
  sys::Ptr<Part> rtn;

  _distance = FLT_MAX;

  for(sys::List<Part>::Iterator pit = m_parts.begin();
    pit != m_parts.end(); ++pit)
  {
    Ray r(_ray);

    for(sys::List<MaterialGroup>::Iterator mit = pit->mgs.begin();
      mit != pit->mgs.end(); ++mit)
    {
      float nd = FLT_MAX;

      if(mit->mesh.intersect(r, nd))
      {
        if(nd < _distance)
        {
          Part& p = *pit;
          rtn = &p;
          _distance = nd;
        }
      }
    }
  }

  return rtn;
}

sys::List<Part>::Iterator Model::partsBegin()
{
  return m_parts.begin();
}

sys::List<Part>::Iterator Model::partsEnd()
{
  return m_parts.end();
}

void Model::color(vec4 _color)
{
  for(sys::List<Part>::Iterator it = m_parts.begin(); it != m_parts.end(); ++it)
  {
    it->color = _color;
  }
}

}

