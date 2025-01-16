#include <SFML/Graphics.hpp>
#include "GUI/Game.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
  // hide console
  FreeConsole();
#endif

  Game game;
  while (!game.GetWindow()->IsDone()) {
    game.Update();
    game.Render();
    game.LateUpdate();
  }
  return EXIT_SUCCESS;
}
