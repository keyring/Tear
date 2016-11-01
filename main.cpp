#include "Tear.h"

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstdio>

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "glfw Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

}

Tear::Engine *g_tear_engine;

int main(void)
{
    glfwSetErrorCallback(error_callback);
    if(!glfwInit()){
        return -1;
    }

    g_tear_engine = new Tear::Engine();

    if(!game_load()){
        fprintf(stderr, "game load fail\n");
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(g_tear_engine->getWindowWidth(), g_tear_engine->getWindowHeight(), "Tear Engine", nullptr, nullptr);
    if(!window){
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;

    glewInit();

    glViewport(0, 0, g_tear_engine->getWindowWidth(), g_tear_engine->getWindowHeight());

    if(!g_tear_engine->init(g_tear_engine->getWindowWidth(), g_tear_engine->getWindowHeight())){
        fprintf(stderr, "game engine init fail\n");
        return 0;
    }

    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();

        g_tear_engine->update();

        glfwSwapBuffers(window);

    }
    g_tear_engine->close();
    delete g_tear_engine;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
