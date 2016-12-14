
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

        double framestart, frametimer;
        int curframe, totalframes, stepframes;


    public:
        SpriteRenderer(glm::vec2 p = glm::vec2(0.0f),
                       glm::vec2 s = glm::vec2(1.0f),
                       GLfloat r = 0.0f,
                       glm::vec3 c = glm::vec3(1.0f));
        ~SpriteRenderer();
        void update(double dt);
        void animate(double dt);
        void draw();

        void setPos(glm::vec2 p){ this->position = p; };
        void setSize(glm::vec2 s){ this->size = s; };
        void setColor(glm::vec3 c){ this->color = c; };
		void setRotate(GLfloat r){ this->rotate = r; };
		void setVao(GLuint v){ this->vao = v; };
        void setShader(GLuint s){ this->shader = s; };
        void setTexture(GLuint t){ this->texture2d = t; };
        void setFrameTimer(double dt){ this->frametimer = dt > 0.0 ? dt : FRAME_INTERVAL ; }
        
    };
};

#endif
