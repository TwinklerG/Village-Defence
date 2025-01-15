#include "Game.h"

Game::Game() : m_stateManager(&m_context) {
  std::ifstream config("res/config/config.json");
  nlohmann::json cfg = nlohmann::json::parse(config);
  m_window = std::make_shared<Window>("Village Defence",
                                      sf::Vector2u(cfg["resolution"]["width"], cfg["resolution"]["height"]),
                                      cfg["framerateLimit"]);
  m_stateManager.GetContext()->m_resolution = to_string(cfg["resolution"]["width"]) + "_" + to_string(
                                                cfg["resolution"]["height"]);
  m_stateManager.GetContext()->m_atomResolution = sf::Vector2f(
    static_cast<float>(cfg["resolution"]["width"]) / 20.0f,
    static_cast<float>(cfg["resolution"]["height"]) * 2.0f / 25.0f
  );
  m_context.m_wind = m_window;
  BgmManager &l_bgmManager = m_context.m_bgmManager;
  l_bgmManager.Play("loading.wav", 1000, true);
  m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game() = default;

void Game::Update() {
  m_window->Update(); // Update window events.
  m_stateManager.Update(m_elapsed);
}

void Game::Render() {
  m_window->BeginDraw(); // Clear.
  m_stateManager.Draw();
  m_window->EndDraw(); // Display.
}

std::shared_ptr<Window> Game::GetWindow() { return m_window; }

sf::Time Game::GetElapsed() const { return m_elapsed; }
void Game::RestartClock() { m_elapsed = m_clock.restart(); }

void Game::LateUpdate() {
  m_stateManager.ProcessRequests();
  RestartClock();
}
