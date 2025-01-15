#include "State_Load.h"
#include "StateManager.h"

State_Load::State_Load(StateManager *l_stateManager): BaseState(l_stateManager), m_title(nullptr), m_toConfirm(-1) {
}

State_Load::~State_Load() = default;

void State_Load::OnCreate() {
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  const sf::Vector2f l_windowSize = sf::Vector2f(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize());
  m_title = std::make_unique<sf::Text>(m_font, L"读档", static_cast<unsigned int>(l_windowSize.y) / 10);
  m_title->setOrigin({m_title->getLocalBounds().size.x / 2.0f, m_title->getLocalBounds().size.y / 2.0f});
  m_title->setPosition({static_cast<float>(l_windowSize.x) / 2.0f, static_cast<float>(l_windowSize.y) / 10.0f * 2.0f});
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
  const auto l_size = sf::Vector2f(static_cast<float>(l_windowSize.x) / 3.0f,
                                   static_cast<float>(l_windowSize.y) / 10.2f);
  const auto l_pos = sf::Vector2f(static_cast<float>(l_windowSize.x) / 2.0f,
                                  static_cast<float>(l_windowSize.y) / 10.0f * 4.0f);
  const auto l_delta = sf::Vector2f(0, static_cast<float>(l_windowSize.y) / 10.0f);
  for (int i = 0; i < l_buttonInfos.size(); i++) {
    if (l_buttonInfos[i] != L"空") {
      m_buttons.emplace_back(l_buttonInfos[i], l_pos + static_cast<float>(i) * l_delta, l_size, l_windowSize.y / 25,
                             m_font, [this, i, l_windowSize]() {
                               m_confirm = std::make_shared<gl::Confirm>(l_windowSize, m_font);
                               m_toConfirm = i;
                             });
    } else {
      m_buttons.emplace_back(l_buttonInfos[i], l_pos + static_cast<float>(i) * l_delta, l_size, l_windowSize.y / 25,
                             m_font, [this, l_windowSize]() {
                               m_toast = std::make_shared<gl::Toast>(L"此存档为空", m_font, l_windowSize);
                             });
    }
  }
}

void State_Load::OnDestroy() {
}

void State_Load::Update(const sf::Time &l_time) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
  }
  if (m_toast && m_toast->Update(l_time)) {
    m_toast = nullptr;
  }
}

void State_Load::Draw() {
  sf::RenderWindow *l_window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  l_window->draw(*m_title);
  for (auto &l_button: m_buttons) {
    l_button.UpdateRender(*l_window);
  }
  if (m_confirm) {
    const auto l_confirmType = m_confirm->UpdateRender(*l_window);
    if (l_confirmType == gl::ConfirmType::CONFIRM) {
      if (m_stateMgr->HasState(StateType::Game)) {
        m_stateMgr->Remove(StateType::Game);
        m_stateMgr->ProcessRequests();
      }
      std::ifstream inArchive("res/archive/archive" + std::to_string(m_toConfirm) + ".json");
      nlohmann::json l_mapData = nlohmann::json::parse(inArchive);
      inArchive.close();
      m_stateMgr->GetContext()->m_mapData = std::make_unique<nlohmann::json>(l_mapData);
      m_stateMgr->SwitchTo(StateType::Game);
    } else if (l_confirmType == gl::ConfirmType::CANCEL) {
      m_confirm = nullptr;
      m_toConfirm = -1;
    }
  }
  if (m_toast) {
    m_toast->Render(*l_window);
  }
}

void State_Load::Activate() {
}


void State_Load::Deactivate() {
}

