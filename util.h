#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

extern GLuint renderingProgram;

std::string readFile(std::string filePath);
void printShaderLog(GLenum shaderType, GLuint shader);
void printProgramLog(GLuint program);
bool checkOpenglError();
GLuint createShader(GLenum shaderType, std::string shaderPath);
GLuint createShaderProgram();
