
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "Tear.h"
#include "SpriteRenderer.h"


#define UPDATE_INTERVAL 10  // 10ms

Tear::Engine *g_tear_engine;


// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>\n"
"out vec2 TexCoords;\n"
"uniform mat4 mv;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"    TexCoords = vertex.zw;\n"
"    gl_Position = projection * mv * vec4(vertex.xy, 0.0, 1.0);\n"
"}";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec2 TexCoords;\n"
"out vec4 color;\n"
"uniform sampler2D image;\n"
"uniform vec3 scolor;\n"
"void main()\n"
"{\n"
"    color = vec4(scolor, 1.0) * texture(image, TexCoords);\n"
"}";


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

static GLuint _shader_create(const GLchar *vs, const GLchar *fs)
{
    // Build and compile our shader program
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, NULL);
    glCompileShader(vertexShader);
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, NULL);
    glCompileShader(fragmentShader);
    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

static GLuint _texture_create(const char *filepath)
{
    // Load image and create a texture 
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    int w, h, n;
    unsigned char *data = stbi_load(filepath, &w, &h, &n, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
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

    // // Set up vertex data (and buffer(s)) and attribute pointers
    // GLfloat vertices[] = {
    //     // Positions          // Colors           // Texture Coords
    //     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
    //     -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Top Left 
    // };
    // GLuint indices[] = {  // Note that we start from 0!
    //     0, 1, 3, // First Triangle
    //     1, 2, 3  // Second Triangle
    // };
    // GLuint VBO, VAO, EBO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // // Position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    // glEnableVertexAttribArray(0);
    // // Color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    // glEnableVertexAttribArray(1);
    // // TexCoord attribute
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    // glEnableVertexAttribArray(2);

    // glBindVertexArray(0); // Unbind VAO


 //   glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Uncommenting this call will result in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if(!g_tear_engine->init(window_width, window_height)){
        std::cout << "game engine init fail" << std::endl;
        return 0;
    }

    GLuint shaderProgram = _shader_create(vertexShaderSource, fragmentShaderSource);
    GLuint texture1 = _texture_create("../../media/cat.png");
    GLuint texture2 = _texture_create("../../media/logo.png");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(window_width), static_cast<GLfloat>(window_height), 0.0f, -1.0f, 1.0f);
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

    Tear::SpriteRenderer *sprite = new Tear::SpriteRenderer();
    sprite->setShader(shaderProgram);
    sprite->setTexture(texture1);

    double lastTime = glfwGetTime();
    double timestamp = 0.0;

    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();

        double nowTime = glfwGetTime();
        double delta = nowTime - lastTime;
        timestamp += delta;
        lastTime = nowTime;

        if(timestamp >= UPDATE_INTERVAL){
            g_tear_engine->update();
            timestamp -= UPDATE_INTERVAL;
        }

        // Render
        // Clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        g_tear_engine->render();

        sprite->draw();

        // Draw our first triangle
        // glUseProgram(shaderProgram);

        // // Bind Textures using texture units
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, texture1);
        // glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, texture2);
        // glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);

        // glBindVertexArray(VAO);
        // //glDrawArrays(GL_TRIANGLES, 0, 6);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0);

		glfwSwapBuffers(window);

    }

    delete sprite;
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
