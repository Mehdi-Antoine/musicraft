//#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
//#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
//#include <glimac/glm.hpp>
//#include <glimac/Image.hpp>

using namespace glimac;

struct SquareProgram {
  
    Program m_Program;

    GLint uPMatrix,
          uVMatrix;

    GLint uKd,
          uKs,
          uShininess;

    GLint uLightPos,
          uLightIntensity;

    GLint uCameraPos;

    GLint uTexture;

    SquareProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/square/square.vs.glsl",
                              applicationPath.dirPath() + "shaders/square/square.gs.glsl",
                              applicationPath.dirPath() + "shaders/square/square.fs.glsl")) {

        uVMatrix   = glGetUniformLocation(m_Program.getGLId(), "uVMatrix");
        uPMatrix   = glGetUniformLocation(m_Program.getGLId(), "uPMatrix");

        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");

        uLightPos = glGetUniformLocation(m_Program.getGLId(), "uLightPos_vs");
        uLightIntensity =  glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");

        uCameraPos =  glGetUniformLocation(m_Program.getGLId(), "uCameraPos");
        
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");

    }
};