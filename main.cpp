#include "Tear.h"

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>\n"
"out vec2 TexCoords;\n"
"uniform mat4 model;\n"
"uniform mat4 projection;\n"
"uniform vec4 frameOffset;\n"
"void main()\n"
"{\n"
"    TexCoords = vec2(frameOffset.x+vertex.z*frameOffset.z, frameOffset.y+vertex.w*frameOffset.w);\n"
"    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
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

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

Tear::SpriteRenderer *sprite;
Tear::SpriteRenderer *animate_sprite;


bool game_load()
{
	g_tear_engine->setWindowWidth(WINDOW_WIDTH);
	g_tear_engine->setWindowHeight(WINDOW_HEIGHT);
    return true;
}

bool game_init()
{
    GLuint shaderProgram = g_tear_engine->_shader_create(vertexShaderSource, fragmentShaderSource);
    GLuint texture1 = g_tear_engine->_texture_create("../../media/cat.png");
    GLuint texture2 = g_tear_engine->_texture_create("../../media/animation.png");

	glUseProgram(shaderProgram);
	glm::mat4 projection = glm::ortho(0.f, 1.f*WINDOW_WIDTH, 1.f*WINDOW_HEIGHT, 0.f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    sprite = new Tear::SpriteRenderer();
    sprite->setShader(shaderProgram);
	sprite->setTexture(texture1);
	sprite->setPos(glm::vec2(100, 100));
	sprite->setSize(glm::vec2(180.0f, 180.0f));
	sprite->setColor(glm::vec3(1.0f, 0.0f, 0.0f));

    animate_sprite = new Tear::SpriteRenderer();
    animate_sprite->setShader(shaderProgram);
    animate_sprite->setTexture(texture2);
    animate_sprite->setPos(glm::vec2(400, 100));
    animate_sprite->setSize(glm::vec2(132, 94));
    animate_sprite->setTotalFrames(16);
    animate_sprite->setColFrames(4);
    animate_sprite->setFrameTimer(0.3);

    return true;
}

void game_update(double dt)
{
	sprite->update(dt);
    animate_sprite->update(dt);
}

void game_render()
{
    sprite->draw();
    animate_sprite->draw();
}

void game_end()
{
    delete sprite;
    delete animate_sprite;
}
