
#include "SpriteRenderer.h"

namespace Tear {

    SpriteRenderer::SpriteRenderer(glm::vec2 p, glm::vec2 s, GLfloat r, glm::vec3 c):
        position(p),
        size(s),
        rotate(r),
        color(c),
        vao(0),
        shader(0),
        texture2d(0)
    {

		GLuint vbo;
		GLfloat vertices[] = {
			//pos        //texture
			//-0.5f, 0.5f, 0.0f, 1.0f,
			//0.5f, -0.5f, 1.0f, 0.0f,
			//-0.5f, -0.5f, 0.0f, 0.0f,

			//-0.5f, 0.5f, 0.0f, 1.0f,
			//0.5f, 0.5f, 1.0f, 1.0f,
			//0.5f, -0.5f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
		};

		glGenVertexArrays(1, &this->vao);
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(this->vao);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLfloat*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
    }

    SpriteRenderer::~SpriteRenderer()
    {
        glDeleteVertexArrays(1, &this->vao);
    }

    void SpriteRenderer::setPos(glm::vec2 p)
    {
        this->position = p;
    }

    void SpriteRenderer::setSize(glm::vec2 s)
    {
        this->size = s;
    }

    void SpriteRenderer::setColor(glm::vec3 c)
    {
        this->color = c;
    }

    void SpriteRenderer::setRotate(GLfloat r)
    {
        this->rotate = r;
    }

	void SpriteRenderer::setVao(GLuint v)
	{
		this->vao = v;
	}

    void SpriteRenderer::setShader(GLuint s)
    {
        this->shader = s;
    }

    void SpriteRenderer::setTexture(GLuint t)
    {
        this->texture2d = t;
    }

    void SpriteRenderer::draw()
    {
        // create model-view matrix
        // (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
        glm::mat4 model;
		model = glm::translate(model, glm::vec3(this->position, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f*this->size.x, 0.5f*this->size.y, 0.0f));
		model = glm::rotate(model, this->rotate, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f*this->size.x, -0.5f*this->size.y, 0.0f));

		model = glm::scale(model, glm::vec3(this->size, 1.0f));

        glUseProgram(this->shader);
		glUniformMatrix4fv(glGetUniformLocation(this->shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(this->shader, "scolor"), this->color.x, this->color.y, this->color.z);

        if(this->texture2d != 0){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->texture2d);
            glUniform1i(glGetUniformLocation(this->shader, "image"), 0);
        }

        glBindVertexArray(this->vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // no index buffer
        glBindVertexArray(0);
    }
}
