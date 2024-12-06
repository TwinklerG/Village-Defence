#include "Game.h"

float Game::m_FrameTime = 1.0f / 60.0f;

Game::Game() : m_window("Villege Defence", sf::Vector2u(1920, 1080)), m_stateManager(&m_context)
{
  m_context.m_wind = &m_window;
  m_context.m_eventManager = m_window.GetEventManager();
  m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game() {}

void Game::Update()
{
  if (m_elapsed >= sf::seconds(m_FrameTime))
  {
    m_window.Update(); // Update window events.
    m_stateManager.Update(sf::seconds(m_FrameTime));
    m_elapsed -= sf::seconds(m_FrameTime);
  }
}

void Game::Render()
{
  m_window.BeginDraw(); // Clear.
  m_stateManager.Draw();
  m_window.EndDraw(); // Display.
}

Window *Game::GetWindow() { return &m_window; }

sf::Time Game::GetElapsed() { return m_elapsed; }
void Game::RestartClock() { m_elapsed += m_clock.restart(); }

void Game::LateUpdate()
{
  m_stateManager.ProcessRequests();
  RestartClock();
}
