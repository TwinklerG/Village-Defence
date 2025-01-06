#include "State_Save.h"

#include <iostream>

State_Save::State_Save(StateManager *l_stateManager): BaseState(l_stateManager) {
}

State_Save::~State_Save() = default;

void State_Save::OnCreate() {
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  const auto l_windowSize = sf::Vector2f(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize());
  m_title = std::make_unique<sf::Text>(m_font, L"存档", static_cast<unsigned int>(l_windowSize.y) / 10);
  m_title->setOrigin({m_title->getLocalBounds().size.x / 2.0f, m_title->getLocalBounds().size.y / 2.0f});
  m_title->setPosition({static_cast<float>(l_windowSize.x) / 2.0f, static_cast<float>(l_windowSize.y) / 10.0f * 2.0f});
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
                           m_font, [this, l_windowSize]() {
                             m_confirm = std::make_shared<gl::Confirm>(l_windowSize, m_font);
                           });
  }
}

void State_Save::OnDestroy() {
}

void State_Save::Update(const sf::Time &l_time) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
  }
}

void State_Save::Draw() {
  const auto l_window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  l_window->draw(*m_title);
  for (auto &l_button: m_buttons) {
    l_button.UpdateRender(*l_window);
  }
  if (m_confirm) {
    if (const gl::ConfirmType l_confirmType = m_confirm->UpdateRender(*l_window);
      l_confirmType == gl::ConfirmType::CONFIRM) {
      m_confirm = nullptr;
      std::cout << "Confirm\n";
    } else if (l_confirmType == gl::ConfirmType::CANCEL) {
      m_confirm = nullptr;
      std::cout << "Cancel\n";
    }
  }
}

void State_Save::Activate() {
}

void State_Save::Deactivate() {
}
