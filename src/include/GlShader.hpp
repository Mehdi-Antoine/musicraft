#pragma once

#include <vector>

#include <GL/glew.h>
#include <string>

#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

#include "GlUniform.hpp"


using namespace glimac;

enum ShaderProgram{ 
  CUBE = 0, 
  SQUARE = 1
};

enum UniformType{ 
  VEC3, 
  MAT4,
  FLOAT
};


class GlShader{
private:
  Program m_program;
  FilePath m_dir_path;
  std::string m_file;
  std::vector <GlUniform *> m_uniforms;

public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

  GlShader(FilePath dir_path, const std::string & file);
  GlShader(const GlShader & shader);
  ~GlShader();

//-------------------------------------------------FUNCTIONS----------------------------------------------------

  void useShader() const;

  GLuint getProgramId() const;

  void linkUniform(UniformType uniform_type, const char* uniform_name);

};