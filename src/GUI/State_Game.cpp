#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager *l_stateManager)
    : BaseState(l_stateManager),
      m_map(m_stateMgr->GetContext()->m_wind->GetRenderWindow(), l_stateManager->GetContext()->m_level) {}

State_Game::~State_Game() {};

void State_Game::OnCreate()
{
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
  envMgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
}

void State_Game::OnDestroy()
{
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->RemoveCallback(StateType::Game, "Key_Escape");
  envMgr->RemoveCallback(StateType::Game, "Key_P");
}

void State_Game::Update(const sf::Time &l_time)
{
  m_map.Update(m_stateMgr->GetContext()->m_wind->GetRenderWindow(), l_time);
  if (m_map.GetLives() <= 0)
  {
    m_stateMgr->Remove(StateType::Game);
    m_stateMgr->SwitchTo(StateType::MainMenu);
  }
}

void State_Game::Draw()
{
  m_map.Render(m_stateMgr->GetContext()->m_wind->GetRenderWindow());
}

void State_Game::MainMenu(EventDetails *l_details)
{
  m_stateMgr->SwitchTo(StateType::MainMenu);
}
void State_Game::Pause(EventDetails *l_details)
{
  m_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}