#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager *l_stateManager) : BaseState(l_stateManager), m_map(l_stateManager->GetContext()->m_wind->GetRenderWindow()) {}

State_Game::~State_Game() = default;

void State_Game::OnCreate()
{
  // m_map.OnCreate(m_stateMgr->GetContext()->m_wind->GetRenderWindow());
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
  envMgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
}

void State_Game::OnDestroy()
{
}

void State_Game::Update(const sf::Time &l_time)
{
  m_map.Update();
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