#include "game.hpp"
#include "game_window.hpp"

int main() {

  Game game;

  GameWindow gw(game);

  gw.Run();

  return 0;
}
