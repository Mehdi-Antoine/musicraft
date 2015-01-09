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


//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//----------------------------------------------CLASS GL SHADER-------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

class GlShader{
private:
  Program m_program;
  FilePath m_dir_path;
  std::string m_file;

public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

  GlShader(FilePath dir_path, const std::string & file);
  GlShader(const GlShader & shader);
  ~GlShader();

//-------------------------------------------------FUNCTIONS----------------------------------------------------

  void useShader() const;

  GLuint getProgramId() const;

  void attachTexture(const char* uniform_name, int binding) const;

};

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------CLASS GL SHADER 2D------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

class GlShader2D{
private:
  Program m_program;
  FilePath m_dir_path;
  std::string m_file;

public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

  GlShader2D(FilePath dir_path, const std::string & file);
  GlShader2D(const GlShader2D & shader);
  ~GlShader2D();

//-------------------------------------------------FUNCTIONS----------------------------------------------------

  void useShader() const;

  GLuint getProgramId() const;

  void attachTexture(const char* uniform_name, int binding) const;

};