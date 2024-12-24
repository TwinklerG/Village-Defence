#include "StateManager.h"
#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Paused.h"
#include "State_Levels.h"
#include "State_About.h"
#include "State_Store.h"
#include "State_Setting.h"
#include "State_Load.h"

StateManager::StateManager(SharedContext *l_shared) : m_shared(l_shared) {
  RegisterState<State_Intro>(StateType::Intro);
  RegisterState<State_MainMenu>(StateType::MainMenu);
  RegisterState<State_Game>(StateType::Game);
  RegisterState<State_Paused>(StateType::Paused);
  RegisterState<State_Levels>(StateType::Levels);
  RegisterState<State_About>(StateType::About);
  RegisterState<State_Store>(StateType::Store);
  RegisterState<State_Setting>(StateType::Setting);
  RegisterState<State_Load>(StateType::Load);
}

StateManager::~StateManager() {
  for (auto &itr: m_states) {
    itr.second->OnDestroy();
    delete itr.second;
  }
}

void StateManager::Draw() {
  if (m_states.empty()) {
    return;
  }
  if (m_states.back().second->IsTransparent() && m_states.size() > 1) {
    auto itr = m_states.end();
    while (itr != m_states.begin()) {
      if (itr != m_states.end()) {
        if (!itr->second->IsTransparent()) {
          break;
        }
      }
      --itr;
    }
    for (; itr != m_states.end(); ++itr) {
      itr->second->Draw();
    }
  } else {
    m_states.back().second->Draw();
  }
}

void StateManager::Update(const sf::Time &l_time) {
  if (m_states.empty()) {
    return;
  }
  if (m_states.back().second->IsTranscendent() && m_states.size() > 1) {
    auto itr = m_states.end();
    while (itr != m_states.begin()) {
      if (itr != m_states.end()) {
        if (!itr->second->IsTranscendent()) {
          break;
        }
      }
      --itr;
    }
    for (; itr != m_states.end(); ++itr) {
      itr->second->Update(l_time);
    }
  } else {
    m_states.back().second->Update(l_time);
  }
}

SharedContext *StateManager::GetContext() const { return m_shared; }

bool StateManager::HasState(const StateType &l_type) {
  for (const auto &[fst, snd]: m_states) {
    if (fst == l_type) {
      if (const auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), l_type); removed == m_toRemove.end()) {
        return true;
      }
      return false;
    }
  }
  return false;
}

void StateManager::Remove(const StateType &l_type) {
  m_toRemove.push_back(l_type);
}

// TODO: Restart
void StateManager::RemoveAll() {
  m_states.clear();
}


void StateManager::ProcessRequests() {
  while (m_toRemove.begin() != m_toRemove.end()) {
    RemoveState(*m_toRemove.begin());
    m_toRemove.erase(m_toRemove.begin());
  }
}

void StateManager::SwitchTo(const StateType &l_type) {
  m_shared->m_eventManager->SetCurrentState(l_type);
  for (auto itr = m_states.begin(); itr != m_states.end(); ++itr) {
    if (itr->first == l_type) {
      m_states.back().second->Deactivate();
      StateType tmp_type = itr->first;
      BaseState *tmp_state = itr->second;
      m_states.erase(itr);
      m_states.emplace_back(tmp_type, tmp_state);
      tmp_state->Activate();
      return;
    }
  }
  // State with l_type wasn't found.
  if (!m_states.empty()) {
    m_states.back().second->Deactivate();
  }
  CreateState(l_type);
  m_states.back().second->Activate();
}

void StateManager::CreateState(const StateType &l_type) {
  auto newState = m_stateFactory.find(l_type);
  if (newState == m_stateFactory.end()) {
    return;
  }
  BaseState *state = newState->second();
  m_states.emplace_back(l_type, state);
  state->OnCreate();
}

void StateManager::RemoveState(const StateType &l_type) {
  for (auto itr = m_states.begin();
       itr != m_states.end(); ++itr) {
    if (itr->first == l_type) {
      itr->second->OnDestroy();
      delete itr->second;
      m_states.erase(itr);
      return;
    }
  }
}
