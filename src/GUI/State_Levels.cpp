#include "State_Levels.h"
#include "StateManager.h"

int State_Levels::m_LevelSum = 4;

State_Levels::State_Levels(StateManager *l_stateManager) : BaseState(l_stateManager) {
}

State_Levels::~State_Levels() = default;

void State_Levels::OnCreate() {
  m_font.loadFromFile("res/fonts/CONSOLAB.TTF");
  auto l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_title.setFont(m_font);
  m_title.setString("Levels");
  m_title.setCharacterSize(l_windowSize.y / 8);
  m_title.setOrigin(m_title.getLocalBounds().width / 2, m_title.getLocalBounds().height / 2);
  m_title.setPosition(static_cast<float>(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize().x) / 2.0f,
                      static_cast<float>(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize().y) / 10.0f);
  for (int i = 0; i < m_LevelSum; ++i) {
    m_buttons.emplace_back(
      "Level " + std::to_string(i),
      sf::Vector2f(static_cast<float>(l_windowSize.x) / 2.0f,
                   static_cast<float>(l_windowSize.y) / 3.0f + static_cast<float>(i) * static_cast<float>(l_windowSize.
                     y) / 8.0f),
      sf::Vector2f(static_cast<float>(l_windowSize.x) / 3.0f, static_cast<float>(l_windowSize.y) / 8.2f),
      l_windowSize.y / 25,
      m_font,
      [i, this]() {
        if (m_stateMgr->HasState(StateType::Game)) {
          m_stateMgr->Remove(StateType::Game);
          m_stateMgr->ProcessRequests();
        }
        m_stateMgr->GetContext()->m_level = i;
        m_stateMgr->SwitchTo(StateType::Game);
      }
    );
  }

  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Levels, "Key_Escape", &State_Levels::MainMenu, this);
}

void State_Levels::OnDestroy() {
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->RemoveCallback(StateType::Levels, "Key_Escape");
}

void State_Levels::Update(const sf::Time &l_time) {
}

void State_Levels::Draw() {
  sf::RenderWindow *l_wind = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  l_wind->draw(m_title);
  for (auto &l_button: m_buttons) {
    l_button.UpdateRender(*l_wind);
  }
}

void State_Levels::MainMenu(EventDetails *l_details) {
  m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Levels::Activate() {
  for (auto &l_button: m_buttons) {
    l_button.SetIsPressed(true);
  }
}

void State_Levels::Deactivate() {
}
