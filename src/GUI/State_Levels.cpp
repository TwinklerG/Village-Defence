#include "State_Levels.h"
#include "StateManager.h"

int State_Levels::m_LevelSum = 4;

State_Levels::State_Levels(StateManager *l_stateManager) : BaseState(l_stateManager), m_title(nullptr) {
}

State_Levels::~State_Levels() = default;

void State_Levels::OnCreate() {
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  const auto l_windowSize = sf::Vector2f(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize());
  m_title = std::make_unique<sf::Text>(m_font, L"关卡", l_windowSize.y / 8);
  m_title->setOrigin({m_title->getLocalBounds().size.x / 2, m_title->getLocalBounds().size.y / 2});
  m_title->setPosition({
    static_cast<float>(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize().x) / 2.0f,
    static_cast<float>(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize().y) / 10.0f * 2.0f
  });
  std::vector<sf::String> l_levels{L"关卡一", L"关卡二", L"关卡三", L"关卡四", L"关卡五"};
  for (int i = 0; i < m_LevelSum; ++i) {
    m_buttons.emplace_back(
      l_levels[i],
      sf::Vector2f(l_windowSize.x / 2.0f,
                   l_windowSize.y / 10.0f * 4.0f + static_cast<float>(i) * l_windowSize.y / 10.0f),
      sf::Vector2f(static_cast<float>(l_windowSize.x) / 3.0f, static_cast<float>(l_windowSize.y) / 10.2f),
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
}

void State_Levels::OnDestroy() {
}

void State_Levels::Update(const sf::Time &l_time) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
  }
}

void State_Levels::Draw() {
  sf::RenderWindow *l_wind = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  l_wind->draw(*m_title);
  for (auto &l_button: m_buttons) {
    l_button.UpdateRender(*l_wind);
  }
}

void State_Levels::Activate() {
  for (auto &l_button: m_buttons) {
    l_button.SetIsPressed(true);
  }
}

void State_Levels::Deactivate() {
}
