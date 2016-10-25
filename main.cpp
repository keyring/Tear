#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char *description)
{
  fprintf(stderr, "TxxE Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

}


int main(void)
{

  glfwSetErrorCallback(error_callback);
  if(!glfwInit()){
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(800, 600, "Txx", NULL, NULL);
  if(!window){
    glfwTerminate();
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  //    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window)){
      glClear(GL_COLOR_BUFFER_BIT);

      glfwSwapBuffers(window);

      glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
