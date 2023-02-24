#ifndef __GAME_RENDERER_H__
#define __GAME_RENDERER_H__

#include "field-renderer.hpp"
#include "game-state.hpp"

class GameRenderer {
  FieldRenderer field_renderer_;
  GameState state_;

public:
  GameRenderer(GameState &state);
  void Render(float dt);
  void Reload();
};

#endif /* end of include guard: __GAME_RENDERER_H__ */
