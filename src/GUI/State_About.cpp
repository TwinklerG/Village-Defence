#include "State_About.h"
#include "StateManager.h"

State_About::State_About(StateManager *l_stateManager)
  : BaseState(l_stateManager) {
}

State_About::~State_About() = default;

void State_About::OnCreate() {
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::About, "Key_Escape", &State_About::MainMenu, this);

  const sf::RenderWindow *l_wind = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  m_font.loadFromFile("res/fonts/CONSOLAZ.TTF");
  m_content.setFont(m_font);
  m_content.setString("Village Defence\n\nCreated By Liang Gong & Powered by SFML\n");
  m_content.setCharacterSize(static_cast<unsigned int>(m_stateMgr->GetContext()->m_atomResolution.x) / 3 * 2);
  m_content.setFillColor(sf::Color::White);
  m_content.setOrigin(m_content.getLocalBounds().width / 2.0f, m_content.getLocalBounds().height / 2.0f);
  m_content.setPosition(static_cast<float>(l_wind->getSize().x) / 2.0f,
                        static_cast<float>(l_wind->getSize().y) + m_content.getLocalBounds().height / 2.0f);
}

void State_About::OnDestroy() {
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->RemoveCallback(StateType::About, "Key_Escape");
}

void State_About::Update(const sf::Time &l_time) {
  m_content.setPosition(m_content.getPosition().x, m_content.getPosition().y - l_time.asSeconds() * 80);
  if (m_content.getPosition().y + m_content.getLocalBounds().height / 2 < 0) {
    MainMenu(nullptr);
  }
}

void State_About::Draw() {
  m_stateMgr->GetContext()->m_wind->GetRenderWindow()->draw(m_content);
}

void State_About::MainMenu(EventDetails *l_details) {
  m_stateMgr->Remove(StateType::About);
  m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_About::Activate() {
}

void State_About::Deactivate() {
}
