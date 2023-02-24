#include "game.hpp"
#include "game-window.hpp"

#include "game-renderer.hpp"
#include "game-state.hpp"
#include "field-renderer.hpp"
#include "shader.hpp"
int main() {

  GameState game_state;

  Game game;

  GameWindow gw(game);

  GameRenderer game_renderer(game_state);

  gw.Run();
  /* gw.Run2(game_state, game_renderer); */

  return 0;
}
