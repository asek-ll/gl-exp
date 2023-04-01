#include "game-window.hpp"
#include "game.hpp"

#include "field-renderer.hpp"
#include "game-renderer.hpp"
#include "game-state.hpp"
#include "shader.hpp"
int main() {

  Game game;
  GameWindow gw(game);

  GameState game_state;
  GameRenderer game_renderer(game_state);




  /* gw.Run(); */
  gw.Run2(game_state, game_renderer);

  return 0;
}
