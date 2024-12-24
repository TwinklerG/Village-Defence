#include "State_Load.h"
#include "StateManager.h"

State_Load::State_Load(StateManager *l_stateManager): State_MainMenu(l_stateManager) {
}

State_Load::~State_Load() = default;

void State_Load::OnCreate() {
  m_font.loadFromFile("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  const sf::Vector2u l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_title = sf::Text(L"读取存档", m_font, static_cast<unsigned int>(l_windowSize.y) / 10);
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
  envMgr->AddCallback(StateType::Load, "Key_Escape", &State_Load::MainMenu, this);
}

void State_Load::OnDestroy() {
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->RemoveCallback(StateType::Load, "Key_Escape");
}

void State_Load::Update(const sf::Time &l_time) {
}

void State_Load::MainMenu(EventDetails *l_details) {
  m_stateMgr->SwitchTo(StateType::MainMenu);
}
