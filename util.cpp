#include "util.h"

GLuint renderingProgram;

std::string readFile(std::string filePath) {
  std::ifstream file{filePath};

  if (!file.is_open()) throw std::runtime_error(filePath.append(" could not be opened "));
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

void printShaderLog(GLenum shaderType, GLuint shader) {
  GLint len{};
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  if (len == 0) {return;}
  char* infoLog = new char[len];
  glGetShaderInfoLog(shader, len, NULL, infoLog);
  std::cout << "error occur in the ";
  switch(shaderType) {
    case GL_VERTEX_SHADER: std::cout << "vertex "; break;
    case GL_FRAGMENT_SHADER: std::cout << "fragment "; break;
    case GL_GEOMETRY_SHADER: std::cout << "geometry "; break;
  }
  std::cout << "shader: " << infoLog << std::endl;
  delete[] infoLog;
  return;
}

void printProgramLog(GLuint program) {
  GLint len{};
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
  if (len == 0) return;
  char* infoLog = new char[len];
  glGetProgramInfoLog(program, len, NULL, infoLog);
  std::cout << "error occurr in the linking stage: " << infoLog << std::endl;
  delete[] infoLog;
  return;
}

bool checkOpenglError() {
  bool foundError = false;
  GLint glErr = glGetError();
  while (glErr != GL_NO_ERROR) {
    foundError = true;
    std::cout << "glError: " << glErr << std::endl;
    glErr = glGetError();
  }
  return foundError;
}

GLuint createShader(GLenum shaderType, std::string shaderPath) {
  GLint shaderStatus{};
  std::string shaderStr = readFile(shaderPath);
  const char* shaderSource = shaderStr.c_str();

  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderSource, NULL);
  glCompileShader(shader);
  checkOpenglError();
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderStatus);
  if (shaderStatus != GL_TRUE) printShaderLog(shaderType, shader);

  return shader;
}

GLuint createShaderProgram() {
  GLint progStatus{};

  GLuint vShader = createShader(GL_VERTEX_SHADER, "./vertshader.glsl");
  GLuint fShader = createShader(GL_FRAGMENT_SHADER, "./fragshader.glsl");

  GLuint fProgram = glCreateProgram();
  glAttachShader(fProgram, vShader);
  glAttachShader(fProgram, fShader);
  glLinkProgram(fProgram);
  checkOpenglError();
  glGetProgramiv(fProgram, GL_LINK_STATUS, &progStatus);
  if (progStatus != GL_TRUE) printProgramLog(fProgram);

  return fProgram;
}
