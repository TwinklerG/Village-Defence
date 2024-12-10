#include <SFML/Graphics.hpp>
#include "GUI/Game.h"

int main() {
  Game game;
  while (!game.GetWindow()->IsDone()) {
    game.Update();
    game.Render();
    game.LateUpdate();
  }
  return EXIT_SUCCESS;
}
