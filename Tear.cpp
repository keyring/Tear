#include "Tear.h"

namespace Tear{
  Engine::Engine():m_window_width(800),
                   m_window_height(600)
  { 
  }

  Engine::~Engine()
  {
  }

  int Engine::init(int width, int height)
  {
    if(!game_init()){
      return 0;
    }

    return 1;
  }

  void Engine::update()
  {
    game_update();
  }

  void Engine::close()
  {
    game_end();
  }


}
