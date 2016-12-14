
#include "Tear.h"

#include <GLFW/glfw3.h>


Tear::Engine *g_tear_engine;

static void _glfw_error_callback(int error, const char *description)
{
    std::cout << "glfw Error: " << description << std::endl;
}

static void _glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(void)
{
    glfwSetErrorCallback(_glfw_error_callback);
    if(!glfwInit()){
        return -1;
    }

    g_tear_engine = new Tear::Engine();

    if(!game_load()){
        std::cout << "game load fail" << std::endl;
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    int window_width = g_tear_engine->getWindowWidth();
    int window_height = g_tear_engine->getWindowHeight();

    GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Tear Engine", NULL, NULL);
    if(!window){
        std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, _glfw_key_callback);

    glewExperimental = GL_TRUE;

    glewInit();

    glViewport(0, 0, window_width, window_height);

    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Uncommenting this call will result in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if(!g_tear_engine->init(window_width, window_height)){
        std::cout << "game engine init fail" << std::endl;
        return 0;
    }

    double update_interval = g_tear_engine->getUpdateInterval();
    double lastTime = glfwGetTime();
    double timestamp = 0.0;

    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();

        double nowTime = glfwGetTime();
        double delta = nowTime - lastTime;
        timestamp += delta;
        lastTime = nowTime;

        if(timestamp >= update_interval){
            g_tear_engine->update(update_interval);
            timestamp -= update_interval;
        }

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        g_tear_engine->render();

		glfwSwapBuffers(window);

    }

    // Properly de-allocate all resources once they've outlived their purpose
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);

    g_tear_engine->close();
    delete g_tear_engine;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
