#include "State_Setting.h"
#include "StateManager.h"

State_Setting::State_Setting(StateManager *l_stateManager): BaseState(l_stateManager), m_confirm(nullptr) {
}

State_Setting::~State_Setting() = default;

void State_Setting::OnCreate() {
  const sf::Vector2u &l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  auto l_pos = sf::Vector2f(static_cast<float>(l_windowSize.x) / 5.0f,
                            static_cast<float>(l_windowSize.y) / 5.0f * 1.0f);
  const auto l_size = sf::Vector2f(static_cast<float>(l_windowSize.x) / 5.1f,
                                   static_cast<float>(l_windowSize.y) / 5.1f);
  const auto l_delta = sf::Vector2f(static_cast<float>(l_windowSize.x) / 5.0f, 0);
  auto l_options = std::vector<gl::Button>{
    gl::Button("(1200, 750)", l_pos + 1.0f * l_delta, l_size
               , l_windowSize.y / 22, m_font, [this]() {
                 m_config.m_windowSize = {1200, 750};
               }),
    gl::Button("(1600, 1000)", l_pos + 2.0f * l_delta, l_size, l_windowSize.y / 22,
               m_font, [this]() {
                 m_config.m_windowSize = {1600, 1000};
               }),
    gl::Button("(2000, 1250)", l_pos + 3.0f * l_delta, l_size, l_windowSize.y / 22,
               m_font, [this]() {
                 m_config.m_windowSize = {2000, 1250};
               })
  };
  m_select.emplace_back(L"分辨率", l_pos, l_size, l_windowSize.y / 18, m_font, l_options);

  l_pos = sf::Vector2f(static_cast<float>(l_windowSize.x) / 5.0f,
                       static_cast<float>(l_windowSize.y) / 5.0f * 2.0f);
  l_options = std::vector<gl::Button>{
    gl::Button("30", l_pos + 1.0f * l_delta, l_size
               , l_windowSize.y / 22, m_font, [this]() {
                 m_config.m_framerateLimit = 30;
               }),
    gl::Button("60", l_pos + 2.0f * l_delta, l_size, l_windowSize.y / 22,
               m_font, [this]() {
                 m_config.m_framerateLimit = 60;
               }),
    gl::Button("144", l_pos + 3.0f * l_delta, l_size, l_windowSize.y / 22,
               m_font, [this]() {
                 m_config.m_framerateLimit = 144;
               })
  };
  m_select.emplace_back(L"帧率上限", l_pos, l_size, l_windowSize.y / 18, m_font, l_options);
}

void State_Setting::OnDestroy() {
}

void State_Setting::Update(const sf::Time &l_time) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    m_confirm = std::make_shared<gl::Confirm>(
      L"退出保存吗", sf::Vector2f(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize()), m_font);
  }
}

void State_Setting::Draw() {
  sf::RenderWindow &l_window = *m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  for (auto &l_select: m_select) {
    l_select.UpdateRender(l_window);
  }
  if (m_confirm) {
    gl::ConfirmType l_confirmType = m_confirm->UpdateRender(l_window);
    if (l_confirmType == gl::ConfirmType::CONFIRM) {
      m_stateMgr->RemoveAll();
      l_window.create(sf::VideoMode{m_config.m_windowSize, 32}, "Village Defence", sf::Style::Close);
      l_window.setFramerateLimit(m_config.m_framerateLimit);
      l_window.setPosition({
        static_cast<int>(sf::VideoMode::getDesktopMode().size.x / 2 - l_window.getSize().x / 2),
        static_cast<int>(sf::VideoMode::getDesktopMode().size.y / 2 - l_window.getSize().y / 2)
      });
      SaveResolution();
      m_stateMgr->SwitchTo(StateType::Intro);
      m_confirm = nullptr;
    } else if (l_confirmType == gl::ConfirmType::CANCEL) {
      m_stateMgr->SwitchTo(StateType::MainMenu);
      m_confirm = nullptr;
    }
  }
}

void State_Setting::Activate() {
  LoadConfig();
  if (m_config.m_windowSize.x == 1200) {
    m_select[0].SetIdx(0);
  } else if (m_config.m_windowSize.x == 1600) {
    m_select[0].SetIdx(1);
  } else {
    m_select[0].SetIdx(2);
  }
  if (m_config.m_framerateLimit == 30) {
    m_select[1].SetIdx(0);
  } else if (m_config.m_framerateLimit == 60) {
    m_select[1].SetIdx(1);
  } else {
    m_select[1].SetIdx(2);
  }
}

void State_Setting::Deactivate() {
}

void State_Setting::LoadConfig() {
  std::ifstream in("res/config/config.json");
  nlohmann::json data = nlohmann::json::parse(in);
  in.close();
  m_config = WindowConfig({data["resolution"]["width"], data["resolution"]["height"]}, data["framerateLimit"]);
}

void State_Setting::SaveResolution() const {
  std::ifstream l_iFs("res/config/config.json");
  nlohmann::json l_cfg = nlohmann::json::parse(l_iFs);
  l_iFs.close();
  l_cfg["resolution"] = {{"width", m_config.m_windowSize.x}, {"height", m_config.m_windowSize.y}};
  l_cfg["framerateLimit"] = m_config.m_framerateLimit;
  m_stateMgr->GetContext()->m_resolution = std::to_string(m_config.m_windowSize.x) + "_" + std::to_string(
                                             m_config.m_windowSize.y);
  m_stateMgr->GetContext()->m_atomResolution = sf::Vector2f(static_cast<float>(m_config.m_windowSize.x) / 20.0f,
                                                            static_cast<float>(m_config.m_windowSize.y) * 2.0f / 25.0f);
  std::ofstream o_iFs("res/config/config.json");
  o_iFs << std::setw(4) << l_cfg;
  o_iFs.close();
}
