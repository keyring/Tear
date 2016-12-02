
#ifndef __SPRITE_RENDERER_H__
#define __SPRITE_RENDERER_H__

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Tear {
    class SpriteRenderer {
        glm::vec2 position;
        glm::vec2 size;
        glm::vec3 color;
        GLfloat rotate;

        GLuint vao;
        GLuint shader;
        GLuint texture2d;

    public:
        SpriteRenderer(glm::vec2 p = glm::vec2(0.0f),
                       glm::vec2 s = glm::vec2(1.0f),
                       GLfloat r = 0.0f,
                       glm::vec3 c = glm::vec3(1.0f));
        ~SpriteRenderer();
        void draw();

        void setPos(glm::vec2 p);
        void setSize(glm::vec2 s);
        void setColor(glm::vec3 c);
		void setRotate(GLfloat r);
		void setVao(GLuint v);
        void setShader(GLuint s);
        void setTexture(GLuint t);
        
    };
};

#endif
