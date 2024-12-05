#include "State_Levels.h"
#include "StateManager.h"

State_Levels::State_Levels(StateManager *l_stateManager) : BaseState(l_stateManager) {}

State_Levels::~State_Levels() = default;

void State_Levels::OnCreate()
{
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Levels, "Key_Escape", &State_Levels::MainMenu, this);
}

void State_Levels::OnDestroy() {}

void State_Levels::Update(const sf::Time &l_time) {}

void State_Levels::Draw() {}

void State_Levels::MainMenu(EventDetails *l_details)
{
  m_stateMgr->Remove(StateType::About);
  m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Levels::Activate() {}
void State_Levels::Deactivate() {}