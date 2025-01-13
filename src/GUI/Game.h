#pragma once
#include "Window.h"
#include "StateManager.h"
#include "SharedContext.hpp"

class Game {
public:
  Game();

  ~Game();

  void Update();

  void Render();

  void LateUpdate();

  std::shared_ptr<Window> GetWindow();

  sf::Time GetElapsed() const;

  void RestartClock();

private:
  std::shared_ptr<Window> m_window;
  sf::Clock m_clock;
  sf::Time m_elapsed;

  SharedContext m_context;
  StateManager m_stateManager;
};
