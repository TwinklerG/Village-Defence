#include "State_Save.h"

State_Save::State_Save(StateManager *l_stateManager): State_MainMenu(l_stateManager) {
}

State_Save::~State_Save() = default;

void State_Save::OnCreate() {
  m_font.loadFromFile("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  const sf::Vector2u l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_title = sf::Text(L"存档", m_font, static_cast<unsigned int>(l_windowSize.y) / 10);
  m_title.setOrigin(m_title.getLocalBounds().width / 2.0f, m_title.getLocalBounds().height / 2.0f);
  m_title.setPosition(static_cast<float>(l_windowSize.x) / 2.0f, static_cast<float>(l_windowSize.y) / 10.0f * 2.0f);
  const auto l_size = sf::Vector2f(static_cast<float>(l_windowSize.x) / 3.0f,
                                   static_cast<float>(l_windowSize.y) / 10.2f);
  const auto l_pos = sf::Vector2f(static_cast<float>(l_windowSize.x) / 2.0f,
                                  static_cast<float>(l_windowSize.y) / 10.0f * 4.0f);
  const auto l_delta = sf::Vector2f(0, static_cast<float>(l_windowSize.y) / 10.0f);
  const auto l_buttonInfos = std::vector<sf::String>({
    L"存档一",
    L"存档二",
    L"存档三",
    L"存档四",
    L"存档五",
  });
  for (int i = 0; i < l_buttonInfos.size(); i++) {
    m_buttons.emplace_back(l_buttonInfos[i], l_pos + static_cast<float>(i) * l_delta, l_size, l_windowSize.y / 20,
                           m_font, []() {
                           });
  }

  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Save, "Key_Escape", &State_Save::MainMenu, this);
}

void State_Save::OnDestroy() {
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->RemoveCallback(StateType::Save, "Key_Escape");
}

void State_Save::Update(const sf::Time &l_time) {
}

void State_Save::Activate() {
}

void State_Save::Deactivate() {
}

void State_Save::MainMenu(EventDetails *l_details) {
  m_stateMgr->SwitchTo(StateType::MainMenu);
}
