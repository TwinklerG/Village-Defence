#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager *l_stateManager)
  : BaseState(l_stateManager) {
  m_map = std::make_unique<Map>(m_stateMgr->GetContext()->m_wind->GetRenderWindow(),
                                l_stateManager->GetContext()->m_level,
                                l_stateManager->GetContext()->m_resolution,
                                l_stateManager->GetContext()->m_atomResolution);
}

State_Game::~State_Game() = default;

void State_Game::OnCreate() {
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
  envMgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
}

void State_Game::OnDestroy() {
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->RemoveCallback(StateType::Game, "Key_Escape");
  envMgr->RemoveCallback(StateType::Game, "Key_P");
}

void State_Game::Update(const sf::Time &l_time) {
  m_map->Update(m_stateMgr->GetContext()->m_wind->GetRenderWindow(), l_time);
  if (m_map->GetLives() <= 0) {
    m_stateMgr->GetContext()->m_soundManager.Play("you_lose.ogg", 10);
    m_stateMgr->Remove(StateType::Game);
    m_stateMgr->SwitchTo(StateType::MainMenu);
  } else if (m_map->IsWin()) {
    m_stateMgr->GetContext()->m_soundManager.Play("winner.ogg", 30);
    m_stateMgr->Remove(StateType::Game);
    m_stateMgr->SwitchTo(StateType::MainMenu);
  }
}

void State_Game::Draw() {
  m_map->Render(m_stateMgr->GetContext()->m_wind->GetRenderWindow());
}

void State_Game::MainMenu(EventDetails *l_details) {
  m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails *l_details) {
  m_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::Activate() {
  m_map->Reload();
  m_stateMgr->GetContext()->m_bgmManager.Play("battle.mp3", 8, true);
}

void State_Game::Deactivate() {
  m_map->Save();
  m_stateMgr->GetContext()->m_bgmManager.Play("loading.wav", 100, true);
}
