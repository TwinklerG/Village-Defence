#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager *l_stateManager) : BaseState(l_stateManager) {
}

State_MainMenu::~State_MainMenu() = default;

void State_MainMenu::OnCreate() {
  m_font.loadFromFile("res/fonts/CONSOLAB.TTF");
  const sf::Vector2u l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_title = sf::Text("Main Menu", m_font, static_cast<unsigned int>(l_windowSize.y) / 10);
  m_title.setOrigin(m_title.getLocalBounds().width / 2.0f, m_title.getLocalBounds().height / 2.0f);
  m_title.setPosition(static_cast<float>(l_windowSize.x) / 2.0f, static_cast<float>(l_windowSize.y) / 10.0f * 3.0f);
  const auto l_size = sf::Vector2f(static_cast<float>(l_windowSize.x) / 3.0f,
                                   static_cast<float>(l_windowSize.y) / 10.2f);
  const auto l_pos = sf::Vector2f(static_cast<float>(l_windowSize.x) / 2.0f,
                                  static_cast<float>(l_windowSize.y) / 10.0f * 5.0f);
  const auto l_delta = sf::Vector2f(0, static_cast<float>(l_windowSize.y) / 10.0f);
  m_buttons = std::vector<gl::Button>{
    gl::Button("NEW GAME", l_pos, l_size,
               l_windowSize.y / 20, m_font, [this]() {
                 m_stateMgr->SwitchTo(StateType::Game);
               }),
    gl::Button("LOAD SAVED", l_pos + l_delta, l_size,
               l_windowSize.y / 20, m_font, [this]() {
                 m_stateMgr->SwitchTo(StateType::Levels);
               }),
    gl::Button("STORE", l_pos + 2.0f * l_delta, l_size,
               l_windowSize.y / 20, m_font, [this]() {
                 m_stateMgr->SwitchTo(StateType::Store);
               }),
    gl::Button("ABOUT", l_pos + 3.0f * l_delta, l_size,
               l_windowSize.y / 20, m_font, [this]() {
                 m_stateMgr->SwitchTo(StateType::About);
               }),
    gl::Button("EXIT", l_pos + 4.0f * l_delta, l_size,
               l_windowSize.y / 20, m_font, [this]() {
                 m_stateMgr->GetContext()->m_wind->Close();
               }),
    gl::Button("Setting", sf::Vector2f(static_cast<float>(l_windowSize.x) / 10.0f * 9,
                                       static_cast<float>(l_windowSize.y) / 10.0f),
               sf::Vector2f(static_cast<float>(l_windowSize.x) / 10.0f, static_cast<float>(l_windowSize.y) / 10.0f),
               l_windowSize.y / 30, m_font, [
                 this]() {
                 this->m_stateMgr->SwitchTo(StateType::Setting);
               }),
  };
}

void State_MainMenu::OnDestroy() {
}

void State_MainMenu::Activate() {
  if (m_stateMgr->HasState(StateType::Levels)) {
    m_stateMgr->Remove(StateType::Levels);
  }
  if (m_stateMgr->HasState(StateType::Game) && m_buttons[0].GetText().getString() == "NEW GAME") {
    sf::Text l_text = m_buttons[0].GetText();
    l_text.setString("RESUME");
    const auto l_lb = l_text.getLocalBounds();
    l_text.setOrigin(l_lb.left + l_lb.width / 2.0f, l_lb.top + l_lb.height / 2.0f);
    m_buttons[0].SetText(l_text);
    m_buttons.pop_back();
  }
}

void State_MainMenu::MouseClick(EventDetails *l_details) {
}

void State_MainMenu::Draw() {
  sf::RenderWindow *window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  window->draw(m_title);
  for (auto &l_button: m_buttons) {
    l_button.UpdateRender(*window);
  }
}

void State_MainMenu::Update(const sf::Time &l_time) {
}

void State_MainMenu::Deactivate() {
}
