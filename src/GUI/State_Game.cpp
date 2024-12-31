#include <iostream>
#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager *l_stateManager)
  : BaseState(l_stateManager) {
  if (m_stateMgr->GetContext()->m_mapData) {
    m_map = std::make_unique<Map>(m_stateMgr->GetContext()->m_wind->GetRenderWindow(),
                                  *m_stateMgr->GetContext()->m_mapData);
    std::cout << "Use Shared Context\n";
    m_stateMgr->GetContext()->m_mapData = nullptr;
    return;
  }
  m_map = std::make_unique<Map>(m_stateMgr->GetContext()->m_wind->GetRenderWindow(),
                                l_stateManager->GetContext()->m_level,
                                l_stateManager->GetContext()->m_resolution,
                                l_stateManager->GetContext()->m_atomResolution);
}

State_Game::~State_Game() = default;

void State_Game::OnCreate() {
}

void State_Game::OnDestroy() {
}

void State_Game::Update(const sf::Time &l_time) {
  m_map->Update(m_stateMgr->GetContext()->m_wind->GetRenderWindow(), l_time);
  if (m_map->GetLives() <= 0) {
    // m_stateMgr->GetContext()->m_soundManager.Play("you_lose.ogg", 10);
    m_stateMgr->Remove(StateType::Game);
    m_stateMgr->SwitchTo(StateType::MainMenu);
  } else if (m_map->IsWin()) {
    // m_stateMgr->GetContext()->m_soundManager.Play("winner.ogg", 30);
    m_stateMgr->Remove(StateType::Game);
    m_stateMgr->SwitchTo(StateType::MainMenu);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
  }
}

void State_Game::Draw() {
  m_map->Render(m_stateMgr->GetContext()->m_wind->GetRenderWindow());
}

void State_Game::Activate() {
  m_map->Reload();
  m_stateMgr->GetContext()->m_bgmManager.Play("battle.mp3", 8, true);
}

void State_Game::Deactivate() {
  m_map->Save();
  m_stateMgr->GetContext()->m_bgmManager.Play("loading.wav", 100, true);
}
