#include "Tear.h"

#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstdio>

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

  Tear::Engine *g_tear_engine = new Tear::Engine();

  if(!game_load()){
    fprintf(stderr, "game load fail\n");
    return 0;
  }

  GLFWwindow *window = glfwCreateWindow(g_tear_engine->getWindowWidth(), g_tear_engine->getWindowHeight(), "Tear Engine", NULL, NULL);
  if(!window){
    glfwTerminate();
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  //    glfwMakeContextCurrent(window);

  if(g_tear_engine->init(g_tear_engine->getWindowWidth(), g_tear_engine->getWindowHeight())){
    fprintf(stderr, "game engine init fail\n");
    return 0;
  }


    while(!glfwWindowShouldClose(window)){
      glClear(GL_COLOR_BUFFER_BIT);

      glfwSwapBuffers(window);

      glfwPollEvents();

      g_tear_engine->update();
    }

    g_tear_engine->close();
    delete g_tear_engine;

    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}
