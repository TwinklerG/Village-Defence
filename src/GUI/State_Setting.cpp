#include "State_Setting.h"

#include "StateManager.h"

State_Setting::State_Setting(StateManager *l_stateManager): BaseState(l_stateManager) {
}

State_Setting::~State_Setting() = default;

void State_Setting::OnCreate() {
  const sf::Vector2u &l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_font.loadFromFile("res/fonts/CONSOLAB.TTF");
  auto l_options = std::vector<gl::Button>{
    gl::Button("(1440, 900)", sf::Vector2f(
                 static_cast<float>(l_windowSize.x) / 2.0f,
                 static_cast<float>(l_windowSize.y) / 5.0f *
                 2.0f),
               sf::Vector2f(static_cast<float>(l_windowSize.x) / 5.0f - 1.0f,
                            static_cast<float>(l_windowSize.y) / 5.0f - 1.0f), l_windowSize.y / 20,
               m_font, [this]() {
                 std::cout << "change resolution to (1440, 900)" << std::endl;
                 m_stateMgr->RemoveAll();
                 m_stateMgr->GetContext()->m_wind->GetRenderWindow()->create(
                   {1440, 900, 32}, "Village Defence", sf::Style::Close
                 );
                 m_stateMgr->SwitchTo(StateType::Intro);
               }),
    gl::Button("(1920, 1080)", sf::Vector2f(
                 static_cast<float>(l_windowSize.x) / 2.0f,
                 static_cast<float>(l_windowSize.y) / 5.0f *
                 3.0f),
               sf::Vector2f(static_cast<float>(l_windowSize.x) / 5.0f - 1.0f,
                            static_cast<float>(l_windowSize.y) / 5.0f - 1.0f), l_windowSize.y / 20,
               m_font, [this]() {
                 std::cout << "change resolution to (1920, 1080)" << std::endl;
                 m_stateMgr->RemoveAll();
                 m_stateMgr->GetContext()->m_wind->GetRenderWindow()->create(
                   {1920, 1080, 32}
                   , "Village Defence", sf::Style::Close
                 );
                 m_stateMgr->SwitchTo(StateType::Intro);
               }),
    gl::Button("(2560, 1600)", sf::Vector2f(
                 static_cast<float>(l_windowSize.x) / 2.0f,
                 static_cast<float>(l_windowSize.y) / 5.0f *
                 4.0f),
               sf::Vector2f(static_cast<float>(l_windowSize.x) / 5.0f - 1.0f,
                            static_cast<float>(l_windowSize.y) / 5.0f - 1.0f), l_windowSize.y / 20,
               m_font, [this]() {
                 std::cout << "change resolution to (2560, 1600)" << std::endl;
                 m_stateMgr->RemoveAll();
                 m_stateMgr->GetContext()->m_wind->GetRenderWindow()->create(
                   {2560, 1600, 32}
                   , "Village Defence", sf::Style::Close
                 );
                 m_stateMgr->SwitchTo(StateType::Intro);
               })
  };
  m_select = std::make_unique<gl::Select>("Resolution",
                                          sf::Vector2f(static_cast<float>(l_windowSize.x) / 2.0f,
                                                       static_cast<float>(l_windowSize.y) / 5.0f),
                                          sf::Vector2f(static_cast<float>(l_windowSize.x) / 5.f - 1.0f,
                                                       static_cast<float>(l_windowSize.y) / 5.0f - 1.0f),
                                          l_windowSize.y / 18,
                                          m_font, l_options);
  // Add KeyBindCallBind
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Setting, "Key_Escape", &State_Setting::MainMenu, this);
}

void State_Setting::OnDestroy() {
}

void State_Setting::Update(const sf::Time &l_time) {
}

void State_Setting::Draw() {
  sf::RenderWindow &l_window = *m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  m_select->UpdateRender(l_window);
}

void State_Setting::MainMenu(EventDetails *l_details) {
  m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Setting::Activate() {
}

void State_Setting::Deactivate() {
}
