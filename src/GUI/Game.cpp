#include "Game.h"

float Game::m_FrameTime = 1.0f / 60.0f;

Game::Game() : m_stateManager(&m_context) {
  std::ifstream config("res/config/config.json");
  nlohmann::json cfg = nlohmann::json::parse(config);
  m_window = std::make_shared<Window>("Village Defence",
                                      sf::Vector2u(cfg["resolution"]["width"], cfg["resolution"]["height"]));
  m_context.m_wind = m_window;
  m_context.m_eventManager = m_window->GetEventManager();
  BgmManager &l_bgmManager = m_context.m_bgmManager;
  l_bgmManager.Play("loading.wav", 100, true);
  m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game() = default;

void Game::Update() {
  if (m_elapsed >= sf::seconds(m_FrameTime)) {
    m_window->Update(); // Update window events.
    m_stateManager.Update(sf::seconds(m_FrameTime));
    m_elapsed -= sf::seconds(m_FrameTime);
  }
}

void Game::Render() {
  m_window->BeginDraw(); // Clear.
  m_stateManager.Draw();
  m_window->EndDraw(); // Display.
}

std::shared_ptr<Window> Game::GetWindow() { return m_window; }

sf::Time Game::GetElapsed() const { return m_elapsed; }
void Game::RestartClock() { m_elapsed += m_clock.restart(); }

void Game::LateUpdate() {
  m_stateManager.ProcessRequests();
  RestartClock();
}
