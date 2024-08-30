#include "util.h"

#define numVAOS 1

GLuint vao[numVAOS];
float x{};
float inc{0.01};
GLuint offsetLocation;

void init(GLFWwindow* window) {
  renderingProgram = createShaderProgram();
  glGenVertexArrays(numVAOS, vao);
  glBindVertexArray(vao[0]);

  GLuint offsetLocation = glGetUniformLocation(renderingProgram, "offset");
}

void display(GLFWwindow* window, double currentTime) {
  if (x > 1.0f) inc = -0.01;
  else if (x < -1.0f) inc = 0.01;
  x += inc;
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);

  glUseProgram(renderingProgram);
  glProgramUniform1f(renderingProgram, offsetLocation, x);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
  // initializing glfw
  if (!glfwInit()) {glfwTerminate(); return 1;}
  // hinting that the system should be able to support opengl 4.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // initializing window and checking for erros
  GLFWwindow* window = glfwCreateWindow(600, 600, "chapter2-program1", NULL, NULL);
  if (!window) {glfwTerminate(); return 1;}
  // making a valid opengl context
  glfwMakeContextCurrent(window);
  // initializing GLEW after making a valid opengl context
  if (glewInit() != GLEW_OK) {glfwTerminate(); return 1;}
  init(window);
  glfwSwapInterval(1);

  // game Loop
  while (!glfwWindowShouldClose(window)) {
    display(window, glfwGetTime());
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // cleaning up and closing the application
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
