#ifndef __TEAR_H__
#define __TEAR_H__

#include <iostream>
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "SpriteRenderer.h"

#define UPDATE_INTERVAL 0.01  // 10ms
#define FRAME_INTERVAL 0.016 // 16ms

extern bool game_load();
extern bool game_init();
extern void game_update(double dt);
extern void game_render();
extern void game_end();

namespace Tear{
    class Engine{
        
        int m_window_width;
        int m_window_height;
        float m_update_interval;

    public:
        Engine();
        ~Engine();

        int init(int width, int height);
        void update(double dt);
        void render();
        void close();

        GLuint _shader_create(const GLchar *vs, const GLchar *fs);
        GLuint _texture_create(const char *filepath);

        int getWindowWidth(){ return this->m_window_width; }
        void setWindowWidth(int value){ this->m_window_width = value; }
        int getWindowHeight(){ return this->m_window_height; }
        void setWindowHeight(int value){ this->m_window_height = value; }

        double getUpdateInterval(){ return this->m_update_interval; }
        void setUpdateInterval(double dt){ this->m_update_interval = dt > 0.0 ? dt : UPDATE_INTERVAL; }
    };
};

// global engine object
extern Tear::Engine *g_tear_engine;
#endif
