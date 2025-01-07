#include "State_Save.h"

#include <iostream>

State_Save::State_Save(StateManager *l_stateManager)
  : BaseState(l_stateManager),
    m_toConfirm(-1) {
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
  std::ifstream in("res/archive/outline.json");
  nlohmann::json data = nlohmann::json::parse(in);
  std::vector<sf::String> l_buttonInfos;
  for (int i = 0; i < 5; ++i) {
    if (data.find(std::to_string(i)) == data.end()) {
      l_buttonInfos.emplace_back(L"空");
    } else {
      std::string tmp = data[std::to_string(i)];
      l_buttonInfos.emplace_back(tmp);
    }
  }
  for (int i = 0; i < l_buttonInfos.size(); i++) {
    m_buttons.emplace_back(l_buttonInfos[i], l_pos + static_cast<float>(i) * l_delta, l_size, l_windowSize.y / 25,
                           m_font, [this, l_windowSize, i]() {
                             m_confirm = std::make_shared<gl::Confirm>(l_windowSize, m_font);
                             if (m_toConfirm == -1) {
                               m_toConfirm = i;
                             }
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
      std::cout << "Save in " << m_toConfirm << "\n";
      m_confirm = nullptr;
      std::ifstream in("res/archive/tmp.json");
      std::ofstream out("res/archive/archive" + std::to_string(m_toConfirm) + ".json");
      nlohmann::json data = nlohmann::json::parse(in);
      out << std::setw(2) << data;
      in.close();
      out.close();
      in.open("res/archive/outline.json");
      nlohmann::json outlineData = nlohmann::json::parse(in);
      time_t l_time;
      time(&l_time);
      m_stateMgr->SwitchTo(StateType::MainMenu);
      outlineData[std::to_string(m_toConfirm)] = std::string(
                                                   "Level " + std::to_string(m_stateMgr->GetContext()->m_level) + "\n")
                                                 + std::string(ctime(&l_time));
      in.close();
      out.open("res/archive/outline.json");
      out << std::setw(2) << outlineData;
      out.close();
    } else if (l_confirmType == gl::ConfirmType::CANCEL) {
      m_confirm = nullptr;
      m_toConfirm = -1;
    }
  }
}

void State_Save::Activate() {
  // std::ifstream in("res/archive/outline.json");
  // nlohmann::json data = nlohmann::json::parse(in);
  // std::vector<sf::String> l_buttonInfos;
  // for (int i = 0; i < 5; ++i) {
  //   if (data.find(std::to_string(i)) == data.end()) {
  //     l_buttonInfos.emplace_back(L"空");
  //   } else {
  //     std::string tmp = data[std::to_string(i)];
  //     l_buttonInfos.emplace_back(tmp);
  //   }
  // }
  // for (int i = 0; i < l_buttonInfos.size(); i++) {
  //   if (m_buttons[i].GetText().getString() != l_buttonInfos[i]) {
  //     m_buttons[i].GetText().setString(l_buttonInfos[i]);
  //   }
  // }
}

void State_Save::Deactivate() {
}
