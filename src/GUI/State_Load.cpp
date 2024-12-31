#include "State_Load.h"
#include "StateManager.h"

State_Load::State_Load(StateManager *l_stateManager): BaseState(l_stateManager), m_title(nullptr) {
}

State_Load::~State_Load() = default;

void State_Load::OnCreate() {
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  const sf::Vector2u l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_title = std::make_unique<sf::Text>(m_font, L"读档", static_cast<unsigned int>(l_windowSize.y) / 10);
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
                           m_font, [this]() {
                             //TODO: Load Map Data Respectively
                             if (m_stateMgr->HasState(StateType::Game)) {
                               m_stateMgr->Remove(StateType::Game);
                               m_stateMgr->ProcessRequests();
                             }
                             std::ifstream in("res/config/save.json");
                             nlohmann::json l_mapData = nlohmann::json::parse(in);
                             in.close();
                             m_stateMgr->GetContext()->m_mapData = std::make_unique<nlohmann::json>(l_mapData);
                             m_stateMgr->SwitchTo(StateType::Game);
                           });
  }
}

void State_Load::OnDestroy() {
}

void State_Load::Update(const sf::Time &l_time) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
  }
}

void State_Load::Draw() {
  sf::RenderWindow *l_window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  l_window->draw(*m_title);
  for (auto &l_button: m_buttons) {
    l_button.UpdateRender(*l_window);
  }
}

void State_Load::Activate() {
  for (auto &l_button: m_buttons) {
    l_button.SetIsPressed(true);
  }
}

void State_Load::Deactivate() {
}
