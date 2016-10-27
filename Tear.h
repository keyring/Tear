#ifndef __TEAR_H__
#define __TEAR_H__

extern bool game_load();
extern bool game_init();
extern void game_update();
extern void game_end();

namespace Tear{
  class Engine{
    int m_window_width;
    int m_window_height;

  public:
    Engine();
    ~Engine();

    int init(int width, int height);
    void update();
    void close();

    int getWindowWidth(){ return this->m_window_width; }
    void setWindowWidth(int value){ this->m_window_width = value; }
    int getWindowHeight(){ return this->m_window_height; }
    void setWindowHeight(int value){ this->m_window_height = value; }
  };
};

// global engine object
extern Tear::Engine *g_tear_engine
#endif
