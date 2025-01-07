#include "State_Setting.h"
#include "StateManager.h"

State_Setting::State_Setting(StateManager *l_stateManager): BaseState(l_stateManager) {
}

State_Setting::~State_Setting() = default;

void State_Setting::OnCreate() {
  const sf::Vector2u &l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  const auto l_pos = sf::Vector2f(static_cast<float>(l_windowSize.x) / 2.0f,
                                  static_cast<float>(l_windowSize.y) / 5.0f * 1.0f);
  const auto l_size = sf::Vector2f(static_cast<float>(l_windowSize.x) / 5.1f,
                                   static_cast<float>(l_windowSize.y) / 5.1f);
  const auto l_delta = sf::Vector2f(0, static_cast<float>(l_windowSize.y) / 5.0f);
  auto l_options = std::vector<gl::Button>{
    gl::Button("(1200, 750)", l_pos + 1.0f * l_delta, l_size
               , l_windowSize.y / 22, m_font, [this]() {
                 m_stateMgr->RemoveAll();
                 auto &l_window = *m_stateMgr->GetContext()->m_wind->GetRenderWindow();
                 l_window.create(sf::VideoMode{{1200, 750}, 32}, "Village Defence", sf::Style::Close);
                 l_window.setFramerateLimit(60);
                 l_window.setPosition({
                   static_cast<int>(sf::VideoMode::getDesktopMode().size.x / 2 - l_window.getSize().x / 2),
                   static_cast<int>(sf::VideoMode::getDesktopMode().size.y / 2 - l_window.getSize().y / 2)
                 });
                 SaveResolution(1200, 750);
                 m_stateMgr->SwitchTo(StateType::Intro);
               }),
    gl::Button("(1600, 1000)", l_pos + 2.0f * l_delta, l_size, l_windowSize.y / 22,
               m_font, [this]() {
                 m_stateMgr->RemoveAll();
                 auto &l_window = *m_stateMgr->GetContext()->m_wind->GetRenderWindow();
                 l_window.create(sf::VideoMode{{1600, 1000}, 32}, "Village Defence", sf::Style::Close);
                 l_window.setFramerateLimit(60);
                 l_window.setPosition({
                   static_cast<int>(sf::VideoMode::getDesktopMode().size.x / 2 - l_window.getSize().x / 2),
                   static_cast<int>(sf::VideoMode::getDesktopMode().size.y / 2 - l_window.getSize().y / 2)
                 });
                 SaveResolution(1600, 1000);
                 m_stateMgr->SwitchTo(StateType::Intro);
               }),
    gl::Button("(2000, 1250)", l_pos + 3.0f * l_delta, l_size, l_windowSize.y / 22,
               m_font, [this]() {
                 m_stateMgr->RemoveAll();
                 auto &l_window = *m_stateMgr->GetContext()->m_wind->GetRenderWindow();
                 l_window.create(sf::VideoMode{{2000, 1250}, 32}, "Village Defence", sf::Style::Close);
                 l_window.setFramerateLimit(60);
                 l_window.setPosition({
                   static_cast<int>(sf::VideoMode::getDesktopMode().size.x / 2 - l_window.getSize().x / 2),
                   static_cast<int>(sf::VideoMode::getDesktopMode().size.y / 2 - l_window.getSize().y / 2)
                 });
                 SaveResolution(2000, 1250);
                 m_stateMgr->SwitchTo(StateType::Intro);
               })
  };
  m_select = std::make_unique<gl::Select>(L"分辨率", l_pos, l_size, l_windowSize.y / 18, m_font, l_options);
}

void State_Setting::OnDestroy() {
}

void State_Setting::Update(const sf::Time &l_time) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
  }
}

void State_Setting::Draw() {
  sf::RenderWindow &l_window = *m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  m_select->UpdateRender(l_window);
}

void State_Setting::Activate() {
}

void State_Setting::Deactivate() {
}

void State_Setting::SaveResolution(int width, int height) const {
  std::ifstream l_iFs("res/config/config.json");
  nlohmann::json l_cfg = nlohmann::json::parse(l_iFs);
  l_iFs.close();
  l_cfg["resolution"] = {{"width", width}, {"height", height}};
  m_stateMgr->GetContext()->m_resolution = std::to_string(width) + "_" + std::to_string(height);
  m_stateMgr->GetContext()->m_atomResolution = sf::Vector2f(static_cast<float>(width) / 20.0f,
                                                            static_cast<float>(height) * 2.0f / 25.0f);
  std::ofstream o_iFs("res/config/config.json");
  o_iFs << std::setw(4) << l_cfg;
  o_iFs.close();
}
